/* This is a code generator for cparser generating Eigen instead of Firm IR.
 * Function arguments are passed by stack in reverse order. Struct and union
 * returns by value are handled via pointer as first argument to caller
 * allocated memory.
 *
 * (c) 2024 Rochus Keller (me@rochus-keller.ch)
 *
 * Made available under the same license as cparser
 */

#include <iostream>
#include <unordered_map>
#include <deque>
#include <bitset>
#include <sstream>
#include <set>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "layout.hpp"
#include "cdemitter.hpp"
#include "cdemittercontext.hpp"
#include "stdcharset.hpp"
#include "stringpool.hpp"
#include "strdiagnostics.hpp"
#include "cdgenerator.hpp"
using namespace ECS;

extern "C" {
#include "ast2ir.h"
#include "target.h"
#include "panic.h"
#include "symbol_table.h"
#include "symbol_t.h"
#include "walk.h"
#include "libfirm/tv.h"
#include "constfold.h"
#include "types.h"
}

// TODO
#define __ECS_DUPLICATE_ISSUE__

class MyEmitter : public Code::Emitter
{
public:
    MyEmitter(Diagnostics& d, StringPool& sp, Charset& c, Code::Platform& p):
        Code::Emitter(d,sp,c,p),ctx(*this,s) {}

    using Smop = Emitter::Context::SmartOperand;
    using Label = Emitter::Context::Label;
    using Context = Code::Emitter::Context;
    using RestoreRegisterState = Code::Emitter::Context::RestoreRegisterState;

    Code::Sections s;
    Context ctx;
};

using Smop = MyEmitter::Smop;
using Label = MyEmitter::Label;
using RestoreRegisterState = MyEmitter::RestoreRegisterState;

static MyEmitter::Context* e = 0;
static std::deque<Label*> break_target_labels, continue_target_label;
static std::deque<Label> goto_target_labels;
static Label* end_of_function_label = 0;
static type_t* return_type = 0;
static symbol_t* func_name = 0;
static std::set<type_t*> to_declare;
static std::unordered_map<std::string,const char*> string_decls;
static std::deque<expression_t*> compound_literal_decls;
static std::deque<entity_t*> static_locals;
static translation_unit_t* current_translation_unit = 0;
static const char* current_source_file = "";

enum EcsTypes { u1, u2, u4, u8, s1, s2, s4, s8, f4, f8, ptr, fun, MaxType };

struct EcsType {
    uint8_t type;
    uint8_t width;
    const char* name;
    const char* dbgname;
} ecsTypes[] = {
    { u1, 8, "u1", "byte" },
    { u2, 16, "u2", "ushort" },
    { u4, 32, "u4", "uint" },
    { u8, 64, "u8", "ulong" },
    { s1, 8, "s1", "char" },
    { s2, 16, "s2", "short" },
    { s4, 32, "s4", "int" },
    { s8, 64, "s8", "long" },
    { f4, 32, "f4", "float" },
    { f8, 64, "f8", "double" },
    { ptr, 0, "ptr" },
    { fun, 0, "fun" },
};

static Code::Type types[MaxType];

static void init_types()
{
    types[u1] = Code::Unsigned(1);
    types[u2] = Code::Unsigned(2);
    types[u4] = Code::Unsigned(4);
    types[u8] = Code::Unsigned(8);
    types[s1] = Code::Signed(1);
    types[s2] = Code::Signed(2);
    types[s4] = Code::Signed(4);
    types[s8] = Code::Signed(8);
    types[f4] = Code::Float(4);
    types[f8] = Code::Float(8);
    types[ptr] = Code::Pointer(target_pointer_width());
    types[fun] = Code::Function(target_pointer_width());
}

static uint8_t getTypeId(type_t *ty) {

    ty = skip_typeref(ty);
    const int sz = get_ctype_size(ty);

    if( ty->kind == TYPE_ATOMIC ) {
        switch (ty->atomic.akind) {
        case ATOMIC_TYPE_BOOL:
            return u1;
        case ATOMIC_TYPE_CHAR:
            // return is_type_signed(ty) ? s1 : u1;
            return s1; // TODO: is_type_signed renders false for ATOMIC_TYPE_CHAR
        case ATOMIC_TYPE_SCHAR:
            return s1;
        case ATOMIC_TYPE_UCHAR:
            return u1;
        case ATOMIC_TYPE_WCHAR_T:
        case ATOMIC_TYPE_USHORT:
        case ATOMIC_TYPE_SHORT:
        case ATOMIC_TYPE_INT:
        case ATOMIC_TYPE_UINT:
        case ATOMIC_TYPE_LONG:
        case ATOMIC_TYPE_ULONG:
        case ATOMIC_TYPE_LONGLONG:
        case ATOMIC_TYPE_ULONGLONG:
            if(sz == 2)
                return !is_type_signed(ty) ? u2 : s2;
            else if( sz == 4 )
                return !is_type_signed(ty) ? u4 : s4;
            else if( sz == 8 )
                return !is_type_signed(ty) ? u8 : s8;
            else
                assert(0);

        case ATOMIC_TYPE_FLOAT:
            return f4;
        case ATOMIC_TYPE_DOUBLE:
        case ATOMIC_TYPE_LONG_DOUBLE:
            return f8;
        }
    }
    if( ty->kind == TYPE_ENUM )
        return s4; // RISK
    if( ty->kind == TYPE_POINTER )
        if( ty->pointer.points_to && ty->pointer.points_to->kind == TYPE_FUNCTION )
            return fun;
        else
            return ptr;
    if( ty->kind == TYPE_FUNCTION )
        return fun;
    if( ty->kind == TYPE_ARRAY )
        return ptr; // RISK

    if( target_pointer_width() == 4 )
        return u4;
    else
        return u8;
}

static Code::Type getCodeType(type_t *ty) {

    return types[getTypeId(ty)];
}

static unsigned char getTypeWidth(type_t *ty) {

    return ecsTypes[ getTypeId(ty) ].width;
}

