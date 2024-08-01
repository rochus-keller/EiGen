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
}

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
static std::deque<Label*> breaks, continues;
static std::deque<Label> clabels;
static Label* return_label = 0;
static Code::Type return_type;
//static std::set<Type*> to_declare;
static std::unordered_map<std::string,string_t*> string_decls;
static std::deque<expression_t*> compound_literal_decls;
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
        case ATOMIC_TYPE_CHAR:
        case ATOMIC_TYPE_SCHAR:
        case ATOMIC_TYPE_UCHAR:
            return !is_type_signed(ty) ? u1 : s1;
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

void name_hash(const char* path, char* buf, int buflen )
{
    const char* code = "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            //"$_#.";
    const int codelen = strlen(code);

    const int len = strlen(path);
    int i;
    buf[buflen] = 0;
    for( i = 0; i < buflen; i++ )
        buf[i] = '_';
    for( i = 0; i < len; i++ )
    {
        const int j = i % buflen;
        buf[j] ^= path[i];
    }
    for( i = 0; i < buflen; i++ )
    {
        const uint8_t ch = (uint8_t)buf[i];
        char c = code[ch % codelen];
        buf[i] = c;
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

static std::string rename(entity_t* var)
{
    const bool is_static = var->variable.base.storage_class == STORAGE_CLASS_STATIC;

    std::string name = var->base.symbol->string;
    while( is_static && var->base.parent_entity->kind == ENTITY_FUNCTION ) {
        var = var->base.parent_entity;
        name = std::string(var->base.symbol->string) + "#" + name;
    }
    if( is_static )
    {
        // prefix with file path hash
        name = file_hash() + name;
    }
    return name;
}

static Smop expression(expression_t * expr);

// Compute the absolute address of a given node.
// It's an error if a given node does not reside in memory.
static Smop lvalue(expression_t * expr) {
    switch (expr->kind)
    {
    case EXPR_REFERENCE: {
        entity_t* var = expr->reference.entity;

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
    case EXPR_ARRAY_ACCESS:  {
        Smop arr = expression(expr->array_access.array_ref); // TODO
        Smop idx = expression(expr->array_access.index);
        type_t    *const elem_type = skip_typeref(expr->base.type);
        idx = e->Multiply(idx, Code::Imm(idx.type,get_ctype_size(elem_type)));
        return e->Add(arr,e->Convert(types[ptr],idx));
    }
    case EXPR_SELECT: {
        Smop tmp = expression(expr->select.compound);
        entity_t* mem = expr->select.compound_entry;
        assert(mem->kind == ENTITY_COMPOUND_MEMBER);
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
#if 0
        // TODO
    case ND_FUNCALL:
        if (node->ret_buffer) {
            return gen_expr(node);
        }
        break;
#endif
    case EXPR_BINARY_ASSIGN:
    case EXPR_CONDITIONAL:
        if (expr->base.type->kind == TYPE_COMPOUND_STRUCT || expr->base.type->kind == TYPE_COMPOUND_UNION) {
            return expression(expr);
        }
        break;
    case EXPR_COMPOUND_LITERAL:  {
        assert( expr->compound_literal.id == 0 );
        compound_literal_decls.push_back(expr);
        expr->compound_literal.id = compound_literal_decls.size();
        char buf[10];
        sprintf(buf,"%d",expr->compound_literal.id);
        return Code::Adr(types[ptr],file_hash() + buf );
    }

    }
    panic("not an lvalue");
    return Smop();
}

static void load(type_t * ty, Smop& tmp) {
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
    if( ty->kind == TYPE_POINTER && ty->pointer.replacemen_of != 0 &&
            ( ty->pointer.replacemen_of->kind == TYPE_ARRAY || ty->pointer.replacemen_of->kind == TYPE_FUNCTION) )
        return; // not really a pointer, but actually an array or function
#endif

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

static void store(type_t *ty, const Smop& lhs, const Smop& rhs) {
    ty = skip_typeref(ty);
    switch (ty->kind) {
    case TYPE_COMPOUND_STRUCT:
    case TYPE_COMPOUND_UNION:
        e->Copy(lhs, rhs, Code::Imm(types[ptr],get_ctype_size(ty)));
        return;
    }

    const Code::Type type = getCodeType(ty);
    e->Move(e->MakeMemory(type,lhs),rhs);
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
        lhs = e->Multiply(lhs, Code::Imm(types[ptr],res));
    }
    if(rhsT->kind != TYPE_POINTER) {
        res = get_ctype_size(lhsT->pointer.points_to);
        rhs = e->Multiply(rhs, Code::Imm(types[ptr],res));
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
        const unsigned char w = getTypeWidth(mem->compound_member.base.type);
        const Code::Type nm = getCodeType(mem->compound_member.base.type);
        // align the bitfield to the msb of the underlying type
        val = e->ShiftLeft(e->Convert(nm,val), Code::Imm(nm,w - mem->compound_member.bit_size -
                                                         mem->compound_member.bit_offset));
        val = e->ShiftRight(val, Code::Imm(nm,w - mem->compound_member.bit_size));
    }
}

static int store_bitfield(expression_t const*const expr, const Smop& lhs, Smop& rhs)
{
    if (expr->kind == EXPR_SELECT &&
            expr->select.compound_entry->compound_member.bitfield) {

        const Code::Type rty = rhs.type;

        // If the lhs is a bitfield, we need to read the current value
        // from memory and merge it with a new value.
        entity_t* mem = expr->select.compound_entry;
        assert(mem->kind == ENTITY_COMPOUND_MEMBER);

        const Code::Type mty = getCodeType(mem->compound_member.base.type);

        Smop rdi = e->Convert(rty,rhs);
        rdi = e->And(rdi, Code::Imm(rty,(1L << mem->compound_member.bit_size) - 1));
        rdi = e->Convert(mty,rdi);
        rdi = e->ShiftLeft(rdi, Code::Imm(mty,mem->compound_member.bit_offset));

        rhs = e->Move(e->MakeMemory(mty,lhs));

        const uint64_t mask = ((1L << mem->compound_member.bit_size) - 1) << mem->compound_member.bit_offset;
        Smop r9;
        if( is_type_signed(mem->compound_member.base.type)) {
            r9 = Code::Imm(mty, ~mask);
        }else {
            const uint64_t mask2 = (((uint64_t(1) << ((get_ctype_size(mem->compound_member.base.type)-1)*8)) - 1) << 8) | 255;
            r9 = Code::UImm(mty, ~mask & mask2);
        }
        rhs = e->And(e->Convert(mty,rhs), r9);
        rhs = e->Or(rhs, rdi);

        store(mem->compound_member.base.type, lhs, rhs);
        return 1;
    }else
        return 0;
}

Smop prefix_inc_dec(expression_t const*const expr, const Smop& lhs, int inc, int returnOldVal )
{
    Smop rhs = e->Move(lhs); // TODO do we need this move, or is a plain '=' enough?
    load(expr->base.type,rhs);
    fetch_bitfield(expr, rhs);
    Smop oldVal = returnOldVal ? e->Move(rhs) : rhs;
    int off = inc ? 1 : -1;
    if( expr->base.type->kind == TYPE_POINTER )
        off *= get_ctype_size(expr->base.type->pointer.points_to);
    rhs = e->Add(rhs, Code::Imm(rhs.type,off));
    if( store_bitfield(expr, lhs, rhs) ) {
        if( !returnOldVal )
            fetch_bitfield(expr, oldVal);
        return oldVal;
    } else {
        store(expr->base.type, lhs, rhs);
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
                Code::Imm(types[ptr],sz)); // sub	ptr $sp, ptr $sp, ptr %d
    e->Copy(Code::Reg(types[ptr],Code::RSP), reg, Code::Imm(types[ptr],sz)); // copy	ptr $sp, ptr $0, ptr %d"
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

    type_t* ty = args->expression->base.type;
    switch (ty->kind) {
    case TYPE_COMPOUND_STRUCT:
    case TYPE_COMPOUND_UNION:
        aligned_size += push_struct(ty, arg);
        break;
    default:
#if 0
        // TODO do we still need that in cparser?
        if( param_count <= 0 )
        {
            // this is one of the variable arguments
            switch(ty->kind)
            {
            case TY_CHAR:
            case TY_BOOL:
            case TY_SHORT: {
                Type* to;
                if( ty->is_unsigned )
                    to = basic_utype(TY_INT);
                else
                    to = basic_type(TY_INT);
                cast(ty,to, arg);
                ty = to;
                break;
            }
            case TY_FLOAT: {
                Type* to = basic_type(TY_DOUBLE);
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

#if 0
    // TODO

    // If the return type is a large struct/union, the caller passes
    // a pointer to a buffer as if it were the first argument.
    if (node->ret_buffer) {
        Smop res = Code::Reg(types[ptr], Code::RFP,node->ret_buffer->offset); // mov ptr $0, ptr $fp%+d
        aligned_size += pushRes(types[ptr], res);
    }
#endif

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
#if 0
#ifndef NDEBUG
    assert(!expr->base.transformed);
    ((expression_t*)expr)->base.transformed = true;
    assert(!is_type_complex(skip_typeref(expr->base.type)));
#endif
#endif
    switch (expr->kind) {
    case EXPR_LITERAL_FLOATINGPOINT: {
        const double d = strtod(expr->literal.value->begin, 0);
        return Code::FImm(getCodeType(expr->base.type),d);
    }
    case EXPR_LITERAL_INTEGER: {
        long long i;
        sscanf(expr->literal.value->begin,"%lld", &i);
        return Code::Imm(getCodeType(expr->base.type),i);
    }
    case EXPR_LITERAL_CHARACTER:
        return Code::Imm(getCodeType(expr->base.type),expr->string_literal.value->begin[0]);
    case EXPR_STRING_LITERAL: {
        std::string name;
        name.resize(10);
        name_hash(expr->string_literal.value->begin, &name[1], name.size()-1);
        name[0] = '.';
        string_decls[name] = expr->string_literal.value;
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
        e->BranchEqual(lfalse,Code::Imm(type,0),e->Convert(type,lhs));
        Smop rhs = expression(expr->binary.right);
        type = getCodeType(expr->binary.right->base.type);
        e->BranchEqual(lfalse,Code::Imm(type,0),e->Convert(type,rhs));
        return e->Set(lfalse,Code::Imm(types[s4],1),Code::Imm(types[s4],0));
    }
    case EXPR_BINARY_LOGICAL_OR: {
        Smop lhs = expression(expr->binary.left);
        Code::Type type = getCodeType(expr->binary.left->base.type);
        Label ltrue = e->CreateLabel();
        e->BranchNotEqual(ltrue,Code::Imm(type,0),e->Convert(type,lhs));
        Smop rhs = expression(expr->binary.right);
        type = getCodeType(expr->binary.right->base.type);
        e->BranchNotEqual(ltrue,Code::Imm(type,0),e->Convert(type,rhs));
        return e->Set(ltrue,Code::Imm(types[s4],0),Code::Imm(types[s4],1));
    }
    case EXPR_UNARY_COMPLEMENT: {
        Smop tmp = expression(expr->binary.left);
        const Code::Type type = getCodeType(expr->binary.left->base.type);
        tmp = e->Complement(e->Convert(type,tmp));
        return tmp;
    }
    case EXPR_UNARY_NOT: {
        Smop tmp = expression(expr->binary.left);
        const Code::Type type = getCodeType(expr->binary.left->base.type);

        Label label = e->CreateLabel();
        e->BranchEqual(label,Code::Imm(type,0),e->Convert(type,tmp));
        tmp = e->Set(label,Code::Imm(type,0), Code::Imm(type,1));
        return tmp;
    }
    case EXPR_UNARY_NEGATE: {
        Smop tmp = expression(expr->binary.left);
        const Code::Type type = getCodeType(expr->binary.left->base.type);
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
        e->BranchEqual(lelse,Code::Imm(type,0),e->Convert(type,cond));
        Smop res;
        Smop lhs = expression(expr->conditional.true_expression);
        // apparently C allows x ? (void)a : (void)b or mixed
        if( lhs.model != Code::Operand::Void ) {
            res = e->MakeRegister(lhs);
            e->Fix(res);
        }
        e->Branch(lend);
        lelse();
        Smop rhs = expression(expr->conditional.false_expression);
        if( rhs.model == Code::Operand::Void || lhs.model == Code::Operand::Void ) {
            if( res.model == Code::Operand::Register )
                e->Unfix(res);
            res = rhs;
        } else {
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
        load(expr->base.type, tmp);
        return tmp;
    }
    case EXPR_SELECT: {
        Smop tmp = lvalue(expr);
        load(expr->select.compound_entry->declaration.type, tmp);

        fetch_bitfield(expr, tmp);

        return tmp;
    }
    case EXPR_REFERENCE: {
        Smop tmp = lvalue(expr);
        load(expr->reference.entity->declaration.type, tmp);
        return tmp;
    }
    case EXPR_ARRAY_ACCESS: {
        Smop tmp = lvalue(expr);
        load(expr->base.type, tmp);
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

        const Code::Type lhsT = getCodeType(expr->binary.left->base.type);
        if( expr->kind != EXPR_BINARY_ASSIGN )
        {
            Smop lhs2 = e->Move(lhs); // TODO do we need this move, or is a plain '=' enough?
            load(expr->binary.left->base.type,lhs2);
            fetch_bitfield(expr->binary.left, lhs2);
            const int baseSize = scale_for_pointer_arith(expr->kind,lhs2,expr->binary.left->base.type,
                                    rhs, expr->binary.right->base.type);
            rhs = e->Convert(lhsT,rhs);
            lhs2 = e->Convert(lhsT,lhs2);
            rhs = binary_ops(expr->kind,lhs2,rhs, baseSize);
        }

        if( store_bitfield(expr->binary.left, lhs, rhs) ) {
            fetch_bitfield(expr->binary.left, rhs);
            return rhs;
            // NOTE: not orig rhs shall be returned according to the standard, but what was actually stored in lhs!
            // gcc effectively seems to consider sign and mem->bit_width; see bitfield-immediate-assign.c
        } else {
            rhs = e->Convert(lhsT,rhs);
            store(expr->binary.left->base.type, lhs, rhs);
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
        if( expr->unary.value->base.type->kind == TYPE_POINTER ||
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
        Smop fun = expression(expr->call.function);

        Smop res;
        if( false ) // TODO node->ret_buffer )
        {
            e->Call(fun,aligned_size); // call fun $0, %d
            //res = Code::Reg(types[ptr], Code::RFP,node->ret_buffer->offset); // mov ptr $0, ptr $fp%+d
        }else if( ret )
        {
            res = e->Call(getCodeType(ret), fun,aligned_size); // call fun $0, %d

        }else
            e->Call(fun,aligned_size); // call fun $0, %d

        return res;
    }

    case EXPR_LABEL_ADDRESS:
    case EXPR_FUNCNAME: // expr->funcname, __func__
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

static void run_initializer(type_t* type, const std::string& name, int offset, initializer_t *initializer);

static void statement(statement_t *const stmt)
{
#if 0
#ifndef NDEBUG
    assert(!stmt->base.transformed);
    stmt->base.transformed = true;
#endif
#endif
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
                run_initializer(skip_typeref(decl->declaration.type), std::string(),
                                decl->variable.offset, decl->variable.initializer);
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

        std::deque<Label> ll;
        for (case_label_statement_t *n = stmt->switchs.first_case; n; n = n->next) {
            ll.push_back(e->CreateLabel());
            n->target = &ll.back();
            if (n->first_case == n->last_case) {
                e->BranchEqual(ll.back(),Code::Imm(cond_type,get_tarval_long(n->first_case)),
                               e->Convert(cond_type,cond));
                continue;
            }

            // [GNU] Case ranges
            cond = e->Convert(cond_type,cond);
            cond = e->Subtract(cond, Code::Imm(cond_type,get_tarval_long(n->first_case)));
            e->BranchGreaterEqual(ll.back(),cond, Code::Imm(cond_type,
                                 get_tarval_long(n->last_case) - get_tarval_long(n->first_case)));
        }
        cond = Smop(); // release register

        if (stmt->switchs.default_label)
        {
            ll.push_back(e->CreateLabel());
            stmt->switchs.default_label->target = &ll.back();
            e->Branch(ll.back());
        }

        clabels.push_back(e->CreateLabel());
        e->Branch(clabels.back());
        statement(stmt->switchs.body);
        clabels.back()();
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
        breaks.push_back(&lbreak);
        Label lcont = e->CreateLabel();
        continues.push_back(&lcont);
        lbegin();
        statement(stmt->do_while.body);
        lcont();
        Smop cond = expression(stmt->do_while.condition);
        const Code::Type type = getCodeType(stmt->do_while.condition->base.type);
        e->BranchNotEqual(lbegin,Code::Imm(type,0),e->Convert(type,cond));
        lbreak();
        breaks.pop_back();
        continues.pop_back();
        return;
    }
    case STATEMENT_FOR: {
        if (stmt->fors.initialisation)
            expression(stmt->fors.initialisation);
        Label lbegin = e->CreateLabel();
        Label lbreak = e->CreateLabel();
        breaks.push_back(&lbreak);
        Label lcont = e->CreateLabel();
        continues.push_back(&lcont);
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
        breaks.pop_back();
        continues.pop_back();
        return;
    }
    case STATEMENT_BREAK: {
        e->Branch(*breaks.back());
        return;
    }
    case STATEMENT_CONTINUE: {
        e->Branch(*continues.back());
        return;
    }
    case STATEMENT_RETURN: {
        if (stmt->returns.value) {
            Smop lhs = expression(stmt->returns.value);
            Code::Type lhsT = getCodeType(stmt->returns.value->base.type);

            switch (stmt->returns.value->base.type->kind) {
            case TYPE_COMPOUND_STRUCT:
            case TYPE_COMPOUND_UNION:
                // TODO copy_struct_mem(lhs);
                break;
            case TYPE_VOID:
                break;
            default:
                e->Move (Code::Reg {lhsT, Code::RRes}, e->Convert(lhsT,lhs));
                break;
            }
            return_type = lhsT;
        }
        assert( return_label != nullptr );
        e->Branch(*return_label);
        return;
    }
    case STATEMENT_LABEL: {
        label_t* lbl = stmt->label.label;
        if(lbl->target == 0)
        {
            clabels.push_back(e->CreateLabel());
            lbl->target = &clabels.back();
            clabels.back()();
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
            clabels.push_back(e->CreateLabel());
            lbl->target = &clabels.back();
            e->Branch(clabels.back());
        }else {
            Label* l = (Label*)lbl->target;
            e->Branch(*l);
        }
        return;
    }
    case STATEMENT_ASM: {
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
    struct Payload {
        int* bottom;
        std::deque<entity_t*>* statics;
    };
    Payload* res = (Payload*)payload;

    entity_t * end = last != NULL ? last->base.next : NULL;
    for (; entity != end; entity = entity->base.next) {
        if ( entity->kind == ENTITY_VARIABLE && entity->variable.base.storage_class != STORAGE_CLASS_STATIC ) {
            type_t *type = skip_typeref(entity->declaration.type);

            *res->bottom += get_ctype_size(type);
            *res->bottom = align_to(*res->bottom, get_ctype_alignment(type));
            entity->variable.offset = -(*res->bottom);
            entity->variable.is_local = true;
        }
        if ( entity->kind == ENTITY_VARIABLE && entity->variable.base.storage_class == STORAGE_CLASS_STATIC )
            res->statics->push_back(entity);
    }
}

static void assign_local_variable_offsets(statement_t *stmt, void * payload)
{
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
static void assign_lvar_offsets(function_t *const function, std::deque<entity_t*>* statics) {

    int top = firstParamOffset();
    int bottom = 0;

    type_t *type = skip_typeref(function->base.type);
    assert(is_type_function(type));
    type_t *const return_type = skip_typeref(type->function.return_type);

    if( return_type && is_type_compound(return_type) )
        top += MAX(target_stack_align(), target_pointer_width());
        // if fn has struct return, the first param is a pointer to result

    // TODO: provide for storage space for union/struct return type

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

    struct {
        int* bottom;
        std::deque<entity_t*>* statics;
    } payload;
    payload.bottom = &bottom;
    payload.statics = statics;

    // Assign offsets to local variables.
    walk_statements(function->body, assign_local_variable_offsets, &payload);

    function->stack_size = align_to(bottom, target_stack_align()); // TODO: orig was 16, i.e. 2 * codegen_StackAlign
}

static void create_function(function_t *const function)
{
    if (function->body == NULL)
        return;

    // No code is emitted for "static inline" functions
    // if no one is referencing them.
    if (!function->base.used && function->base.storage_class == STORAGE_CLASS_STATIC)
        return;

    return_type = Code::Type();


    std::deque<entity_t*> statics;
    assign_lvar_offsets(function, &statics);

    // TODO: allocate statics and consider initializers

    // NOTE: static is not supported by ECS; therefore getName provides some unique mangling
    e->Begin(Code::Section::Code, rename((entity_t*)function) );

    clabels.clear();
    Label lret = e->CreateLabel();
    return_label = &lret;

    const bool ismain = is_main((entity_t*)function);

    // Prologue
    if( !ismain && target_has_linkregister() )
        e->Push(Code::Reg(types[fun],Code::RLink));
    e->Enter(function->stack_size);

    type_t* ft = function->base.type;
    assert(is_type_function(ft));

    if( ismain )
    {
        if( ft->function.return_type->kind != TYPE_VOID &&
                ft->function.return_type->kind != TYPE_ATOMIC &&
                ft->atomic.akind != ATOMIC_TYPE_INT )
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
    if( ft->function.return_type && ft->function.return_type->kind != TYPE_VOID )
    {
        if( return_type.model == Code::Type::Void )
            e->Move(Code::Reg(types[s4],Code::RRes),Code::Imm(types[s4],0));
    }
    e->Leave();
    if( ismain )
    {
        if( return_type.model == Code::Type::Void )
            e->Push(Code::Reg {types[s4], Code::RRes});
        else
            e->Push(Code::Reg {return_type, Code::RRes});
        e->Call(Code::Adr(types[fun],"_Exit"),0);
    }else
        e->Return();
    return_label = 0;
    clabels.clear();
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

static entity_t* get_compound_member_n(compound_t* compound, int n)
{
    int i = 0;
    for (entity_t *mem = compound->members.first_entity; mem != NULL; mem = mem->base.next, i++)
    {
        if( i == n )
            return mem;
    }
    return 0;
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

static Smop to(Code::Type type, const std::string& name, int offset)
{
    if( !name.empty() )
        return Code::Mem(type,name,offset);
    else
        return e->MakeMemory(type, Code::Reg(types[ptr],Code::RFP, offset));
}

static void run_initializer(type_t* type, const std::string& name, int offset, initializer_t *initializer)
{
    switch(initializer->kind)
    {
    case INITIALIZER_VALUE: {
        if( type->kind == TYPE_ATOMIC || type->kind == TYPE_POINTER ) {
            //Smop to = name.empty() ? Code::Mem()
            e->Move(to(getCodeType(type),name,offset), expression(initializer->value.value));
        }else if( type->kind == TYPE_COMPOUND_UNION ) {
            entity_t* mem = get_compound_member_n(type->compound.compound,0);
            assert(mem && mem->kind == ENTITY_COMPOUND_MEMBER);
            e->Move(to(getCodeType(mem->declaration.type),name,offset), expression(initializer->value.value));
        }

        //else if( type->kind == TYPE_COMPOUND_STRUCT )
        //    run_initializer(type,name,offset,initializer->value);
        else
            panic("INITIALIZER_VALUE for given type not yet implemented: %d", type->kind);
        break;
    }
    case INITIALIZER_LIST: {
        switch(type->kind)
        {
        case TYPE_ARRAY: {
            type_t* et = skip_typeref(type->array.element_type);
            const int elsz = get_ctype_size(et);
            int idx = 0;
            for( int i = 0; i < initializer->list.len; i++ )
            {
                initializer_t* cur = initializer->list.initializers[i];
                if( cur->kind == INITIALIZER_VALUE || cur->kind == INITIALIZER_LIST )
                {
                    run_initializer(et, name, offset + idx * elsz, cur);
                }else if( cur->kind == INITIALIZER_DESIGNATOR )
                {
                    assert( cur->designator.designator->array_index );
                    ir_tarval * v = fold_expression(cur->designator.designator->array_index);
                    assert(v);
                    idx = get_tarval_long(v);
                    i++;
                    assert(i < initializer->list.len);
                    cur = initializer->list.initializers[i];
                    run_initializer(et, name, offset + idx * elsz, cur);
                }else
                    panic("INITIALIZER_LIST not yet implemented for array element initializer %d", cur->kind);
                idx++;
            }
            break;
        }
        case TYPE_COMPOUND_STRUCT:
        case TYPE_COMPOUND_UNION: {
            int idx = 0;
            for( int i = 0; i < initializer->list.len; i++ )
            {
                initializer_t* cur = initializer->list.initializers[i];
                if( cur->kind == INITIALIZER_VALUE || cur->kind == INITIALIZER_LIST )
                {
                    entity_t* mem = get_compound_member_n(type->compound.compound,idx);
                    assert(mem && mem->kind == ENTITY_COMPOUND_MEMBER);
                    run_initializer(skip_typeref(mem->declaration.type), name,
                                    offset + mem->compound_member.offset, cur);
                }else if( cur->kind == INITIALIZER_DESIGNATOR )
                {
                    entity_t* mem = find_compound_entry(type->compound.compound,cur->designator.designator->symbol);
                    assert(mem && mem->kind == ENTITY_COMPOUND_MEMBER);
                    idx = get_idx_of_member(type->compound.compound,mem);
                    i++;
                    assert(i < initializer->list.len);
                    cur = initializer->list.initializers[i];
                    run_initializer(skip_typeref(mem->declaration.type), name,
                                    offset + mem->compound_member.offset, cur);
                }else
                    panic("INITIALIZER_LIST not yet implemented for compound member %d", cur->kind);
                idx++;
            }
            break;
        }
        default:
            panic("INITIALIZER_LIST not yet implemented for lhs type %d", type->kind);
        }

        break;
    }
    case INITIALIZER_STRING: {
        assert( type->kind == TYPE_ARRAY && type->array.size );
        assert( initializer->value.value->kind == EXPR_STRING_LITERAL );
        Smop str = expression(initializer->value.value);
        Smop to;
        if( !name.empty() )
            to = Code::Adr(types[ptr],name,offset);
        else
            to = Code::Reg(types[ptr],Code::RFP, offset);
        e->Copy(to, str, Code::Imm(types[ptr],type->array.size));

        // not necessary e->Require(str.address);
        break;
    }
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
        assert( return_label != 0 ); // this happens in a function

    }else
    {
        // initialize global or (local) static variable
        assert( return_label == 0 ); // this cannot happen in a function
        // we already called e->Begin(Code::Section::Data
        // just reserve space here and initialize it using an .initdata section (TODO: consider constant
        const std::string name = rename(entity);
        // e->Reserve(get_ctype_size(entity->variable.base.type));

        type_t* type = skip_typeref(entity->declaration.type);
#if 1
        // directly initialize section with string data, without extra initializer
        if( entity->variable.initializer->kind == INITIALIZER_STRING )
        {
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
            for( int i = 0; i < get_ctype_size(entity->variable.base.type); i++ )
                e->Define(Code::Imm(types[s1],0));
        e->Require(name + "##init");

        // .initdata name
        e->Begin(Code::Section::InitData, name + "##init",
                 0,
                 true, // required
                 false, // duplicable
                 false // replaceable
                 );
        run_initializer(type, name, 0, entity->variable.initializer);
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
            if( !declaration_is_definition(entity) )
                continue;

            e->Begin(Code::Section::Data, rename(entity),
                     get_ctype_alignment(entity->variable.base.type),
                     false, // required
                     false, // duplicable
                     false // replaceable
                     );
            if( entity->variable.initializer )
            {
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

    init_types();

    scope_to_ir(&unit->scope);

    for( auto i = string_decls.begin(); i != string_decls.end(); ++i )
    {
        e->Begin(Code::Section::Data, (*i).first,
                 1,
                 false, // required
                 true, // duplicable
                 false // replaceable
                 );
        std::string str = (*i).second->begin;
        for( int j = 0; j < str.size(); j++ )
        {
            if( str[j] == '\n' || str[j] == '\r' )
                str[j] = ' ';
        }
        e->Comment(str.c_str());
        for( int j = 0; j <= (*i).second->size; j++ )
            e->Define(Code::Imm(types[s1],(*i).second->begin[j]));
    }

    for( auto i = compound_literal_decls.begin(); i != compound_literal_decls.end(); ++i )
    {
        expression_t* expr = (*i);
        char buf[10];
        sprintf(buf,"%d",expr->compound_literal.id);
        const std::string name = file_hash() + buf;
        e->Begin(Code::Section::Data, name,
                 get_ctype_alignment(expr->compound_literal.type),
                 false, // required
                 false, // duplicable
                 false // replaceable
                 );
        assert(expr->compound_literal.initializer);
        e->Reserve(get_ctype_size(expr->compound_literal.type));
        e->Require(name + "##init");

        // .initdata name
        e->Begin(Code::Section::InitData, name + "##init",
                 0,
                 true, // required
                 false, // duplicable
                 false // replaceable
                 );
        run_initializer(skip_typeref(expr->compound_literal.type), name, 0, expr->compound_literal.initializer);
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