uint32_t MurmurOAAT_32(const char* str, uint32_t h)
{
    // One-byte-at-a-time hash based on Murmur's mix
    // Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}

void name_hash(const char* in, char* out, int outlen )
{
    const char* code = "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            //"$_#.";
    const int codelen = strlen(code);

    const int inlen = strlen(in);
    int i;
    out[outlen] = 0;
    for( i = 0; i < outlen; i++ )
        out[i] = '_';
    if( inlen < outlen )
        for( i = 0; i < inlen; i++ )
        {
            union { uint32_t h; char s[4]; };
            h = MurmurOAAT_32(in+i,0x12345678);
            for( int j = 0; j < 4; j++ )
                out[(i+j) % outlen] ^= s[j];
        }
    else
        for( i = 0; i < inlen; i++ )
        {
            const int j = i % outlen;
            out[j] ^= in[i];
        }
    for( i = 0; i < outlen; i++ )
    {
        const uint8_t ch = (uint8_t)out[i];
        char c = code[ch % codelen];
        out[i] = c;
    }
}

static std::string file_hash()
{
    const int len = 10;
    char buf[len];
    name_hash(current_source_file,buf,len);
    std::string res = buf;
    res += '#';
    return res;
}

static std::string rename2(entity_base_t* var,bool is_static)
{
    std::string name = var->symbol->string;
    while( is_static && var && var->parent_entity && var->parent_entity->kind == ENTITY_FUNCTION ) {
        if( var->parent_scope->depth > 2 ) // depth 2 is on function level
        {
            char buf[20];
            sprintf(buf,"%p#",var->parent_scope );
            char* p = &buf[2]; // get rid of "0x"
            name = p + name;
        }
        var = &var->parent_entity->base;
        name = std::string(var->symbol->string) + "#" + name;
    }
    if( is_static )
    {
        // prefix with file path hash
        name = file_hash() + name;
    }
    return name;
}

static std::string rename(entity_t* var)
{
    const bool is_static = var->variable.base.storage_class == STORAGE_CLASS_STATIC;
    return rename2(&var->base, is_static);
}

const char* file_name(const char* path)
{
    const char* pos = strrchr(path, '/');
    if( pos == 0 )
        pos = strrchr(path, '\\');
    if( pos == 0 )
        return path;
    else
        return pos+1;
}

static inline ECS::Position toPos(int line, int column)
{
#ifdef CPARSER_SUPPORT_COLUMNS
    return ECS::Position(line, column);
#else
    return ECS::Position(line, 1);
#endif
}

static void loc( const position_t& pos, bool force = false )
{
    static const char* input_name = "";
    static int line_no = 0, col_no = 0;

    if( pos.input_name != input_name || pos.lineno != line_no || pos.colno != col_no || force )
    {
        if( target.debug_info && end_of_function_label )
        {
            e->Break(pos.input_name,toPos(pos.lineno,pos.colno));
            // NOTE that pos.input_name is either an absolute or relative path, depending on what
            // is fed to the compiler.
        }//else
        {
            std::ostringstream s;
            s << "line " << file_name(pos.input_name) << ":" << pos.lineno << ":" << pos.colno;
            e->Comment(s.str().c_str());
        }
        input_name = pos.input_name;
        line_no = pos.lineno;
        col_no = pos.colno;
    }
}

static Smop var_address(entity_t* var)
{
    // Local variable
    if ( (var->kind == ENTITY_VARIABLE && var->variable.is_local) ||
         var->kind == ENTITY_PARAMETER ) {
        return (Code::Reg(types[ptr],Code::RFP, var->variable.offset));
    }

    // Function
    if (var->kind == ENTITY_FUNCTION) {
        return (Code::Adr(types[fun],rename(var)));
    }

    // Global variable (includes local static)
    return (Code::Adr(types[ptr],rename(var)));
}

static Smop expression(expression_t * expr);
static void run_initializer(type_t* type, const std::string& name, int offset, initializer_t *initializer);

static void Fill(type_t* type, const Smop& lhs)
{
    const int len = get_ctype_size(type);
    switch( len )
    {
    case 1:
        e->Move(e->MakeMemory(types[u1],lhs),Code::UImm(types[u1],0));
        break;
    case 2:
        e->Move(e->MakeMemory(types[u2],lhs),Code::UImm(types[u2],0));
        break;
    case 4:
        e->Move(e->MakeMemory(types[u4],lhs),Code::UImm(types[u4],0));
        break;
    case 8:
        e->Move(e->MakeMemory(types[u8],lhs),Code::UImm(types[u8],0));
        break;
    default:
        e->Fill(lhs,Code::Imm(types[ptr],get_ctype_size(type)), Code::Imm(types[u1],0));
        break;
    }
}

// Compute the absolute address of a given node.
// It's an error if a given node does not reside in memory.
static Smop lvalue(expression_t * expr) {

    switch (expr->kind)
    {
    case EXPR_REFERENCE: {
        entity_t* var = expr->reference.entity;

        return var_address(var);
    }
    case EXPR_ARRAY_ACCESS:  {
        Smop arr = expression(expr->array_access.array_ref);
        e->SaveRegister(arr);
        Smop idx = expression(expr->array_access.index);
        e->RestoreRegister(arr);
        type_t    *const elem_type = skip_typeref(expr->base.type);
        idx = e->Multiply(idx, Code::Imm(idx.type,get_ctype_size(elem_type)));
        loc(expr->base.pos);
        return e->Add(arr,e->Convert(types[ptr],idx));
    }
    case EXPR_SELECT: {
        Smop tmp = expression(expr->select.compound);
        entity_t* mem = expr->select.compound_entry;
        assert(mem->kind == ENTITY_COMPOUND_MEMBER);
        loc(expr->base.pos);
        return e->Add(e->Convert(types[ptr],tmp), Code::Imm(types[ptr],mem->compound_member.offset));
    }
    case EXPR_BINARY_COMMA: {
        expression(expr->binary.left); // ignore result
        return lvalue(expr->binary.right);
    }
    case EXPR_UNARY_DEREFERENCE: {
        Smop tmp = expression(expr->unary.value);
        return tmp;
    }
    case EXPR_CALL:
        if (expr->call.return_buffer) {
            return expression(expr);
        }
        break;
    case EXPR_BINARY_ASSIGN:
    case EXPR_CONDITIONAL:
        if (is_type_compound(skip_typeref(expr->base.type))) {
            return expression(expr);
        }
        break;
    case EXPR_COMPOUND_LITERAL:  {
        if( expr->compound_literal.global_scope ) {
            assert( expr->compound_literal.id == 0 );
            compound_literal_decls.push_back(expr);
            expr->compound_literal.id = compound_literal_decls.size();
            char buf[10];
            sprintf(buf,"%d",expr->compound_literal.id);
            return Code::Adr(types[ptr],file_hash() + buf );
        }else
        {
            type_t* type = skip_typeref(expr->compound_literal.type);

            // make sure the whole area is zero in case the initializer doesn't
            Smop lhs (Code::Reg(types[ptr],Code::RFP,expr->compound_literal.id));
            Fill(type,lhs);

            run_initializer(type, "", expr->compound_literal.id, expr->compound_literal.initializer);
            return (Code::Reg(types[ptr],Code::RFP, expr->compound_literal.id));
        }
    }

    }
    panic("not an lvalue");
    return Smop();
}

static void load(type_t * ty, Smop& tmp, const position_t& pos) {
    ty = skip_typeref(ty);
    switch (ty->kind) {
    case TYPE_ARRAY:
    case TYPE_COMPOUND_STRUCT:
    case TYPE_COMPOUND_UNION:
    case TYPE_FUNCTION:
        // If it is an array, do not attempt to load a value to the
        // register because in general we can't load an entire array to a
        // register. As a result, the result of an evaluation of an array
        // becomes not the array itself but the address of the array.
        // This is where "array is automatically converted to a pointer to
        // the first element of the array in C" occurs.
        return;
    }

#if 1
    if( ty->kind == TYPE_POINTER && ty->pointer.replacemen_of != 0 ) {
        type_t* t = skip_typeref(ty->pointer.replacemen_of);
        if( t->kind == TYPE_ARRAY)
            return; // not really a pointer, but actually an array
        if( t->kind == TYPE_FUNCTION ) {
            tmp = e->Convert(types[fun], tmp);
            return; // actually or function
        }
    }
#endif

    loc(pos);
    const Code::Type type = getCodeType(ty);
    tmp = e->MakeMemory(type,tmp);
}

static void cast(type_t *from, type_t *to, Smop& reg) {

    if (to->kind == TYPE_VOID)
        return;

    Code::Type fromType = getCodeType(from);
    Code::Type toType = getCodeType(to);

    if (to->kind == TYPE_ATOMIC && to->atomic.akind == ATOMIC_TYPE_BOOL) {
        Label label = e->CreateLabel();
        e->BranchNotEqual(label,Code::Imm(fromType,0),reg);
        reg = e->Set (label, Code::Imm(toType,0), Code::Imm(toType,1));
        return;
    }

    if( fromType != toType )
        reg = e->Convert(toType,reg);
}

static void store(type_t *ty, const Smop& lhs, const Smop& rhs, const position_t& pos) {
    ty = skip_typeref(ty);
    switch (ty->kind) {
    case TYPE_COMPOUND_STRUCT:
    case TYPE_COMPOUND_UNION:
        loc(pos);
        e->Copy(lhs, rhs, Code::Imm(types[ptr],get_ctype_size(ty)));
        return;
    }

    const Code::Type type = getCodeType(ty);
    Smop rhs2 = e->Convert(type,rhs);
    loc(pos);
    e->Move(e->MakeMemory(type,lhs),rhs2);
}

static int scale_for_pointer_arith(expression_kind_t op, Smop& lhs, type_t* lhsT, Smop& rhs, type_t* rhsT )
{
    lhsT = skip_typeref(lhsT);
    rhsT = skip_typeref(rhsT);
    switch(op)
    {
    case EXPR_BINARY_ADD:
    case EXPR_BINARY_ADD_ASSIGN:
    case EXPR_BINARY_SUB:
    case EXPR_BINARY_SUB_ASSIGN:
        if( lhsT->kind != TYPE_POINTER && rhsT->kind != TYPE_POINTER )
            return 0;
        break;
    default:
        return 0;
    }
    int res = 0;
    if(lhsT->kind != TYPE_POINTER) {
        res = get_ctype_size(rhsT->pointer.points_to);
        lhs = e->Multiply(lhs, Code::Imm(lhs.type,res));
    }
    if(rhsT->kind != TYPE_POINTER) {
        res = get_ctype_size(lhsT->pointer.points_to);
        rhs = e->Multiply(rhs, Code::Imm(rhs.type,res));
    }
    if( res == 0 ) // apparently both sides are pointers
        res = get_ctype_size(rhsT->pointer.points_to);
    else
        res = 0; // only divide by with for pointer sub pointer
    return res;
}


static Smop binary_ops(expression_kind_t op, const Smop& lhs, const Smop& rhs, int baseTypeSize)
{
    switch (op) {
    case EXPR_BINARY_ADD:
    case EXPR_BINARY_ADD_ASSIGN:
        if( target_data[target.target].architecture == Amd32 ) // TODO: work-around add issue with 64 bit numbers on 32 bit systems
        {
            Smop tmp = e->Move(lhs);
            return e->Add(tmp,rhs);
        }else
            return e->Add(lhs,rhs);
    case EXPR_BINARY_SUB:
    case EXPR_BINARY_SUB_ASSIGN: {
        Smop res = e->Subtract(lhs,rhs);
        if( baseTypeSize )
            res = e->Divide(res, Code::Imm(types[ptr],baseTypeSize));
        return res;
    }
    case EXPR_BINARY_MUL:
    case EXPR_BINARY_MUL_ASSIGN:
        return e->Multiply(lhs,rhs);
    case EXPR_BINARY_DIV:
    case EXPR_BINARY_DIV_ASSIGN:
        if( rhs.model == Code::Operand::Immediate && rhs.type.model == Code::Type::Float && rhs.fimm == 0.0 ) {
            if( lhs.model == Code::Operand::Immediate && lhs.type.model == Code::Type::Float && lhs.fimm == 0.0)
                return Code::FImm(lhs.type,NAN);
            else
                return Code::FImm(lhs.type,HUGE_VALF);
        }
        else
            return e->Divide(lhs,rhs);
    case EXPR_BINARY_MOD:
    case EXPR_BINARY_MOD_ASSIGN:
        return e->Modulo(lhs,rhs);
    case EXPR_BINARY_BITWISE_AND:
    case EXPR_BINARY_BITWISE_AND_ASSIGN:
        return e->And(lhs,rhs);
    case EXPR_BINARY_BITWISE_OR:
    case EXPR_BINARY_BITWISE_OR_ASSIGN:
        return e->Or(lhs,rhs);
    case EXPR_BINARY_BITWISE_XOR:
    case EXPR_BINARY_BITWISE_XOR_ASSIGN:
        return e->ExclusiveOr(lhs,rhs);
    case EXPR_BINARY_EQUAL:
    case EXPR_BINARY_GREATER:
    case EXPR_BINARY_GREATEREQUAL:
    case EXPR_BINARY_LESS:
    case EXPR_BINARY_LESSEQUAL:
    case EXPR_BINARY_NOTEQUAL:
    {
        Label ltrue = e->CreateLabel();
        switch(op)
        {
        case EXPR_BINARY_EQUAL:
            e->BranchEqual(ltrue,lhs,rhs);
            break;
        case EXPR_BINARY_NOTEQUAL:
            e->BranchNotEqual(ltrue,lhs,rhs);
            break;
        case EXPR_BINARY_LESS:
            e->BranchLessThan(ltrue,lhs,rhs);
            break;
        case EXPR_BINARY_LESSEQUAL:
            e->BranchGreaterEqual(ltrue,rhs,lhs);
            break;
        case EXPR_BINARY_GREATER:
            e->BranchLessThan(ltrue,rhs,lhs);
            break;
        case EXPR_BINARY_GREATEREQUAL:
            e->BranchGreaterEqual(ltrue,lhs,rhs);
            break;
        }

        return e->Set(ltrue,Code::Imm(types[s4],0),Code::Imm(types[s4],1));
    } break;
    case EXPR_BINARY_SHIFTLEFT:
    case EXPR_BINARY_SHIFTLEFT_ASSIGN:
        return e->ShiftLeft(lhs,rhs);
    case EXPR_BINARY_SHIFTRIGHT:
    case EXPR_BINARY_SHIFTRIGHT_ASSIGN:
        return e->ShiftRight(lhs,rhs);
    }
    panic("expression not implemented");
}

static void fetch_bitfield(expression_t const *const expr, Smop& val)
{
    if( expr->kind != EXPR_SELECT )
        return;

    entity_t* mem = expr->select.compound_entry;
    assert(mem->kind == ENTITY_COMPOUND_MEMBER);

    if (mem->compound_member.bitfield) {

        loc(expr->base.pos);

        const unsigned char w = getTypeWidth(mem->compound_member.base.type);
        const Code::Type nm = getCodeType(mem->compound_member.base.type);
        // align the bitfield to the msb of the underlying type
        val = e->ShiftLeft(e->Convert(nm,val), Code::Imm(nm,w - mem->compound_member.bit_size -
                                                         mem->compound_member.bit_offset));
        val = e->ShiftRight(val, Code::Imm(nm,w - mem->compound_member.bit_size));
    }
}

static void store_bitfield_imp(entity_t* mem, const Smop& lhs, Smop& rhs, const position_t& pos)
{
    loc(pos);

    const Code::Type rty = rhs.type;

    // If the lhs is a bitfield, we need to read the current value
    // from memory and merge it with a new value.
    assert(mem->kind == ENTITY_COMPOUND_MEMBER);

    const Code::Type mty = getCodeType(mem->compound_member.base.type);

    Smop rdi = e->Convert(rty,rhs);
    rdi = e->And(rdi, Code::Imm(rty,(1LL << mem->compound_member.bit_size) - 1));
    rdi = e->Convert(mty,rdi);
    rdi = e->ShiftLeft(rdi, Code::Imm(mty,mem->compound_member.bit_offset));

    rhs = e->Move(e->MakeMemory(mty,lhs));

    const uint64_t mask = ((1LL << mem->compound_member.bit_size) - 1) << mem->compound_member.bit_offset;
    Smop r9;
    if( mty.model == Code::Type::Signed ) { // renders false results: is_type_signed(mem->compound_member.base.type)) {
        if( mty.size == 1 )
            r9 = Code::Imm(mty, ~(char)mask);
        else if( mty.size == 2 )
            r9 = Code::Imm(mty, ~(short)mask);
        else if( mty.size == 4 )
            r9 = Code::Imm(mty, ~(int)mask);
        else
            r9 = Code::Imm(mty, ~(int64_t)mask);
    }else {
        if( mty.size == 1 )
            r9 = Code::UImm(mty, ~(unsigned char)mask);
        else if( mty.size == 2 )
            r9 = Code::UImm(mty, ~(unsigned short)mask);
        else if( mty.size == 4 )
            r9 = Code::UImm(mty, ~(unsigned int)mask);
        else
            r9 = Code::UImm(mty, ~mask);
    }
    rhs = e->And(e->Convert(mty,rhs), r9);
    rhs = e->Or(rhs, rdi);

    store(mem->compound_member.base.type, lhs, rhs, pos);
}

static int store_bitfield(expression_t const*const expr, const Smop& lhs, Smop& rhs)
{
    if (expr->kind == EXPR_SELECT &&
            expr->select.compound_entry->compound_member.bitfield) {

        store_bitfield_imp(expr->select.compound_entry, lhs, rhs, expr->base.pos);
        return 1;
    }else
        return 0;
}

Smop prefix_inc_dec(expression_t const*const expr, const Smop& lhs, int inc, int returnOldVal )
{
    loc(expr->base.pos);

    Smop rhs = e->Move(lhs);
    load(expr->base.type,rhs,expr->base.pos);
    fetch_bitfield(expr, rhs);
    Smop oldVal = returnOldVal ? e->Move(rhs) : rhs;
    int off = 1;
    type_t* type = skip_typeref(expr->base.type);
    if( type->kind == TYPE_POINTER )
        off *= get_ctype_size(type->pointer.points_to);
    if( inc )
        rhs = e->Add(rhs, Code::Imm(rhs.type,off));
    else
        rhs = e->Subtract(rhs, Code::Imm(rhs.type,off));
    if( store_bitfield(expr, lhs, rhs) ) {
        if( !returnOldVal )
            fetch_bitfield(expr, oldVal);
        return oldVal;
    } else {
        store(expr->base.type, lhs, rhs, expr->base.pos);
        if( !returnOldVal )
            oldVal = rhs;
        return oldVal;
    }
}

// Round up `n` to the nearest multiple of `align`. For instance,
// align_to(5, 8) returns 8 and align_to(11, 8) returns 16.
int align_to(int n, int align) {

    return (n + align - 1) / align * align;
}

static int push_struct(type_t *ty, const Smop& reg) {

    const int sz = align_to(get_ctype_size(ty), target_stack_align());
    e->Subtract(Code::Reg(types[ptr],Code::RSP), Code::Reg(types[ptr],Code::RSP),
                Code::Imm(types[ptr],sz));
    e->Copy(Code::Reg(types[ptr],Code::RSP), reg, Code::Imm(types[ptr],sz));
    return sz;
}

static int pushRes(const Code::Type& type, const Smop& reg) {

    e->Push(e->Convert(type,reg));
    const int aligned_size = align_to(type.size,target_stack_align());
    return aligned_size;
}

static int push_args2(call_argument_t *args, int param_count) {

    if (!args)
        return 0;

    // invert order of arguments
    int aligned_size = push_args2(args->next,param_count-1);

    Smop arg = expression(args->expression);

    type_t* ty = skip_typeref(args->expression->base.type);
    switch (ty->kind) {
    case TYPE_COMPOUND_STRUCT:
    case TYPE_COMPOUND_UNION:
        aligned_size += push_struct(ty, arg);
        break;
    default:
#if 0
        // NOTE: this no longer seems to be necessary with cparser
        if( param_count <= 0 && ty->kind == TYPE_ATOMIC )
        {
            // this is one of the variable arguments
            switch(ty->atomic.akind)
            {
            case ATOMIC_TYPE_BOOL:
            case ATOMIC_TYPE_CHAR:
            case ATOMIC_TYPE_SCHAR:
            case ATOMIC_TYPE_UCHAR:
            case ATOMIC_TYPE_SHORT:
            case ATOMIC_TYPE_USHORT: {
                type_t* to;
                if( is_type_signed(ty) )
                    to = type_int;
                else
                    to = type_unsigned_int;
                cast(ty,to, arg);
                ty = to;
                break;
            }
            case ATOMIC_TYPE_FLOAT: {
                type_t* to = type_double;
                cast(ty,to, arg);
                ty = to;
                break;
            }
            }
        }
#endif
        aligned_size += pushRes(getCodeType(ty), arg);
        break;
    }
    return aligned_size;
}

static int push_args(expression_t const * const expr, int param_count) {

    assert( expr->kind == EXPR_CALL);
    int aligned_size = 0;

    aligned_size += push_args2(expr->call.arguments, param_count);

    // If the return type is a large struct/union, the caller passes
    // a pointer to a buffer as if it were the first argument.
    if (expr->call.return_buffer) {
        Smop res;
        if( expr->call.return_buffer->lhs )
            res = var_address(expr->call.return_buffer->lhs);
        else
            res = Code::Reg(types[ptr], Code::RFP,expr->call.return_buffer->offset);
        aligned_size += pushRes(types[ptr], res);
    }

    return aligned_size;
}

static int getParamCount(function_type_t* fn)
{
    int res = 0;
    function_parameter_t * arg = fn->parameters;
    while(arg) {
        res++;
        arg = arg->next;
    }
    return res;
}

static void statement(statement_t *const stmt);

static Smop expression(expression_t * expr)
{
    switch (expr->kind) {
    case EXPR_LITERAL_FLOATINGPOINT: {
        const double d = strtod(expr->literal.value->begin, 0);
        return Code::FImm(getCodeType(expr->base.type),d);
    }
    case EXPR_LITERAL_INTEGER: {
        type_t* type = skip_typeref(expr->base.type);
        if( is_type_signed(type) ) {
            const long long ll = strtoll(expr->literal.value->begin,0,0);
            if( get_ctype_size(type) <= 4 )
                return Code::Imm(getCodeType(expr->base.type),(int)ll);
            else
                return Code::Imm(getCodeType(expr->base.type),ll);
        } else {
            const unsigned long long ull = strtoull(expr->literal.value->begin,0,0);
            if( get_ctype_size(type) <= 4 )
                return Code::UImm(getCodeType(expr->base.type), (unsigned int) ull);
            else
                return Code::UImm(getCodeType(expr->base.type), ull);
        }
    }
    case EXPR_LITERAL_CHARACTER:
        return Code::Imm(getCodeType(expr->base.type),expr->string_literal.value->begin[0]);
    case EXPR_STRING_LITERAL: {
        // NOTE: the type of a EXPR_STRING_LITERAL is POINTER TO CHAR
        std::string name;
        name.resize(10);
        name_hash(expr->string_literal.value->begin, &name[1], name.size()-1);
        name[0] = '.';
        string_decls[name] = expr->string_literal.value->begin;
        return Code::Adr(types[ptr],name);
    }
    case EXPR_ENUM_CONSTANT: {
        ir_tarval* v = expr->reference.entity->enum_value.tv;
        assert(v);
        return Code::Imm(getCodeType(expr->base.type),get_tarval_long(v));
    }
    case EXPR_BINARY_LOGICAL_AND: {
        Smop lhs = expression(expr->binary.left);
        Code::Type type = getCodeType(expr->binary.left->base.type);
        Label lfalse = e->CreateLabel();
        loc(expr->base.pos);
        e->BranchEqual(lfalse,Code::Imm(type,0),e->Convert(type,lhs));
        lhs = Smop(); // release lhs
        Smop rhs = expression(expr->binary.right);
        type = getCodeType(expr->binary.right->base.type);
        loc(expr->base.pos);
        e->BranchEqual(lfalse,Code::Imm(type,0),e->Convert(type,rhs));
        loc(expr->base.pos);
        return e->Set(lfalse,Code::Imm(types[s4],1),Code::Imm(types[s4],0));
    }
    case EXPR_BINARY_LOGICAL_OR: {
        Smop lhs = expression(expr->binary.left);
        Code::Type type = getCodeType(expr->binary.left->base.type);
        Label ltrue = e->CreateLabel();
        loc(expr->base.pos);
        e->BranchNotEqual(ltrue,Code::Imm(type,0),e->Convert(type,lhs));
        lhs = Smop(); // release lhs
        Smop rhs = expression(expr->binary.right);
        type = getCodeType(expr->binary.right->base.type);
        loc(expr->base.pos);
        e->BranchNotEqual(ltrue,Code::Imm(type,0),e->Convert(type,rhs));
        loc(expr->base.pos);
        return e->Set(ltrue,Code::Imm(types[s4],0),Code::Imm(types[s4],1));
    }
    case EXPR_UNARY_COMPLEMENT: {
        Smop tmp = expression(expr->binary.left);
        const Code::Type type = getCodeType(expr->binary.left->base.type);
        loc(expr->base.pos);
        tmp = e->Complement(e->Convert(type,tmp));
        return tmp;
    }
    case EXPR_UNARY_NOT: {
        Smop tmp = expression(expr->binary.left);
        const Code::Type type = getCodeType(expr->binary.left->base.type);

        Label label = e->CreateLabel();
        loc(expr->base.pos);
        e->BranchEqual(label,Code::Imm(type,0),e->Convert(type,tmp));
        loc(expr->base.pos);
        tmp = e->Set(label,Code::Imm(type,0), Code::Imm(type,1));
        return tmp;
    }
    case EXPR_UNARY_NEGATE: {
        Smop tmp = expression(expr->binary.left);
        const Code::Type type = getCodeType(expr->binary.left->base.type);
        loc(expr->base.pos);
        return e->Negate(e->Convert(type,tmp));
    }
    case EXPR_UNARY_PLUS:
        return expression(expr->binary.left);
    case EXPR_BINARY_COMMA: {
        expression(expr->binary.left); // ignore result
        return expression(expr->binary.right);
    }
    case EXPR_CONDITIONAL: {
        Smop cond = expression(expr->conditional.condition);
        const Code::Type type = getCodeType(expr->conditional.condition->base.type);
        Label lelse = e->CreateLabel();
        Label lend = e->CreateLabel();
        loc(expr->base.pos);
        e->BranchEqual(lelse,Code::Imm(type,0),e->Convert(type,cond));
        cond = Smop(); // release cond
        Smop res;
        Smop lhs = expression(expr->conditional.true_expression);
        // apparently C allows x ? (void)a : (void)b or mixed
        if( lhs.model != Code::Operand::Void ) {
            res = e->MakeRegister(lhs);
            e->Fix(res);
        }
        loc(expr->base.pos);
        e->Branch(lend);
        lelse();
        Smop rhs = expression(expr->conditional.false_expression);
        if( rhs.model == Code::Operand::Void || lhs.model == Code::Operand::Void ) {
            if( res.model == Code::Operand::Register )
                e->Unfix(res);
            res = rhs;
        } else {
            rhs = e->Convert(res.type,rhs);
            loc(expr->base.pos);
            e->Move(res,rhs);
            if( res.model == Code::Operand::Register )
                e->Unfix(res);
        }
        lend();
        return res;
    }
    case EXPR_SIZEOF:
        return Code::Imm(types[s4],get_ctype_size(expr->typeprop.type)); // TODO what type has the Imm?
    case EXPR_ALIGNOF:
        return Code::Imm(types[s4],get_ctype_alignment(expr->typeprop.type)); // TODO what type has the Imm?
    case EXPR_UNARY_TAKE_ADDRESS: {
        return lvalue(expr->unary.value);
    }
    case EXPR_UNARY_DEREFERENCE: {
        Smop tmp = expression(expr->unary.value);
        load(expr->base.type, tmp,expr->base.pos);
        return tmp;
    }
    case EXPR_SELECT: {
        Smop tmp = lvalue(expr);
        load(expr->select.compound_entry->declaration.type, tmp, expr->base.pos);

        fetch_bitfield(expr, tmp);

        return tmp;
    }
    case EXPR_REFERENCE: {
        Smop tmp = lvalue(expr);
        load(expr->reference.entity->declaration.type, tmp, expr->base.pos);
        return tmp;
    }
    case EXPR_ARRAY_ACCESS: {
        Smop tmp = lvalue(expr);
        load(expr->base.type, tmp,expr->base.pos);
        return tmp;
    }
    case EXPR_STATEMENT: {
        statement(expr->statement.statement);
    }
    case EXPR_UNARY_CAST: {
        Smop tmp = expression(expr->unary.value);
        type_t *const to_type = skip_typeref(expr->base.type);
        type_t *const from_type  = skip_typeref(expr->unary.value->base.type);
        cast(from_type, to_type, tmp);
        return tmp;
    }
    case EXPR_BINARY_ADD_ASSIGN:
    case EXPR_BINARY_DIV_ASSIGN:
    case EXPR_BINARY_MOD_ASSIGN:
    case EXPR_BINARY_MUL_ASSIGN:
    case EXPR_BINARY_SUB_ASSIGN:
    case EXPR_BINARY_SHIFTLEFT_ASSIGN:
    case EXPR_BINARY_SHIFTRIGHT_ASSIGN:
    case EXPR_BINARY_BITWISE_AND_ASSIGN:
    case EXPR_BINARY_BITWISE_OR_ASSIGN:
    case EXPR_BINARY_BITWISE_XOR_ASSIGN:
    case EXPR_BINARY_ASSIGN: {
        Smop lhs = lvalue(expr->binary.left);
        e->SaveRegister(lhs);
        Smop rhs = expression(expr->binary.right);
        e->RestoreRegister(lhs);

        if( expr->kind != EXPR_BINARY_ASSIGN )
        {
            Smop lhs2 = e->Move(lhs);
            load(expr->binary.left->base.type,lhs2,expr->binary.left->base.pos);
            fetch_bitfield(expr->binary.left, lhs2);
            const int baseSize = scale_for_pointer_arith(expr->kind,lhs2,expr->binary.left->base.type,
                                    rhs, expr->binary.right->base.type);
            const Code::Type lhsT = getCodeType(expr->binary.left->base.type);
            rhs = e->Convert(lhsT,rhs);
            lhs2 = e->Convert(lhsT,lhs2);
            loc(expr->base.pos);
            rhs = binary_ops(expr->kind,lhs2,rhs, baseSize);
        }

        if( store_bitfield(expr->binary.left, lhs, rhs) ) {
            fetch_bitfield(expr->binary.left, rhs);
            return rhs;
            // NOTE: not orig rhs shall be returned according to the standard, but what was actually stored in lhs!
            // gcc effectively seems to consider sign and mem->bit_width; see bitfield-immediate-assign.c
        } else {
            loc(expr->base.pos);
            store(expr->binary.left->base.type, lhs, rhs, expr->binary.left->base.pos);
            return rhs;
        }     
    }
    case EXPR_UNARY_PREFIX_DECREMENT:
    case EXPR_UNARY_PREFIX_INCREMENT: {
        Smop lhs = lvalue(expr->unary.value);
        return prefix_inc_dec(expr->unary.value,lhs,expr->kind == EXPR_UNARY_PREFIX_INCREMENT, 0);
    }
    case EXPR_UNARY_POSTFIX_DECREMENT:
    case EXPR_UNARY_POSTFIX_INCREMENT: {
        // Convert i++ to `(typeof i)((i += 1) - 1)`
        Smop lhs = lvalue(expr->unary.value);
        if( skip_typeref(expr->unary.value->base.type)->kind == TYPE_POINTER ||
                !(expr->unary.value->kind == EXPR_SELECT &&
                            expr->unary.value->select.compound_entry->compound_member.bitfield) )
        {
            // for pointers and normal integers, we just keep the original value
            // keep the old value for returning
            Smop ret = prefix_inc_dec(expr->unary.value,lhs,expr->kind == EXPR_UNARY_POSTFIX_INCREMENT, 1);
            return ret;
        }else
        {
            // for bitfields we use the effectively stored value in the bitfield and invert the
            // operation on this value (because it over or underflows differently than a normal int).
            assert(expr->unary.value->kind == EXPR_SELECT &&
                   expr->unary.value->select.compound_entry->compound_member.bitfield);
            lhs = prefix_inc_dec(expr->unary.value,lhs,expr->kind == EXPR_UNARY_PREFIX_INCREMENT, 0);
            fetch_bitfield(expr->unary.value, lhs);
            const int off = expr->kind == EXPR_UNARY_PREFIX_INCREMENT ? -1 : 1;
            lhs = e->Add(lhs, Code::Imm(lhs.type,off));
            return lhs;
        }
    }
    case EXPR_CALL: {
        const RestoreRegisterState restore(*e);

        function_type_t * function_type = expr->call.concrete_type;
        if (function_type == NULL) {
            type_t *type = skip_typeref(expr->call.function->base.type);
            assert(is_type_pointer(type));
            type_t         *points_to    = skip_typeref(type->pointer.points_to);
            assert(is_type_function(points_to));
            function_type = &points_to->function;
        }

        type_t* ret = 0;
        if( function_type->return_type ) {
            ret = skip_typeref(function_type->return_type);
            if( ret->kind == TYPE_VOID )
                ret = 0;
        }

        const int aligned_size = push_args(expr,getParamCount(function_type));
        Smop f = expression(expr->call.function);
        f = e->Convert(types[fun],f);

        Smop res;
        loc(expr->base.pos);
        if( expr->call.return_buffer )
        {
            e->Call(f,aligned_size);
            if( expr->call.return_buffer->lhs )
                res = var_address(expr->call.return_buffer->lhs);
            else
                res = Code::Reg(types[ptr], Code::RFP,expr->call.return_buffer->offset);
        }else if( ret )
        {
            res = e->Call(getCodeType(ret), f,aligned_size);

        }else
            e->Call(f,aligned_size);

        return res;
    }
    case EXPR_FUNCNAME: {
        const char* in = "";
        if( func_name )
            in = func_name->string;
        std::string name;
        name.resize(10);
        name_hash(in, &name[1], name.size()-1);
        name[0] = '.';
        string_decls[name] = in;
        return Code::Adr(types[ptr],name);
    }
    case EXPR_COMPOUND_LITERAL:
        return lvalue(expr);

    case EXPR_LABEL_ADDRESS:
    case EXPR_VA_ARG:   // expr->va_arge
    case EXPR_VA_COPY:  // expr->va_copye
    case EXPR_VA_START: // expr->va_starte

    default:
        panic("expression kind not yet implemented: %d", expr->kind);

    case EXPR_BUILTIN_CONSTANT_P:
    case EXPR_BUILTIN_TYPES_COMPATIBLE_P:
    case EXPR_CLASSIFY_TYPE:
    case EXPR_OFFSETOF:
    case EXPR_ERROR:

    case EXPR_UNARY_ASSUME:  // expr->unary.value
    case EXPR_UNARY_DELETE:
    case EXPR_UNARY_DELETE_ARRAY:
    case EXPR_UNARY_THROW:
    case EXPR_UNARY_IMAG:
    case EXPR_UNARY_REAL:

    case EXPR_BINARY_ISGREATER: // these are GNU builtins
    case EXPR_BINARY_ISGREATEREQUAL:
    case EXPR_BINARY_ISLESS:
    case EXPR_BINARY_ISLESSEQUAL:
    case EXPR_BINARY_ISLESSGREATER:
    case EXPR_BINARY_ISUNORDERED:
        panic("expression kind not supported: %d", expr->kind);

    case EXPR_BINARY_ADD:
    case EXPR_BINARY_SUB:
    case EXPR_BINARY_MUL:
    case EXPR_BINARY_DIV:
    case EXPR_BINARY_MOD:
    case EXPR_BINARY_BITWISE_AND:
    case EXPR_BINARY_BITWISE_OR:
    case EXPR_BINARY_BITWISE_XOR:
    case EXPR_BINARY_EQUAL:
    case EXPR_BINARY_GREATER:
    case EXPR_BINARY_GREATEREQUAL:
    case EXPR_BINARY_LESS:
    case EXPR_BINARY_LESSEQUAL:
    case EXPR_BINARY_NOTEQUAL:
    case EXPR_BINARY_SHIFTLEFT:
    case EXPR_BINARY_SHIFTRIGHT:
        break; // implemented below
    }

    Smop lhs = expression(expr->binary.left);
    e->SaveRegister(lhs);
    Smop rhs = expression(expr->binary.right);
    e->RestoreRegister(lhs);

    const Code::Type lhsT = getCodeType(expr->binary.left->base.type);

    rhs = e->Convert(lhsT,rhs);
    lhs = e->Convert(lhsT,lhs);

    const int baseSize = scale_for_pointer_arith(expr->kind,lhs,expr->binary.left->base.type,
                            rhs, expr->binary.right->base.type);
    loc(expr->base.pos);
    return binary_ops(expr->kind,lhs,rhs,baseSize);
}

static void statement(statement_t *const stmt);
static void compound_statement_to_ir(compound_statement_t *compound)
{
    // create_local_declarations(compound->scope.first_entity);

    statement_t *stmt = compound->statements;
    for ( ; stmt != NULL; stmt = stmt->base.next) {
        statement(stmt);
    }
}

static int firstParamOffset();

// copy struct pointed to by $0 to the local var at offset
static void copy_struct_mem(const Smop& reg) {
    assert( return_type != 0 );

    e->Copy(Code::Mem(types[ptr],Code::RFP, firstParamOffset() ),
                                            // the pointer to result is the first (invisible) param
            reg,Code::Imm(types[ptr],get_ctype_size(return_type)));
}

static void statement(statement_t *const stmt)
{
    switch (stmt->kind) {
    case STATEMENT_COMPOUND:
        compound_statement_to_ir(&stmt->compound);
        return;
    case STATEMENT_EMPTY:
        return; /* nothing */
    case STATEMENT_DECLARATION:
        for( entity_t* decl = stmt->declaration.declarations_begin; decl; decl = decl->base.next )
        {
            if( decl->kind == ENTITY_VARIABLE && decl->variable.is_local && decl->variable.initializer )
            {
                loc(stmt->base.pos);
                type_t* type = skip_typeref(decl->declaration.type);
                // If a partial initializer list is given, the standard requires
                // that unspecified elements are set to 0. Here, we simply
                // zero-initialize the entire memory region of a variable before
                // initializing it with user-supplied values.
                Smop lhs (Code::Reg(types[ptr],Code::RFP,decl->variable.offset));
                Fill(type,lhs);

                run_initializer(type, std::string(), decl->variable.offset, decl->variable.initializer);
            }
            if( decl == stmt->declaration.declarations_end )
                break;
        }
        return;
    case STATEMENT_EXPRESSION:
        expression(stmt->expression.expression);
        return;
    case STATEMENT_IF: {
        Smop cond = expression(stmt->ifs.condition);
        const Code::Type type = getCodeType(stmt->ifs.condition->base.type);
        Label lelse = e->CreateLabel();
        Label lend = e->CreateLabel();
        e->BranchEqual(lelse,Code::Imm(type,0),e->Convert(type,cond));
        cond = Smop(); // release register
        statement(stmt->ifs.true_statement);
        e->Branch(lend);
        lelse();
        if (stmt->ifs.false_statement)
            statement(stmt->ifs.false_statement);
        lend();
        return;
    }
    case STATEMENT_SWITCH: {
        Smop cond = expression(stmt->switchs.expression);

        const Code::Type cond_type = getCodeType(stmt->switchs.expression->base.type);

        std::deque<Label> case_target_labels; // marks the statement to be executed when a case is hit
        for (case_label_statement_t *n = stmt->switchs.first_case; n; n = n->next) {
            if( n == stmt->switchs.default_label )
                continue;
            case_target_labels.push_back(e->CreateLabel());
            n->target = &case_target_labels.back();
            if (n->first_case == n->last_case) {
                // normal case, there is only one value (n->first_case) for the case.
                e->BranchEqual(case_target_labels.back(),Code::Imm(cond_type,get_tarval_long(n->first_case)),
                               e->Convert(cond_type,cond));
                continue;
            }

            // [GNU] Case ranges; special case
            cond = e->Convert(cond_type,cond);
            cond = e->Subtract(cond, Code::Imm(cond_type,get_tarval_long(n->first_case)));
            e->BranchGreaterEqual(case_target_labels.back(),cond, Code::Imm(cond_type,
                                 get_tarval_long(n->last_case) - get_tarval_long(n->first_case)));
        }
        cond = Smop(); // release register

        if (stmt->switchs.default_label)
        {
            case_target_labels.push_back(e->CreateLabel());
            stmt->switchs.default_label->target = &case_target_labels.back();
            e->Branch(case_target_labels.back());
        }

        Label lbreak = e->CreateLabel();
        break_target_labels.push_back(&lbreak);
        e->Branch(lbreak);
        statement(stmt->switchs.body);
        lbreak();
        break_target_labels.pop_back();
        return;
    }
    case STATEMENT_CASE_LABEL: {
        Label* lbl = (Label*)stmt->case_label.target;
        assert(lbl != 0);
        (*lbl)();
        statement(stmt->case_label.statement);
        return;
    }
    case STATEMENT_DO_WHILE: {
        Label lbegin = e->CreateLabel();
        Label lbreak = e->CreateLabel();
        break_target_labels.push_back(&lbreak);
        Label lcont = e->CreateLabel();
        continue_target_label.push_back(&lcont);
        lbegin();
        statement(stmt->do_while.body);
        lcont();
        Smop cond = expression(stmt->do_while.condition);
        const Code::Type type = getCodeType(stmt->do_while.condition->base.type);
        e->BranchNotEqual(lbegin,Code::Imm(type,0),e->Convert(type,cond));
        lbreak();
        break_target_labels.pop_back();
        continue_target_label.pop_back();
        return;
    }
    case STATEMENT_FOR: {
        if (stmt->fors.initialisation)
            expression(stmt->fors.initialisation);
        Label lbegin = e->CreateLabel();
        Label lbreak = e->CreateLabel();
        break_target_labels.push_back(&lbreak);
        Label lcont = e->CreateLabel();
        continue_target_label.push_back(&lcont);
        lbegin();
        if (stmt->fors.condition) {
            Smop cond = expression(stmt->fors.condition);
            const Code::Type type = getCodeType(stmt->fors.condition->base.type);
            e->BranchEqual(lbreak,Code::Imm(type,0),e->Convert(type,cond));
        }
        statement(stmt->fors.body);
        lcont();
        if (stmt->fors.step)
            expression(stmt->fors.step);
        e->Branch(lbegin);
        lbreak();
        break_target_labels.pop_back();
        continue_target_label.pop_back();
        return;
    }
    case STATEMENT_BREAK: {
        loc(stmt->base.pos);
        e->Branch(*break_target_labels.back());
        return;
    }
    case STATEMENT_CONTINUE: {
        loc(stmt->base.pos);
        e->Branch(*continue_target_label.back());
        return;
    }
    case STATEMENT_RETURN: {
        if (stmt->returns.value) {
            Smop lhs = expression(stmt->returns.value);
            type_t* type = skip_typeref(stmt->returns.value->base.type);
            switch (type->kind) {
            case TYPE_COMPOUND_STRUCT:
            case TYPE_COMPOUND_UNION:
                loc(stmt->base.pos);
                copy_struct_mem(lhs);
                break;
            case TYPE_VOID:
                break;
            default: {
                Code::Type lhsT = getCodeType(stmt->returns.value->base.type);
                loc(stmt->base.pos);
                e->Move (Code::Reg(lhsT, Code::RRes), e->Convert(lhsT,lhs));
                break;
            }
            }
        }
        assert( end_of_function_label != nullptr );
        loc(stmt->base.pos);
        e->Branch(*end_of_function_label);
        return;
    }
    case STATEMENT_LABEL: {
        label_t* lbl = stmt->label.label;
        if(lbl->target == 0)
        {
            goto_target_labels.push_back(e->CreateLabel());
            lbl->target = &goto_target_labels.back();
            goto_target_labels.back()();
        }else {
            Label* l = (Label*)lbl->target;
            (*l)();
        }
        statement(stmt->label.statement);
        return;
    }
    case STATEMENT_GOTO: {
        label_t* lbl = stmt->gotos.label;
        if(lbl->target == 0)
        {
            goto_target_labels.push_back(e->CreateLabel());
            lbl->target = &goto_target_labels.back();
            loc(stmt->base.pos);
            e->Branch(goto_target_labels.back());
        }else {
            Label* l = (Label*)lbl->target;
            loc(stmt->base.pos);
            e->Branch(*l);
        }
        return;
    }
    case STATEMENT_ASM: {
        loc(stmt->base.pos);
        try {
            e->AssembleInlineCode(current_source_file,stmt->base.pos.lineno,stmt->asms.asm_text->begin);
        }catch(...) {}
        return;
    }
    case STATEMENT_COMPUTED_GOTO: // stmt->computed_goto
    case STATEMENT_ERROR:
    default:
        panic("statement not yet implemented: %d", stmt->kind);
    }
}

static int firstParamOffset()
{
    return 2 * target_stack_align(); // previous frame and return address;
}

static bool is_main(entity_t const *const entity)
{
    static symbol_t *sym_main = NULL;
    if (sym_main == NULL) {
        sym_main = symbol_table_insert("main");
    }

    if (entity->base.symbol != sym_main)
        return false;
    /* must be in outermost scope */
    if (entity->base.parent_scope != &current_translation_unit->scope)
        return false;

    return true;
}

static void assign_local_variable_offsets2(entity_t *entity, entity_t * last, void* payload )
{
    int* bottom = (int*)payload;

    entity_t * end = last != NULL ? last->base.next : NULL;
    for (; entity != end; entity = entity->base.next) {
        if ( entity->kind == ENTITY_VARIABLE && entity->variable.base.storage_class != STORAGE_CLASS_STATIC ) {
            type_t *type = skip_typeref(entity->declaration.type);

            *bottom += get_ctype_size(type);
            *bottom = align_to(*bottom, get_ctype_alignment(type));
            entity->variable.offset = -(*bottom);
            entity->variable.is_local = true;
        }
        if ( entity->kind == ENTITY_VARIABLE && entity->variable.base.storage_class == STORAGE_CLASS_STATIC )
            static_locals.push_back(entity);
    }
}

static void assign_compound_literal_offsets(expression_t* expr, void *payload)
{
    int* bottom = (int*)payload;

    if( expr->kind == EXPR_COMPOUND_LITERAL && !expr->compound_literal.global_scope )
    {
        type_t *type = skip_typeref(expr->compound_literal.type);

        *bottom += get_ctype_size(type);
        *bottom = align_to(*bottom, get_ctype_alignment(type));
        expr->compound_literal.id = -(*bottom);
    }
}

static void assign_local_variable_offsets(statement_t *stmt, void * payload)
{
    // TODO: check for return_buffers and possible lhs entities to avoid copying
    switch (stmt->kind) {
    case STATEMENT_DECLARATION: {
        const declaration_statement_t *const decl_stmt = &stmt->declaration;
        assign_local_variable_offsets2(decl_stmt->declarations_begin,
                                        decl_stmt->declarations_end, payload);
        break;
    }

    case STATEMENT_FOR:
        assign_local_variable_offsets2(stmt->fors.scope.first_entity, NULL, payload);
        break;

    default:
        break;
    }
}

// Assign offsets to local variables and collect static variables.
static void assign_lvar_offsets(function_t *const function) {

    int top = firstParamOffset();
    int bottom = 0;

    type_t *type = skip_typeref(function->base.type);
    assert(is_type_function(type));
    type_t *const return_type = skip_typeref(type->function.return_type);

    if( return_type && is_type_compound(return_type) )
        top += MAX(target_stack_align(), target_pointer_width());
        // if fn has struct return, the first param is a pointer to result


    if( is_main((entity_t const*)function) )
    {
        // redeclare params of main as locals (will be set to values of _argc and _argv globals)
        for (entity_t *parameter = function->parameters.first_entity;
             parameter != NULL; parameter = parameter->base.next) {
            if (parameter->kind != ENTITY_PARAMETER)
                continue;
            type_t *type = skip_typeref(parameter->declaration.type);
            bottom += get_ctype_size(type);
            bottom = align_to(bottom, get_ctype_alignment(type));
            parameter->variable.offset = -bottom;
        }
    }else
    {
        // Assign offsets to parameters.
        for (entity_t *parameter = function->parameters.first_entity;
             parameter != NULL; parameter = parameter->base.next) {
            if (parameter->kind != ENTITY_PARAMETER)
                continue;
            type_t *type = skip_typeref(parameter->declaration.type);
            top = align_to(top, target_stack_align());
            parameter->variable.offset = top;
            top += get_ctype_size(type);
        }
    }

    // Assign offsets to local variables.
    walk_statements_and_expressions(function->body, assign_local_variable_offsets,
                                    assign_compound_literal_offsets, &bottom);

    // provide for storage space for union/struct return types
    return_buffer_t* return_buffer = function->return_buffers;
    while(return_buffer)
    {
        if( return_buffer->lhs == 0 )
        {
            bottom += get_ctype_size(return_buffer->type);
            bottom = align_to(bottom, get_ctype_alignment(return_buffer->type));
            return_buffer->offset = -bottom;
        }
        return_buffer = return_buffer->next;
    }

    function->stack_size = align_to(bottom, target_stack_align());
}

static void print_type_decl(type_t* ty, bool type_section);

static void print_member(entity_t* m)
{
    assert(m && m->kind == ENTITY_COMPOUND_MEMBER);

    type_t* type = skip_typeref(m->declaration.type);
    if( m->base.symbol == 0 && (is_type_compound(type)) )
    {
        // anonymous struct or union
        for (entity_t *mem = type->compound.compound->members.first_entity;
             mem != NULL; mem = mem->base.next)
        {
            if (mem->kind != ENTITY_COMPOUND_MEMBER)
                continue;
            print_member(mem);
        }
        return;
    }
    if( m->base.symbol == 0 )
    {
        return; // anonymous member of basic type, apparently legal
    }
    std::string name(m->base.symbol->string);
    if( m->compound_member.bitfield )
    {
        uint64_t pat = 0;
        for( int i = 0; i < m->compound_member.bit_size; i++ )
        {
            if( i != 0 )
                pat <<= 1;
            pat |=  1;
        }
        pat <<= m->compound_member.bit_offset;
        if( (m->compound_member.bit_size + m->compound_member.bit_offset) > 32 )
            e->DeclareField(name,m->compound_member.offset,Code::UImm(types[u8],pat));
        else
            e->DeclareField(name,m->compound_member.offset,Code::UImm(types[u4],pat));
    }else
        e->DeclareField(name,m->compound_member.offset,Code::Imm(types[ptr],0));
    e->Locate(m->base.pos.input_name,toPos(m->base.pos.lineno,m->base.pos.colno));
    print_type_decl(type,false);
}

static void print_type_decl(type_t* ty, bool type_section)
{
    ty = skip_typeref(ty);
    switch(ty->kind)
    {
    case TYPE_VOID:
        e->DeclareVoid();
        break;
    case TYPE_ATOMIC:
    case TYPE_ENUM:
        e->DeclareType(std::string(ecsTypes[getTypeId(ty)].dbgname));
        break;
    case TYPE_POINTER:
        e->DeclarePointer();
        print_type_decl(ty->pointer.points_to,false);
       break;
    case TYPE_FUNCTION: {
        Label ext = e->CreateLabel();
        e->DeclareFunction(ext);
        print_type_decl(ty->function.return_type,0);
        function_parameter_t* param = ty->function.parameters;
        while(param)
        {
            print_type_decl(param->type,false);
            param = param->next;
        }
        ext();
        break;
    }
    case TYPE_ARRAY:
        e->DeclareArray(0,ty->array.size);
        print_type_decl(ty->array.element_type,false);
        break;
    case TYPE_COMPOUND_STRUCT:
    case TYPE_COMPOUND_UNION: {
        if( type_section || ty->compound.compound->base.symbol == 0 )
        {
            Label ext = e->CreateLabel();
            e->DeclareRecord(ext,get_ctype_size(ty));
            for (entity_t *mem = ty->compound.compound->members.first_entity;
                 mem != NULL; mem = mem->base.next)
            {
                if (mem->kind != ENTITY_COMPOUND_MEMBER)
                    continue;
                print_member(mem);
            }
            ext();
        }else
        {
            to_declare.insert(ty);
            entity_base_t* base = &ty->compound.compound->base;
            // only global entities have base->parent_entity != 0
            // otherwise we have to scope
#ifdef __ECS_DUPLICATE_ISSUE__
            const std::string name = rename2(base,1);
#else
            const std::string name = rename2(base,base->parent_entity != 0);
#endif
            e->DeclareType(name);
        }
        break;
    }
    default:
        assert(0);
    }
}

static void print_var_name(entity_t *var)
{
    e->DeclareSymbol(*end_of_function_label,var->base.symbol->string,
                     Code::Mem(types[ptr],Code::RFP, var->variable.offset));
    e->Locate(var->base.pos.input_name,toPos(
                  var->base.pos.lineno,var->base.pos.colno));
    print_type_decl(var->declaration.type,false);
}

static void print_local_variable_names2(entity_t *entity, entity_t * last, void* payload )
{
    entity_t * end = last != NULL ? last->base.next : NULL;
    for (; entity != end; entity = entity->base.next) {
        if ( entity->kind == ENTITY_VARIABLE && entity->variable.is_local ) {
            print_var_name(entity);
        }
    }
}

static void print_local_variable_names(statement_t *stmt, void * payload)
{
    switch (stmt->kind) {
    case STATEMENT_DECLARATION: {
        const declaration_statement_t *const decl_stmt = &stmt->declaration;
        print_local_variable_names2(decl_stmt->declarations_begin,
                                        decl_stmt->declarations_end, payload);
        break;
    }
    case STATEMENT_FOR:
        print_local_variable_names2(stmt->fors.scope.first_entity, NULL, payload);
        break;
    default:
        break;
    }
}

static void create_function(function_t * function)
{
    if (function->body == NULL)
        return;

    // No code is emitted for "static inline" functions
    // if no one is referencing them.
    if (!function->base.used && function->base.storage_class == STORAGE_CLASS_STATIC)
        return;

    return_type = 0;
    func_name = ((entity_t*)function)->declaration.base.symbol;

    assign_lvar_offsets(function);

    // NOTE: static is not supported by ECS; therefore getName provides some unique mangling
    e->Begin(Code::Section::Code, rename((entity_t*)function) );

    type_t* ft = function->base.type;
    assert(is_type_function(ft));

    if( ft->function.return_type && ft->function.return_type->kind != TYPE_VOID )
        return_type = skip_typeref(ft->function.return_type);

    goto_target_labels.clear();
    Label lret = e->CreateLabel();
    end_of_function_label = &lret;

    if( target.debug_info )
    {
        e->Locate(function->base.base.pos.input_name,toPos(
                      function->base.base.pos.lineno,function->base.base.pos.colno));
        if( return_type )
        {
            if( return_type->kind != TYPE_VOID )
                e->DeclareType(getCodeType(return_type));
            else
                e->DeclareVoid();
        }else
            e->DeclareVoid();
        for (entity_t *parameter = function->parameters.first_entity;
             parameter != NULL; parameter = parameter->base.next) {
            if (parameter->kind != ENTITY_PARAMETER)
                continue;
            print_var_name(parameter);
        }
        walk_statements(function->body, print_local_variable_names, 0);
    }

    const bool ismain = is_main((entity_t*)function);

    // Prologue
    if( !ismain && target_has_linkregister() )
        e->Push(Code::Reg(types[fun],Code::RLink));
    e->Enter(function->stack_size);

    if( ismain )
    {
        if( return_type && return_type->kind != TYPE_VOID &&
                return_type->kind != TYPE_ATOMIC &&
                return_type->atomic.akind != ATOMIC_TYPE_INT )
            panic("return type of function main must be void or int");
        int p = 0;
        // initialize the parameter substitutes with the corresponding global var
        for (entity_t *var = function->parameters.first_entity; var != NULL; var = var->base.next, p++) {
            if (var->kind != ENTITY_PARAMETER)
                continue;
            type_t *type = skip_typeref(var->declaration.type);
            switch( p )
            {
            case 0:
                // argc
                if( type->kind != TYPE_ATOMIC && type->atomic.akind != ATOMIC_TYPE_INT )
                    panic("first parameter of function main must be of int type");
                e->Move(e->MakeMemory(getCodeType(type),
                                      Code::Reg(types[ptr],Code::RFP, var->variable.offset)),
                        Code::Mem(getCodeType(type),"_argc"));
                break;
            case 1:
                // argv
                if( type->kind != TYPE_POINTER )
                    panic("second parameter of function main must be of pointer type");
                e->Move(e->MakeMemory(types[ptr], Code::Reg(types[ptr],Code::RFP, var->variable.offset)),
                        Code::Mem(types[ptr],"_argv"));
                break;
            default:
                panic("function main has either none or two paramters");
                break;
            }
        }
    }
    statement(function->body);

    // Epilogue
    lret();
    if( return_type && is_type_compound(return_type) )
        e->Move(Code::Reg(types[s4],Code::RRes),Code::Imm(types[s4],0));

    e->Leave();
    if( ismain )
    {
        e->Push(Code::Reg(types[s4], Code::RRes));
        e->Call(Code::Adr(types[fun],"_Exit"),0);
    }else
        e->Return();
    end_of_function_label = 0;
    goto_target_labels.clear();
    return_type = 0;
    func_name = 0;
}

static bool declaration_is_definition(const entity_t *entity)
{
    switch (entity->kind) {
    case ENTITY_VARIABLE:
        return entity->declaration.storage_class != STORAGE_CLASS_EXTERN
            || entity->variable.alias.entity != NULL;
    case ENTITY_FUNCTION:
        return entity->function.body != NULL
            || entity->function.alias.entity != NULL;
    case ENTITY_PARAMETER:
    case ENTITY_COMPOUND_MEMBER:
        return false;
    case ENTITY_ASM_ARGUMENT:
    case ENTITY_ASM_LABEL:
    case ENTITY_CLASS:
    case ENTITY_ENUM:
    case ENTITY_ENUM_VALUE:
    case ENTITY_LABEL:
    case ENTITY_LOCAL_LABEL:
    case ENTITY_NAMESPACE:
    case ENTITY_STRUCT:
    case ENTITY_TYPEDEF:
    case ENTITY_UNION:
        break;
    }
    panic("entity is not a declaration");
}

static bool is_decl_necessary(entity_t const *const entity)
{
    assert(is_declaration(entity));
    declaration_t const *const decl = &entity->declaration;
    return
        decl->used ||
        (declaration_is_definition(entity) &&
         (decl->storage_class != STORAGE_CLASS_STATIC || decl->modifiers & DM_USED));
}

static std::pair<entity_t*,int> find_next_member_imp(bool lhs_is_compound, type_t* compound, entity_t *cur, bool& active)
{
    assert(is_type_compound(compound));
    if( cur == 0 )
        active = true;
    for(entity_t *mem = compound->compound.compound->members.first_entity; mem != NULL; mem = mem->base.next)
    {
        if (mem->kind != ENTITY_COMPOUND_MEMBER)
            continue;
        if( mem == cur )
        {
            active = true;
            if( compound->kind == TYPE_COMPOUND_UNION )
                return std::pair<entity_t*,int>(0,0); // we only want to see the first element of a union
            continue;
        }
        type_t* memtype = skip_typeref(mem->declaration.type);
        if( active && mem->base.symbol != 0 && ( !is_type_compound(memtype) || lhs_is_compound ) )
            return std::pair<entity_t*,int>(mem,0);
        if( is_type_compound(memtype) )
        {
            std::pair<entity_t*,int> mem2 = find_next_member_imp(lhs_is_compound, memtype, cur, active);
            if( mem2.first )
                return std::pair<entity_t*,int>(mem2.first, mem2.second + mem->compound_member.offset);
        }
    }
    return std::pair<entity_t*,int>(0,0);
}

static std::pair<entity_t*,int> find_next_member(bool lhs_is_compound, type_t* compound, entity_t *cur)
{
    bool active = false;
    return find_next_member_imp(lhs_is_compound, compound, cur, active);
}

#ifdef ECS_MEMBER_BY_INDEX
static entity_t* find_member_by_idx_imp(compound_t* compound, int n, int& i)
{
    for(entity_t *mem = compound->members.first_entity; mem != NULL; mem = mem->base.next)
    {
        if (mem->kind != ENTITY_COMPOUND_MEMBER)
            continue;
        type_t* memtype = skip_typeref(mem->declaration.type);
        if( i == n && mem->base.symbol != 0 && !is_type_compound(memtype) )
            return mem;
        if( is_type_compound(memtype) )
        {
            entity_t *mem2 = find_member_by_idx_imp(memtype->compound.compound, n, i);
            if( mem2 )
                return mem2;
        }
        if( mem->base.symbol != 0 && !is_type_compound(memtype) )
            i++; // only count passing valid candidates
    }
    return 0;
}

static entity_t* find_member_by_idx(compound_t* compound, int n)
{
    int i = 0;
    return find_member_by_idx_imp(compound, n, i);
}
#endif

std::pair<entity_t*,int> find_member_by_name(compound_t *compound, symbol_t *symbol)
{
    for (entity_t *iter = compound->members.first_entity; iter != NULL;
         iter = iter->base.next) {
        if (iter->kind != ENTITY_COMPOUND_MEMBER)
            continue;

        if (iter->base.symbol == symbol) {
            return std::pair<entity_t*,int>(iter,0);
        } else if (iter->base.symbol == NULL) {
            /* search in anonymous structs and unions */
            type_t *type = skip_typeref(iter->declaration.type);
            if (is_type_compound(type)) {
                std::pair<entity_t*,int> iter2 = find_member_by_name(type->compound.compound, symbol);
                if( iter2.first )
                    return std::pair<entity_t*,int>(iter2.first,iter2.second + iter->compound_member.offset);
            }
        }
    }
    return std::pair<entity_t*,int>(0,0);
}

static int get_idx_of_member(compound_t* compound, entity_t* m)
{
    int i = 0;
    for (entity_t *mem = compound->members.first_entity; mem != NULL; mem = mem->base.next, i++)
    {
        if( m == mem )
            return i;
    }
    return -1;
}

static Smop makeLhsMem(Code::Type type, const std::string& name, int offset)
{
    if( !name.empty() )
        return Code::Mem(type,name,offset);
    else
        return e->MakeMemory(type, Code::Reg(types[ptr],Code::RFP, offset));
}

static inline Smop makeLhsAdr(const std::string& name, int offset)
{
    if( !name.empty())
        return Code::Adr(types[ptr],name, offset);
    else
        return Code::Reg(types[ptr],Code::RFP, offset);
}

static void run_value(type_t* type, const std::string& name, int offset, initializer_t *initializer)
{
    assert(initializer->kind == INITIALIZER_VALUE);
    // a single expression can initialize a scalar, an char array or a struct/union
    if( type->kind == TYPE_ATOMIC || type->kind == TYPE_POINTER || type->kind == TYPE_ENUM ) {
        // NOTE char str[] = "..."; is handled in INITIALIZER_STRING
        Smop v = expression(initializer->value.value);
        e->Move(makeLhsMem(v.type,name,offset), v);
    }else if( type->kind == TYPE_COMPOUND_UNION ) {
        std::pair<entity_t*,int> mem = find_member_by_name(type->compound.compound,0);
        assert(mem.first && mem.first->kind == ENTITY_COMPOUND_MEMBER);
        Smop v = expression(initializer->value.value);
        e->Move(makeLhsMem(v.type,name,offset + mem.first->compound_member.offset + mem.second), v);
    }else if( type->kind == TYPE_COMPOUND_STRUCT ) {
        // a single expression that has compatible structure or union type, e.g. *struct_ptr
        Smop rhs = expression(initializer->value.value);

        store(type, makeLhsAdr(name,offset), rhs, initializer->base.pos);
        // instead of e->Move(to(v.type,name,offset), v);
    }else
        panic("INITIALIZER_VALUE for given type not yet implemented: %d", type->kind);
}

static void run_string(type_t* type, const std::string& name, int offset, initializer_t *initializer)
{
    assert(initializer->kind == INITIALIZER_STRING);
    assert( type->kind == TYPE_ARRAY && type->array.size );
    assert( initializer->value.value->kind == EXPR_STRING_LITERAL );
    Smop str = expression(initializer->value.value);
    Smop to;
    if( !name.empty() )
        to = Code::Adr(types[ptr],name,offset);
    else
        to = Code::Reg(types[ptr],Code::RFP, offset);
    e->Copy(to, str, Code::Imm(types[ptr],initializer->value.value->string_literal.value->size));
}

static void run_list_compound_init(type_t* type, const std::string& name, int& offset, initializer_t *list, int& lIdx);

static void run_list_array_init(type_t* type, const std::string& name, int& offset, initializer_t *list, int& lIdx, int max)
{
    assert( type->kind == TYPE_ARRAY );
    assert( list->kind == INITIALIZER_LIST );

    type_t* et = skip_typeref(type->array.element_type);
    int arrIdx = 0;
    int off = offset;
    while( lIdx < list->list.len )
    {
        if( max && arrIdx >= max ) {
            offset += get_ctype_size(type);
            return;
        }

        initializer_t* cur = list->list.initializers[lIdx];
        if( cur->kind == INITIALIZER_VALUE )
        {
            if( is_type_array(et) )
            {
                run_list_array_init(et,name,off,list,lIdx, et->array.size);
            }else if( is_type_compound(et) )
            {
                run_list_compound_init(et,name, off, list, lIdx);
            }else
            {
                run_initializer(et, name, off, cur);
                off += get_ctype_size(et);
                lIdx++;
            }
        }else if( cur->kind == INITIALIZER_LIST || cur->kind == INITIALIZER_STRING )
        {
            run_initializer(et, name, off, cur);
            off += get_ctype_size(et);
            lIdx++; // this consumes exactly one element of list
        }else if( cur->kind == INITIALIZER_DESIGNATOR )
        {
            assert( cur->designator.designator->array_index );
            ir_tarval * v = fold_expression(cur->designator.designator->array_index);
            assert(v);
            arrIdx = get_tarval_long(v);
            lIdx++;
            assert(lIdx < list->list.len);
            cur = list->list.initializers[lIdx];
            const int sz = get_ctype_size(et);
            off = offset + arrIdx * sz;
            run_initializer(et, name, off, cur);
            off += sz;
            lIdx++;
        }else
            panic("INITIALIZER_LIST not yet implemented for array element initializer %d", cur->kind);
        arrIdx++;
    }
    offset += get_ctype_size(type);
}

static void run_list_compound_init(type_t* type, const std::string& name, int& offset, initializer_t *list, int& lIdx)
{
    assert( type->kind == TYPE_COMPOUND_STRUCT || type->kind == TYPE_COMPOUND_UNION );
    assert( list->kind == INITIALIZER_LIST );

    // a struct or union is initialized by a list
    entity_t* mem = 0;
    while( lIdx < list->list.len )
    {
        initializer_t* cur = list->list.initializers[lIdx];
        if( cur->kind == INITIALIZER_VALUE )
        {
            bool lhs_is_compound = is_type_compound(skip_typeref(cur->value.value->base.type));
            std::pair<entity_t*,int> res = find_next_member(lhs_is_compound, type, mem);
            mem = res.first;
            if( mem == 0 ) {
                offset += get_ctype_size(type);
                return; // we reached the end of the struct and don't need more list elements
            }
            assert(mem && mem->kind == ENTITY_COMPOUND_MEMBER);
            type_t* mt = skip_typeref(mem->declaration.type);
            int off = offset + mem->compound_member.offset + res.second;
            if( is_type_array(mt) )
            {
                run_list_array_init(mt,name,off,list,lIdx, mt->array.size);
            }else if( is_type_compound(mt) )
            {
                run_list_compound_init(mt,name, off, list, lIdx);
            }else if( mem->compound_member.bitfield )
            {
                Smop rhs = expression(cur->value.value);
                store_bitfield_imp(mem, makeLhsAdr(name, off), rhs, cur->base.pos);
                lIdx++;
            }else{
                run_initializer(mt, name, off, cur);
                lIdx++;
            }
        }else if(cur->kind == INITIALIZER_LIST)
        {
            std::pair<entity_t*,int> res = find_next_member(true, type, mem);
            mem = res.first;
            if( mem == 0 ) {
                offset += get_ctype_size(type);
                return; // we reached the end of the struct and don't need more list elements
            }
            assert(mem && mem->kind == ENTITY_COMPOUND_MEMBER);
            run_initializer(skip_typeref(mem->declaration.type), name,
                            offset + mem->compound_member.offset + res.second, cur);
            lIdx++;
        }else if( cur->kind == INITIALIZER_DESIGNATOR )
        {
            std::pair<entity_t*,int> res = find_member_by_name(type->compound.compound,
                                                               cur->designator.designator->symbol);
            mem = res.first;
            assert(mem && mem->kind == ENTITY_COMPOUND_MEMBER);
            lIdx++;
            assert(lIdx < list->list.len);
            cur = list->list.initializers[lIdx];
            run_initializer(skip_typeref(mem->declaration.type), name,
                            offset + mem->compound_member.offset + res.second, cur);
            lIdx++;
        }else
            panic("INITIALIZER_LIST not yet implemented for compound member %d", cur->kind);
    }
    offset += get_ctype_size(type);
}

static void run_list(type_t* type, const std::string& name, int offset, initializer_t *initializer)
{
    assert(initializer->kind == INITIALIZER_LIST);
    // a list of len 1 can be used to initialize a scalar or a char array
    int off = offset;
    int lIdx = 0;
    switch(type->kind)
    {
    case TYPE_ARRAY: {
        run_list_array_init(type, name, off, initializer, lIdx, 0);
        break;
    }
    case TYPE_COMPOUND_STRUCT:
    case TYPE_COMPOUND_UNION: {
        run_list_compound_init(type, name, off, initializer, lIdx);
        break;
    }
    default:
        panic("INITIALIZER_LIST not yet implemented for lhs type %d", type->kind);
    }
}

static void run_initializer(type_t* type, const std::string& name, int offset, initializer_t *initializer)
{
    switch(initializer->kind)
    {
    case INITIALIZER_VALUE:
        run_value(type,name,offset,initializer);
        break;
    case INITIALIZER_LIST:
        run_list(type,name,offset,initializer);
        break;
    case INITIALIZER_STRING:
        run_string(type,name,offset,initializer);
        break;
    case INITIALIZER_DESIGNATOR:
        panic("INITIALIZER_DESIGNATOR not yet implemented");
        break;
    }
}

static void initialize_variable(entity_t * entity)
{
    assert(entity->variable.initializer);
    if( entity->variable.is_local )
    {
        // add code right here
        assert( end_of_function_label != 0 ); // this happens in a function

    }else
    {
        // initialize global or (local) static variable
        assert( end_of_function_label == 0 ); // this cannot happen in a function
        // we already called e->Begin(Code::Section::Data
        // just reserve space here and initialize it using an .initdata section (TODO: consider constant
        const std::string name = rename(entity);

        type_t* type = skip_typeref(entity->declaration.type);
#if 1
        // directly initialize section with string data, without extra initializer
        if( entity->variable.initializer->kind == INITIALIZER_STRING )
        {
            // covers both char str1[] = "abcd"; and char str2[] = {"abcd"};
            assert( type->kind == TYPE_ARRAY && type->array.size );
            assert( entity->variable.initializer->value.value->kind == EXPR_STRING_LITERAL );
            string_t* str = entity->variable.initializer->value.value->string_literal.value;
            for( int i = 0; i < type->array.size; i++ ) {
                if( i <= str->size )
                    e->Define(Code::Imm(types[s1],str->begin[i]));
                else
                    e->Define(Code::Imm(types[s1],0));
            }
            return;
        }else
#endif
            // initialize the whole area with zeros
            for( int i = 0; i < get_ctype_size(entity->variable.base.type); i++ )
                e->Define(Code::Imm(types[s1],0));

        e->Require(name + "##init");

        // .initdata name
        e->Begin(Code::Section::InitData, name + "##init",
                 0,
                 true, // required
                 true, // duplicable
                 false // replaceable
                 );
        if( target.debug_info )
        {
            e->Locate(entity->base.pos.input_name,toPos(entity->base.pos.lineno,entity->base.pos.colno));
            e->DeclareVoid();
        }
        run_initializer(type, name, 0, entity->variable.initializer);
    }
}

static void allocate_variable(entity_t* entity)
{
    if( !declaration_is_definition(entity) )
        return;

    e->Begin(Code::Section::Data, rename(entity),
             get_ctype_alignment(entity->variable.base.type),
             false, // required
             true, // duplicable
             entity->variable.initializer == 0 // replaceable
             );

#ifndef __ECS_DUPLICATE_ISSUE__
    if( target.debug_info )
    {
        e->Locate(entity->base.pos.input_name,
                  toPos(entity->base.pos.lineno,entity->base.pos.colno));
        print_type_decl(entity->declaration.type, false);
    }
#endif

    if( entity->variable.initializer )
    {
#ifdef __ECS_DUPLICATE_ISSUE__
        if( target.debug_info )
        {
            e->Locate(entity->base.pos.input_name,
                      toPos(entity->base.pos.lineno,entity->base.pos.colno));
            print_type_decl(entity->declaration.type, false);
        }
#endif
        initialize_variable(entity);
    }else
    {
        if( entity->variable.base.storage_class == STORAGE_CLASS_STATIC || !entity->variable.is_local )
        {
            for( int i = 0; i < get_ctype_size(entity->variable.base.type); i++ )
                e->Define(Code::Imm(types[s1],0));
        }else
        {
            e->Reserve(get_ctype_size(entity->variable.base.type));
        }
    }
}

static void scope_to_ir(scope_t *scope)
{
    for (entity_t *entity = scope->first_entity; entity != NULL; entity = entity->base.next) {
        if (entity->base.symbol == NULL)
            continue;

        switch (entity->kind) {
        case ENTITY_FUNCTION: {
            if (entity->function.btk != BUILTIN_NONE) {
                /* builtins have no representation */
                continue;
            }

            /* Only create the IR if the function is used or potentially usable from outside (i.e. not static). */
            if (is_decl_necessary(entity)) {
                create_function(&entity->function);
            }
            break;
        }
        case ENTITY_VARIABLE: {
            allocate_variable(entity);
            break;
        }
        case ENTITY_NAMESPACE:
            scope_to_ir(&entity->namespacee.members);
            break;
        default:
            break;
        }
    }
}

static ASCIICharset charset;
static StringPool stringPool;
static StreamDiagnostics diagnostics {std::cerr};

// modified version of http://www.josuttis.com/cppcode/fdstream.hpp
class fdoutbuf : public std::streambuf {
  protected:
    FILE* fd;    // file descriptor
  public:
    // constructor
    fdoutbuf (FILE* _fd) : fd(_fd) {}
  protected:
    // write one character
    virtual int_type overflow (int_type c) {
        return fputc(c,fd);
    }
    // write multiple characters
    virtual
    std::streamsize xsputn (const char* s, std::streamsize num) {
        return fwrite(s,1,num,fd);
    }
};

class fdostream : public std::ostream {
  protected:
    fdoutbuf buf;
  public:
    fdostream (FILE* fd) : std::ostream(0), buf(fd) {
        rdbuf(&buf);
    }
};

extern "C" {

void translation_unit_to_ir(translation_unit_t *unit, FILE* cod_out, const char* source_file)
{
    Layout layout(
        { target_data[target.target].int_width, 1, 8},
        {4, 4, 8},
        target_pointer_width(),
        target_pointer_width(),
        {0, target_stack_align(), target_stack_align()},
        true
    );
    Code::Platform platform(layout,target_has_linkregister());

    MyEmitter emitter(diagnostics,stringPool,charset,platform);
    e = &emitter.ctx;
    current_translation_unit = unit;
    current_source_file = source_file;
    //to_declare.clear();
    string_decls.clear();
    compound_literal_decls.clear();
    static_locals.clear();

    init_types();

    scope_to_ir(&unit->scope);

    for( auto i = compound_literal_decls.begin(); i != compound_literal_decls.end(); ++i )
    {
        expression_t* expr = (*i);
        char buf[10];
        sprintf(buf,"%d",expr->compound_literal.id);
        const std::string name = file_hash() + buf;
        e->Begin(Code::Section::Data, name,
                 get_ctype_alignment(expr->compound_literal.type),
                 false, // required
                 true, // duplicable
                 false // replaceable
                 );
        assert(expr->compound_literal.initializer);
        for( int i = 0; i < get_ctype_size(expr->compound_literal.type); i++ )
            e->Define(Code::Imm(types[s1],0)); // zero all in case the initializer doesn't
        e->Require(name + "##init");

        // .initdata name
        e->Begin(Code::Section::InitData, name + "##init",
                 0,
                 true, // required
                 true, // duplicable
                 false // replaceable
                 );
        if(target.debug_info) {
            e->Locate(expr->compound_literal.initializer->base.pos.input_name,
                      toPos(expr->compound_literal.initializer->base.pos.lineno,
                            expr->compound_literal.initializer->base.pos.colno));
            e->DeclareVoid();
        }
        run_initializer(skip_typeref(expr->compound_literal.type), name, 0, expr->compound_literal.initializer);
    }

    for( auto i = string_decls.begin(); i != string_decls.end(); ++i )
    {
        e->Begin(Code::Section::Data, (*i).first,
                 1,
                 false, // required
                 true, // duplicable
                 false // replaceable
                 );
        std::string str = (*i).second;
        for( int j = 0; j < str.size(); j++ )
        {
            if( str[j] == '\n' || str[j] == '\r' )
                str[j] = ' ';
        }
        const std::string cmt = "\"" + str + "\"";
        e->Comment(cmt.c_str());
        for( int j = 0; j <= str.size(); j++ )
            e->Define(Code::Imm(types[s1],(*i).second[j]));
    }

    for( auto i = static_locals.begin(); i != static_locals.end(); ++i )
    {
        entity_t* var = (*i);
        allocate_variable(var);
    }

    for( statement_t *stat = unit->global_asm; stat; stat = stat->base.next)
    {
        try {

            if( stat->asms.is_target ){
                // pass-through to machine code generator
                e->BeginAssembly();
                e->Assemble(source_file,stat->base.pos.lineno,stat->asms.asm_text->begin);
            }else
                e->AssembleCode(source_file,stat->base.pos.lineno,stat->asms.asm_text->begin);
        }catch(...) {}
    }

    if( target.debug_info )
    {
        std::set<type_t*> done;
        while( !to_declare.empty() )
        {
            // during print_type_decl now entries may be added to to_declare!
            std::set<type_t*>::iterator i = to_declare.begin();
            type_t* t = (*i);
            to_declare.erase(i);
            if( done.find(t) != done.end() )
                continue;
            done.insert(t);
            assert(is_type_compound(t) && t->compound.compound->base.symbol != 0);
            std::string name = rename2(&t->compound.compound->base,
#ifdef __ECS_DUPLICATE_ISSUE__
                                       1);
#else
                                       t->compound.compound->base.parent_entity != 0);
#endif
            e->Begin(Code::Section::TypeSection,name);
            e->Locate(t->compound.compound->base.pos.input_name,
                      toPos(t->compound.compound->base.pos.lineno,
                                    t->compound.compound->base.pos.colno));
            print_type_decl(t,true);
        }
        for( int i = 0; i < ptr; i++ )
        {
            e->Begin(Code::Section::TypeSection,ecsTypes[i].dbgname);
            e->DeclareType(types[i]);
        }
    }

    e = 0;

    fdostream out_stream(cod_out);

    out_stream << "; this is Eigen intermediate code, generated by ECC" << std::endl;
    out_stream << "; see https://github.com/rochus-keller/EiGen/tree/master/ecc for more information" << std::endl;
    out_stream << "; assuming pointer size " << (int)target_pointer_width()
      << ", int size " << (int)target_data[target.target].int_width
      << ", stack alignment " << (int)target_stack_align() << " bytes, "
      << (target_has_linkregister() ? "with" : "no") << " link reg" << std::endl;

    Code::Generator cdgen(layout,platform);

    cdgen.Generate(emitter.s, target_data[target.target].name,out_stream);

    current_translation_unit = 0;
    current_source_file = "";
}

void exit_ast2ir(void)
{
    //  NOP
}

}
