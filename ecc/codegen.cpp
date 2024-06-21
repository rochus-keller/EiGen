/* This is a version of chibicc codegen which generates Eigen intermediate code
 * instead of x86_64. 
 * Function arguments are passed by stack in reverse order. Struct and union
 * returns by value are handled via pointer as first argument to caller 
 * allocated memory.
 *
 * (c) 2024 Rochus Keller (me@rochus-keller.ch)
 *
 * Made available under the same license as chibicc
 */

#include <iostream>
#include <unordered_map>
#include <deque>
#include <bitset>
#include <sstream>
#include "layout.hpp"
#include "cdemitter.hpp"
#include "cdemittercontext.hpp"
#include "stdcharset.hpp"
#include "stringpool.hpp"
#include "strdiagnostics.hpp"
#include "cdgenerator.hpp"
using namespace ECS;

// This version of codegen was derived from https://software.openbrace.org/attachments/315

extern "C" {
#include "chibicc.h"
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
static std::unordered_map<const char*, Label*> labels;
static std::deque<Label> clabels;
static Label* return_label = 0;

static FILE *output_file;
static int depth;
static Obj *current_fn;
static Code::Type returnType;
static int pc, infunc = 0;

__attribute__((format(printf, 1, 2)))
static void println(char *fmt, ...) {

    va_list ap;
    va_start(ap, fmt);
    vfprintf(output_file, fmt, ap);
    va_end(ap);
    if( infunc && fmt[0] == ' ' && fmt[1] == ' ' && fmt[2] != ';' )
    {
        pc++;
        if( pc % 10 == 0 )
            fprintf(output_file,"\t; pc %d", pc );
    }
    fprintf(output_file, "\n");
}

enum EcsTypes { u1, u2, u4, u8, s1, s2, s4, s8, f4, f8, ptr, fun, MaxType };

struct EcsType {
    uint8_t type;
    uint8_t width;
} ecsTypes[] = {
    { u1, 8 },
    { u2, 16 },
    { u4, 32 },
    { u8, 64 },
    { s1, 8 },
    { s2, 16 },
    { s4, 32 },
    { s8, 64 },
    { f4, 32 },
    { f8, 64 },
    { ptr, 0 },
    { fun, 0 },
};

static Code::Type types[MaxType];

static uint8_t getTypeId(Type *ty) {

    switch (ty->kind) {
    case TY_CHAR:
        return ty->is_unsigned ? u1 : s1;
    case TY_SHORT:
        return ty->is_unsigned ? u2 : s2;
    case TY_INT:
        if( ty->size == 2 )
            return ty->is_unsigned ? u2 : s2;
        else if( ty->size == 4 )
            return ty->is_unsigned ? u4 : s4;
        else if( ty->size == 8 )
            return ty->is_unsigned ? u8 : s8;
        else
            assert(0);
    case TY_LONG:
        if( ty->size == 2 )
            return ty->is_unsigned ? u2 : s2;
        else if( ty->size == 4 )
            return ty->is_unsigned ? u4 : s4;
        else if( ty->size == 8 )
            return ty->is_unsigned ? u8 : s8;
        else
            assert(0);
    case TY_LONGLONG:
        return ty->is_unsigned ? u8 : s8;
    case TY_FLOAT:
        return f4;
    case TY_DOUBLE:
    case TY_LDOUBLE:
        return f8;
    case TY_ENUM:
        return s4; // RISK
    case TY_PTR:
        if( ty->base && ty->base->kind == TY_FUNC )
            return fun;
        else
            return ptr;
    case TY_FUNC:
        return fun;
    case TY_ARRAY:
        return ptr; // RISK

    }
    if( target_pointer_width == 4 )
        return u4;
    else
        return u8;
}

static Code::Type getCodeType(Type *ty) {

    return types[getTypeId(ty)];
}

static void init_types()
{
    for( int i = 0; i < MaxType; i++ )
    {
        switch(i)
        {
        case u1:
            types[i] = Code::Unsigned(1);
            break;
        case u2:
            types[i] = Code::Unsigned(2);
            break;
        case u4:
            types[i] = Code::Unsigned(4);
            break;
        case u8:
            types[i] = Code::Unsigned(8);
            break;
        case s1:
            types[i] = Code::Signed(1);
            break;
        case s2:
            types[i] = Code::Signed(2);
            break;
        case s4:
            types[i] = Code::Signed(4);
            break;
        case s8:
            types[i] = Code::Signed(8);
            break;
        case f4:
            types[i] = Code::Float(4);
            break;
        case f8:
            types[i] = Code::Float(8);
            break;
        case ptr:
            types[i] = Code::Pointer(target_pointer_width);
            break;
        case fun:
            types[i] = Code::Function(target_pointer_width);
            break;
        }
    }
}


static uint8_t getTypeWidth(Type *ty) {

    return ecsTypes[ getTypeId(ty) ].width;
}


static Smop gen_expr(Node *node);
static void gen_stmt(Node *node);


static int count(void) {

    static int i = 1;
    return i++;
}

static const char* file_path(int file_no)
{

    File **files = get_input_files();
    for (int i = 0; files[i]; i++)
        if( files[i]->file_no == file_no )
            return files[i]->name;
    return "";
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

static std::string getName(Obj * o)
{
    if( o->is_static && o->name[0] != '.' )
    {
        const int len = 9;
        char buf[len];
        name_hash(base_file,buf,len);
        std::string name = buf;
        name += '#';
        std::string file = file_name(base_file);
        for(int i = 0; i < file.size(); i++ )
        {
            const char ch = file[i];
            if( !::isalnum(ch) && ch != '_' && ch != '.' )
                file[i] = '_';
        }
        name += file;
        name += '#';
        name += o->name;
        return name;
    }else
        return o->name;
}

static void pushRes(const Code::Type& type, const Smop& reg) {

    e->Push(e->Convert(type,reg));
    depth++;
}

static Smop pop(const Code::Type& type) {

    Smop res = e->Pop(type); // pop %s %s", type, arg
    depth--;
    return res;
}

// Round up `n` to the nearest multiple of `align`. For instance,
// align_to(5, 8) returns 8 and align_to(11, 8) returns 16.
int align_to(int n, int align) {

    return (n + align - 1) / align * align;
}

// Compute the absolute address of a given node.
// It's an error if a given node does not reside in memory.
static Smop gen_addr(Node *node) {

    switch (node->kind) {
    case ND_VAR:
        // Variable-length array, which is always local.
        if (node->var->ty->kind == TY_VLA) {
            return (Code::Reg(types[ptr],Code::RFP, node->var->offset)); // mov ptr $0, ptr $fp%+d"
        }

        // Local variable
        if (node->var->is_local) {
            return (Code::Reg(types[ptr],Code::RFP, node->var->offset)); // mov ptr $0, ptr $fp%+d"
        }

#if 0
        // TODO
        if (opt_fpic) {
            // Thread-local variable
            if (node->var->is_tls) {
                println("  data16 lea %s@tlsgd(%%rip), %%rdi", node->var->name);
                println("  .value 0x6666");
                println("  rex64");
                println("  call __tls_get_addr@PLT");
                return;
            }

            // Function or global variable
            println("  mov %s@GOTPCREL(%%rip), %%rax", node->var->name);
            return;
        }

        // Thread-local variable
        if (node->var->is_tls) {
            println("  mov %%fs:0, %%rax");
            println("  add $%s@tpoff, %%rax", node->var->name);
            return;
        }
#endif
        // Function
        if (node->ty->kind == TY_FUNC) {
            return (Code::Adr(types[fun],getName(node->var))); // mov fun $0, fun @%s
        }

        // Global variable
        return (Code::Adr(types[ptr],getName(node->var))); // mov ptr $0, ptr @%s
    case ND_DEREF:
        return gen_expr(node->lhs);
    case ND_COMMA:
        gen_expr(node->lhs); // ignore result
        return gen_addr(node->rhs);
    case ND_MEMBER: {
        Smop tmp = gen_addr(node->lhs);
        return e->Add(e->Convert(types[ptr],tmp), Code::Imm(types[ptr],node->member->offset)); // add ptr $0, ptr $0, ptr %d
    }
    case ND_FUNCALL:
        if (node->ret_buffer) {
            return gen_expr(node);
        }
        break;
    case ND_ASSIGN:
    case ND_COND:
        if (node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION) {
            return gen_expr(node);
        }
        break;
    case ND_VLA_PTR:
        return (Code::Reg(types[ptr], Code::RFP,node->var->offset)); // mov ptr $0, ptr $fp%+d
    }

    error_tok(node->tok, "not an lvalue");
    return Smop();
}

// Load a value from where $0 is pointing to.
static void load(Type *ty, Smop& tmp) {

    switch (ty->kind) {
    case TY_ARRAY:
    case TY_STRUCT:
    case TY_UNION:
    case TY_FUNC:
    case TY_VLA:
        // If it is an array, do not attempt to load a value to the
        // register because in general we can't load an entire array to a
        // register. As a result, the result of an evaluation of an array
        // becomes not the array itself but the address of the array.
        // This is where "array is automatically converted to a pointer to
        // the first element of the array in C" occurs.
        return;
    }

    const Code::Type type = getCodeType(ty);
    tmp = e->MakeMemory(type,tmp); // mov %s $0, %s [$0]
}

static void store(Type *ty, const Smop& lhs, const Smop& rhs) {

    switch (ty->kind) {
    case TY_STRUCT:
    case TY_UNION:
        // copy ptr %s, ptr $0, ptr %d", tmp, ty->size);
        e->Copy(lhs, rhs, Code::Imm(types[ptr],ty->size));
        return;
    }

    const Code::Type type = getCodeType(ty);
    // mov %s [%s], %s $0", type, tmp, type );
    e->Move(e->MakeMemory(type,lhs),rhs);
}

static void cast(Type *from, Type *to, Smop& reg) {


    if (to->kind == TY_VOID)
        return;

    if (to->kind == TY_BOOL) {
        Code::Type type = getCodeType(from);
        Label label = e->CreateLabel();
        e->BranchNotEqual(label,Code::Imm(type,0),reg); // breq +2, %s 0, %s %s", type, type, reg
        reg = e->Set (label, Code::Imm(type,0), Code::Imm(type,1));
        return;
    }

    const Code::Type t1 = getCodeType(from);
    const Code::Type t2 = getCodeType(to);
    if( t1 != t2 )
        reg = e->Convert(t2,reg); // conv %s %s, %s %s", ecsTypes[t2].name, reg, ecsTypes[t1].name, reg
}

static int push_struct(Type *ty, const Smop& reg) {

    int sz = align_to(ty->size, target_stack_align);
    e->Subtract(Code::Reg(types[ptr],Code::RSP), Code::Reg(types[ptr],Code::RSP),
                Code::Imm(types[ptr],sz)); // sub	ptr $sp, ptr $sp, ptr %d
    const int res = sz / target_stack_align;
    depth += res;
    e->Copy(Code::Reg(types[ptr],Code::RSP), reg, Code::Imm(types[ptr],sz)); // copy	ptr $sp, ptr $0, ptr %d"
    return res;
}

static int push_args2(Node *args) {

    if (!args)
        return 0;

    // invert order of arguments
    int res = push_args2(args->next);

    Smop arg = gen_expr(args);

    switch (args->ty->kind) {
    case TY_STRUCT:
    case TY_UNION:
        res += push_struct(args->ty, arg);
        break;
    default:
        pushRes(getCodeType(args->ty), arg);
        res++;
        break;
    }
    return res;
}

static int push_args(Node *node) {

    int stack = 0;

    for (Node *arg = node->args; arg; arg = arg->next) {
        arg->pass_by_stack = true;
    }

    stack += push_args2(node->args);

    // If the return type is a large struct/union, the caller passes
    // a pointer to a buffer as if it were the first argument.
    if (node->ret_buffer) {
        Smop res = Code::Reg(types[ptr], Code::RFP,node->ret_buffer->offset); // mov ptr $0, ptr $fp%+d
        pushRes(types[ptr], res);
        stack++;
    }

    return stack;
}

// copy struct pointed to by $0 to the local var at offset
static void copy_struct_mem(const Smop& reg) {

    Type *ty = current_fn->ty->return_ty;
    Obj *var = current_fn->params;

    e->Copy(Code::Reg(types[ptr],Code::RFP, var->offset),
            reg,Code::Imm(types[ptr],ty->size)); // copy ptr $fp%+d, ptr $0, ptr %d
}

static void builtin_alloca(void) {
    // TODO
#if 0
    // Align size to 16 bytes.
    println("  add $15, %%rdi");
    println("  and $0xfffffff0, %%edi");

    // Shift the temporary area by %rdi.
    println("  mov %d(%%rbp), %%rcx", current_fn->alloca_bottom->offset);
    println("  sub %%rsp, %%rcx");
    println("  mov %%rsp, %%rax");
    println("  sub %%rdi, %%rsp");
    println("  mov %%rsp, %%rdx");
    println("1:");
    println("  cmp $0x0, %%rcx");
    println("  je 2f");
    println("  mov (%%rax), %%r8b");
    println("  mov %%r8b, (%%rdx)");
    println("  inc %%rdx");
    println("  inc %%rax");
    println("  dec %%rcx");
    println("  jmp 1b");
    println("2:");

    // Move alloca_bottom pointer.
    println("  mov %d(%%rbp), %%rax", current_fn->alloca_bottom->offset);
    println("  sub %%rdi, %%rax");
    println("  mov %%rax, %d(%%rbp)", current_fn->alloca_bottom->offset);
#endif
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

static void loc(Token * tok)
{
    static int file_no = 0, line_no = 0;

    if( tok->file->file_no != file_no || tok->line_no != line_no )
    {
        std::ostringstream s;
        s << "line " << file_name(file_path(tok->file->file_no)) << ":" << tok->line_no;
        e->Comment(s.str().c_str());
        file_no = tok->file->file_no;
        line_no = tok->line_no;
    }
}

static Type* getFuncReturn(Type* ty)
{
    if( ty == 0 )
        return 0;
    if( ty->kind == TY_PTR )
        return getFuncReturn(ty->base); // function pointer go this way
    if( ty->kind == TY_FUNC && ty->return_ty && ty->return_ty->kind != TY_VOID )
        return ty->return_ty;
    return 0;
}

// Generate code for a given node.
static Smop gen_expr(Node *node) {

    loc(node->tok);

    switch (node->kind) {
    case ND_NULL_EXPR:
        return Smop();
    case ND_NUM: {

        const Code::Type ty = getCodeType(node->ty);
        switch (node->ty->kind)
        {
        case TY_FLOAT:
        case TY_DOUBLE:
        case TY_LDOUBLE: {
            return (Code::FImm(ty,node->fval)); // mov %s $0, %s %Lf
        }
        }
        return (Code::Imm(ty,node->val)); // mov %s $0, %s %Ld
    }
    case ND_NEG: {

        Smop tmp = gen_expr(node->lhs);
        const Code::Type type = getCodeType(node->ty);
        return e->Negate(e->Convert(type,tmp)); // neg %s $0, %s $0
    }
    case ND_VAR: {

        Smop tmp = gen_addr(node);
        load(node->ty, tmp);
        return tmp;
    }
    case ND_MEMBER: {

        Smop tmp = gen_addr(node);
        load(node->ty, tmp);

        Member *mem = node->member;
        if (mem->is_bitfield) {
            const uint8_t w = getTypeWidth(mem->ty);
            const Code::Type nm = getCodeType(mem->ty);
            // align the bitfield to the msb of the underlying type
            tmp = e->ShiftLeft(e->Convert(nm,tmp), Code::Imm(nm,w - mem->bit_width - mem->bit_offset)); // lsh %s $0, %s $0, %s %d
            tmp = e->ShiftRight(tmp, Code::Imm(nm,w - mem->bit_width)); // rsh %s $0, %s $0, %s %d
        }
        return tmp;
    }
    case ND_DEREF: {

        Smop tmp = gen_expr(node->lhs);
        load(node->ty, tmp);
        return tmp;
    }
    case ND_ADDR:

        return gen_addr(node->lhs);
    case ND_ASSIGN: {

        Smop lhs = gen_addr(node->lhs);
        e->SaveRegister(lhs);
        Smop rhs = gen_expr(node->rhs);
        e->RestoreRegister(lhs);

        if (node->lhs->kind == ND_MEMBER && node->lhs->member->is_bitfield) {

            const Code::Type rty = getCodeType(node->rhs->ty);

            Smop savedRhs = rhs; // mov %s %s, %s $0

            // If the lhs is a bitfield, we need to read the current value
            // from memory and merge it with a new value.
            Member *mem = node->lhs->member;
            const Code::Type mty = getCodeType(mem->ty);

            Smop rdi = e->Convert(rty,rhs); // mov %s %s, %s $0
            rdi = e->And(rdi, Code::Imm(rty,(1L << mem->bit_width) - 1)); // and  %s %s, %s %s,  %s %ld
            rdi = e->Convert(mty,rdi);
            rdi = e->ShiftLeft(rdi, Code::Imm(mty,mem->bit_offset)); // lsh %s %s, %s %s, %s %d

            rhs = e->Move(e->MakeMemory(mty,lhs)); // mov ptr $0, ptr [$sp]

            const uint64_t mask = ((1L << mem->bit_width) - 1) << mem->bit_offset;
            Smop r9;
            if( mem->ty->is_unsigned ) {
                const uint64_t mask2 = (((uint64_t(1) << ((mem->ty->size-1)*8)) - 1) << 8) | 255;
                r9 = Code::UImm(mty, ~mask & mask2); // mov %s %s, %s %lu
            } else {
                r9 = Code::Imm(mty, ~mask); // mov %s %s, %s %ld
            }
            rhs = e->And(e->Convert(mty,rhs), r9); // and %s $0, %s $0, %s %s
            rhs = e->Or(rhs, rdi); // or %s $0, %s $0, %s %s

            store(node->ty, lhs, rhs);
            return savedRhs; // mov %s $0, %s %s
        }else {
            store(node->ty, lhs, rhs);
            return rhs;
        }
    }
    case ND_STMT_EXPR:

        for (Node *n = node->body; n; n = n->next)
            gen_stmt(n);
        return Smop();
    case ND_COMMA:

        gen_expr(node->lhs); // ignore result
        return gen_expr(node->rhs);
    case ND_CAST: {
        Smop tmp = gen_expr(node->lhs);
        cast(node->lhs->ty, node->ty, tmp);
        return tmp;
    }
    case ND_MEMZERO: {

        Smop lhs (Code::Reg(types[ptr],Code::RFP,node->var->offset)); // mov ptr $0, ptr $fp%+d
        e->Fill(lhs,Code::Imm(types[ptr],node->var->ty->size), Code::Imm(types[u1],0)); // fill ptr $0, ptr %d, u1 0
        return Smop();
    }
    case ND_COND: {

        Smop cond = gen_expr(node->cond);
        const Code::Type type = getCodeType(node->cond->ty);
        Label lelse = e->CreateLabel();
        Label lend = e->CreateLabel();
        e->BranchEqual(lelse,Code::Imm(type,0),e->Convert(type,cond)); // breq .L.else.%d, %s 0, %s $0
        Smop res = e->MakeRegister(gen_expr(node->then));
        e->Fix(res);
        e->Branch(lend); // br .L.end.%d
        lelse();
        e->Move(res,gen_expr(node->els));
        e->Unfix(res);
        lend();
        return res;
    }
    case ND_NOT: {

        Smop tmp = gen_expr(node->lhs);
        const Code::Type type = getCodeType(node->lhs->ty);

        Label label = e->CreateLabel();
        e->BranchEqual(label,Code::Imm(type,0),e->Convert(type,tmp)); // breq +2, %s 0, %s $0
        tmp = e->Set(label,Code::Imm(type,0), Code::Imm(type,1));
        return tmp;
    }
    case ND_BITNOT: {

        Smop tmp = gen_expr(node->lhs);
        const Code::Type type = getCodeType(node->lhs->ty);
        tmp = e->Complement(e->Convert(type,tmp)); // not %s $0, %s $0
        return tmp;
    }
    case ND_LOGAND: {

        Smop lhs = gen_expr(node->lhs);
        Code::Type type = getCodeType(node->lhs->ty);
        Label lfalse = e->CreateLabel();
        e->BranchEqual(lfalse,Code::Imm(type,0),e->Convert(type,lhs)); // breq .L.false.%d, %s 0, %s $0
        Smop rhs = gen_expr(node->rhs);
        type = getCodeType(node->rhs->ty);
        e->BranchEqual(lfalse,Code::Imm(type,0),e->Convert(type,rhs)); // breq .L.false.%d, %s 0, %s $0
        return e->Set(lfalse,Code::Imm(types[s4],1),Code::Imm(types[s4],0));
    }
    case ND_LOGOR: {

        Smop lhs = gen_expr(node->lhs);
        Code::Type type = getCodeType(node->lhs->ty);
        Label ltrue = e->CreateLabel();
        e->BranchNotEqual(ltrue,Code::Imm(type,0),e->Convert(type,lhs)); // brne .L.true.%d, %s 0, %s $0
        Smop rhs = gen_expr(node->rhs);
        type = getCodeType(node->rhs->ty);
        e->BranchNotEqual(ltrue,Code::Imm(type,0),e->Convert(type,rhs)); // brne .L.true.%d, %s 0, %s $0
        return e->Set(ltrue,Code::Imm(types[s4],0),Code::Imm(types[s4],1));
    }
    case ND_FUNCALL: {
#if 0
        // TODO
        if (node->lhs->kind == ND_VAR && !strcmp(node->lhs->var->name, "alloca")) {
            gen_expr(node->args);
            println("  mov %%rax, %%rdi");
            builtin_alloca();
            return;
        }
#endif

        const RestoreRegisterState restore(*e);

        const int stack_slots = push_args(node);
        Smop f = gen_expr(node->lhs);

        Type* ret = getFuncReturn(node->lhs->ty);
        Smop res;
        if( ret )
            res = e->Call(getCodeType(ret), f,stack_slots * target_stack_align); // call fun $0, %d
        else
            e->Call(f,stack_slots * target_stack_align); // call fun $0, %d

        depth -= stack_slots;

        return res;
    }
    case ND_LABEL_VAL:
#if 0
        println("  lea %s(%%rip), %%rax", node->unique_label);
#else
        error_tok(node->tok,"label-as-value not yet supported"); // TODO
#endif
        return Smop();
    case ND_CAS: {
#if 0
        gen_expr(node->cas_addr);
        pushRes();
        gen_expr(node->cas_new);
        pushRes();
        gen_expr(node->cas_old);
        println("  mov %%rax, %%r8");
        load(node->cas_old->ty->base);
        pop("%rdx"); // new
        pop("%rdi"); // addr

        int sz = node->cas_addr->ty->base->size;
        // TODO println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz));
        println("  sete %%cl");
        println("  je 1f");
        println("  mov %s, (%%r8)", reg_ax(sz));
        println("1:");
        println("  movzbl %%cl, %%eax");
#else
        error_tok(node->tok,"atomic compare-and-swap not yet supported"); // TODO
#endif
        return Smop();
    }
    case ND_EXCH: {
#if 0
        gen_expr(node->lhs);
        pushRes();
        gen_expr(node->rhs);
        pop("%rdi");

        int sz = node->lhs->ty->base->size;
        println("  xchg %s, (%%rdi)", reg_ax(sz));
#else
        error_tok(node->tok,"atomic exchange not yet supported"); // TODO
#endif
        return Smop();
    }
    }

    Smop rhs = gen_expr(node->rhs);
    e->SaveRegister(rhs);
    Smop lhs = gen_expr(node->lhs);
    e->RestoreRegister(rhs);

    const Code::Type lhsT = getCodeType(node->lhs->ty);
    Code::Type rhsT = getCodeType(node->rhs->ty);

    if( lhsT != rhsT )
    {
        cast(node->rhs->ty, node->lhs->ty, rhs);
        rhsT = lhsT;
    }

    switch (node->kind) {
    case ND_ADD:
        return e->Add(e->Convert(lhsT,lhs),rhs);
        // add %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    case ND_SUB:
        return e->Subtract(e->Convert(lhsT,lhs),rhs);
        // sub %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    case ND_MUL:
        return e->Multiply(e->Convert(lhsT,lhs),rhs);
        // mul %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    case ND_DIV:
        return e->Divide(e->Convert(lhsT,lhs),rhs);
        // div %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    case ND_MOD:
        return e->Modulo(e->Convert(lhsT,lhs),rhs);
        // mod %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    case ND_BITAND:
        return e->And(e->Convert(lhsT,lhs),rhs);
        // and %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    case ND_BITOR:
        return e->Or(e->Convert(lhsT,lhs),rhs);
        // or %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    case ND_BITXOR:
        return e->ExclusiveOr(e->Convert(lhsT,lhs),rhs);
        // xor %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    case ND_EQ:
    case ND_NE:
    case ND_LT:
    case ND_LE:
    {
        Label ltrue = e->CreateLabel();
        if (node->kind == ND_EQ) {
            e->BranchEqual(ltrue,e->Convert(lhsT,lhs),rhs);
            // breq +2, %s $0, %s %s", lhsT, rhsT, tmpname
        } else if (node->kind == ND_NE) {
            e->BranchNotEqual(ltrue,e->Convert(lhsT,lhs),rhs);
            // brne +2, %s $0, %s %s", lhsT, rhsT, tmpname
        } else if (node->kind == ND_LT) {
            e->BranchLessThan(ltrue,e->Convert(lhsT,lhs),rhs);
            // brlt +2, %s $0, %s %s", lhsT, rhsT, tmpname
        } else if (node->kind == ND_LE) {
            e->BranchGreaterEqual(ltrue,rhs,e->Convert(lhsT,lhs));
            // brge +2, %s %s, %s $0", rhsT, tmpname, lhsT
        }

        return e->Set(ltrue,Code::Imm(types[s4],0),Code::Imm(types[s4],1));
    } break;
    case ND_SHL:
        return e->ShiftLeft(e->Convert(lhsT,lhs),rhs);
        // lsh %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    case ND_SHR:
        return e->ShiftRight(e->Convert(lhsT,lhs),rhs);
        // rsh %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
    default:
        error_tok(node->tok, "invalid expression");
        break;
    }
    return Smop();
}

static void gen_stmt(Node *node) {


    loc(node->tok);

    switch (node->kind) {
    case ND_IF: {

        Smop cond = gen_expr(node->cond);
        const Code::Type type = getCodeType(node->cond->ty);
        Label lelse = e->CreateLabel();
        Label lend = e->CreateLabel();
        e->BranchEqual(lelse,Code::Imm(type,0),e->Convert(type,cond));
        // breq .L.else.%d, %s 0, %s $0", c, type, type
        gen_stmt(node->then);
        e->Branch(lend); // br .L.end.%d
        lelse();
        if (node->els)
            gen_stmt(node->els);
        lend();
        return;
    }
    case ND_FOR: {

        if (node->init)
            gen_stmt(node->init);
        Label lbegin = e->CreateLabel();
        Label lbreak = e->CreateLabel();
        labels[node->brk_label] = &lbreak;
        Label lcont = e->CreateLabel();
        labels[node->cont_label] = &lcont;
        lbegin();
        if (node->cond) {
            Smop cond = gen_expr(node->cond);
            const Code::Type type = getCodeType(node->cond->ty);
            e->BranchEqual(lbreak,Code::Imm(type,0),e->Convert(type,cond));
            // breq %s, %s 0, %s $0", node->brk_label, type, type
        }
        gen_stmt(node->then);
        lcont();
        if (node->inc)
            gen_expr(node->inc);
        e->Branch(lbegin); // br .L.begin.%d
        lbreak();
        labels.erase(node->brk_label);
        labels.erase(node->cont_label);
        return;
    }
    case ND_DO: {

        Label lbegin = e->CreateLabel();
        Label lbreak = e->CreateLabel();
        labels[node->brk_label] = &lbreak;
        Label lcont = e->CreateLabel();
        labels[node->cont_label] = &lcont;
        lbegin();
        gen_stmt(node->then);
        lcont();
        Smop cond = gen_expr(node->cond);
        const Code::Type type = getCodeType(node->cond->ty);
        e->BranchNotEqual(lbegin,Code::Imm(type,0),e->Convert(type,cond));
        // brne .L.begin.%d, %s 0, %s $0", c, type, type
        lbreak();
        labels.erase(node->brk_label);
        labels.erase(node->cont_label);
        return;
    }
    case ND_SWITCH: {

        Smop cond = gen_expr(node->cond);

        const Code::Type cond_type = getCodeType(node->cond->ty);

        std::deque<const char*> kk;
        std::deque<Label> ll;
        for (Node *n = node->case_next; n; n = n->case_next) {
            kk.push_back(n->label); ll.push_back(e->CreateLabel());
            labels[n->label] = &ll.back();
            if (n->begin == n->end) {
                e->BranchEqual(ll.back(),Code::Imm(cond_type,n->begin),e->Convert(cond_type,cond));
                // breq %s, %s %ld, %s $0", n->label, cond_type, n->begin, cond_type
                continue;
            }

            // [GNU] Case ranges
            cond = e->Convert(cond_type,cond); // mov %s %s, %s $0
            cond = e->Subtract(cond, Code::Imm(cond_type,n->begin));
                   // sub %s %s, %s %s, %s %ld", cond_type, di, cond_type, di, cond_type, n->begin
            // lhs <= rhs -> rhs >= lhs
            e->BranchGreaterEqual(ll.back(),cond, Code::Imm(cond_type,n->end - n->begin));
                //  brge %s, %s %s, %s %ld", n->label, cond_type, di, cond_type, n->end - n->begin
        }

        if (node->default_case)
        {
            kk.push_back(node->default_case->label); ll.push_back(e->CreateLabel());
            labels[node->default_case->label] = &ll.back();
            e->Branch(ll.back());
            // br %s", node->default_case->label
        }

        Label lbrk = e->CreateLabel();
        labels[node->brk_label] = &lbrk;
        e->Branch(lbrk); // br %s", node->brk_label
        gen_stmt(node->then);
        lbrk();
        labels.erase(node->brk_label);
        for( auto i = kk.begin(); i != kk.end(); ++i)
            labels.erase((*i));
    }
        return;
    case ND_CASE: {

        auto i = labels.find(node->label);
        assert(i != labels.end());
        (*(*i).second)();
        gen_stmt(node->lhs);
        return;
    }
    case ND_BLOCK:

        for (Node *n = node->body; n; n = n->next)
            gen_stmt(n);
        return;
    case ND_GOTO: {

        auto i = labels.find(node->unique_label);
        if(i == labels.end())
        {
            clabels.push_back(e->CreateLabel());
            labels[node->unique_label] = &clabels.back();
            e->Branch(clabels.back());
        }else
            e->Branch(*(*i).second); // br %s"
        return;
    }
    case ND_GOTO_EXPR:
        gen_expr(node->lhs);
#if 0
        println("  jmp *%%rax");
#else
        error_tok(node->tok,"goto labels-as-values not yet supported"); // TODO
#endif
        return;
    case ND_LABEL: {

        auto i = labels.find(node->unique_label);
        if(i == labels.end())
        {
            clabels.push_back(e->CreateLabel());
            labels[node->unique_label] = &clabels.back();
            clabels.back()();
        }else
            (*(*i).second)();
        gen_stmt(node->lhs);
        return;
    }
    case ND_RETURN:

        if (node->lhs) {
            Smop lhs = gen_expr(node->lhs);
            Code::Type lhsT = getCodeType(node->lhs->ty);

            switch (node->lhs->ty->kind) {
            case TY_STRUCT:
            case TY_UNION:
                copy_struct_mem(lhs);
                break;
            case TY_VOID:
            case TY_VLA:
                break;
            default:
                e->Move (Code::Reg {lhsT, Code::RRes}, e->Convert(lhsT,lhs));
                break;
            }
            returnType = lhsT;
        }
        assert( return_label != nullptr );
        e->Branch(*return_label); // br .L.return.%s
        return;
    case ND_EXPR_STMT:
        gen_expr(node->lhs);
        return;
    case ND_ASM:
        error_tok(node->tok,"inline assembler not yet supported"); // TODO
        return;
    }

    error_tok(node->tok, "invalid statement");
}

// Assign offsets to local variables.
static void assign_lvar_offsets(Obj *prog) {

    for (Obj *fn = prog; fn; fn = fn->next) {
        if (!fn->is_function)
            continue;

        int top = 2 * target_stack_align; // previous frame and return address

        // Assign offsets to parameters.
        for (Obj *var = fn->params; var; var = var->next) {
            top = align_to(top, MAX(target_stack_align, var->align));
            var->offset = top;
            top += var->ty->size;
        }

        int bottom = 0;

        // Assign offsets to local variables.
        for (Obj *var = fn->locals; var; var = var->next) {
            if (var->offset)
                continue;

            bottom += var->ty->size;
            bottom = align_to(bottom, var->align);
            var->offset = -bottom;
        }

        fn->stack_size = align_to(bottom, target_stack_align); // TODO: orig was 16, i.e. 2 * codegen_StackAlign
    }
}

static Type* getTypeOf(Obj *prog, const char* name )
{
    for (Obj *var = prog; var; var = var->next) {
        if( var->name == name )
            return var->ty;
    }
    return 0;
}

static void emit_data(Obj *prog) {

    for (Obj *var = prog; var; var = var->next) {
        if (var->is_function || !var->is_definition)
            continue;

        // if (var->is_static)
        e->Begin(Code::Section::Data, getName(var), var->align);

        // Common symbol
        if (opt_fcommon && var->is_tentative) {
            // TODO e->Reserve(var->ty->size);
            continue;
        }


        // .data or .tdata
        if (var->init_data) {
#if 0
            // TODO
            if (var->is_tls)
                println("  ; tls");
#endif

            Relocation *rel = var->rel;
            int pos = 0;
            // var->ty is either an ARRAY or STRUCT or UNION, but initdata is always array of char
            while (pos < var->ty->size) {
                if (rel && rel->offset == pos) {
                    Type* ty = getTypeOf(prog,*rel->label);
                    Code::Type type(Code::Type::Pointer,target_pointer_width);
                    if( ty && ty->kind == TY_FUNC )
                        type.model = Code::Type::Function;
                    e->Define(Code::Adr(type,*rel->label));
                    rel = rel->next;
                    pos += target_pointer_width;
                } else {
                    const char d = var->init_data[pos++];
                    e->Define(Code::Imm(types[s1],d));
                }
            }
#if 0
            // TODO
            if (var->is_tls)
                println("  ; end tls");
#endif
            continue;
        }
    }
}

static void print_var_names(Obj* fn)
{
#if 0
    // TODO
    for (Obj *var = fn->params; var; var = var->next) {
        println("  ; param '%s' %s offset=%d size=%d align=%d", var->name, getTypeName(var->ty),
                var->offset, var->ty->size, var->align );
    }
    for (Obj *var = fn->locals; var; var = var->next) {
        if( var->offset > 0 )
            break; // hit a param; apparently chibicc links params just behind locals
        println("  ; local '%s' %s offset=%d size=%d align=%d", var->name, getTypeName(var->ty),
                var->offset, var->ty->size, var->align );
    }
#endif
}

static void emit_text(Obj *prog) {

    for (Obj *fn = prog; fn; fn = fn->next) {
        if (!fn->is_function || !fn->is_definition)
            continue;

        // No code is emitted for "static inline" functions
        // if no one is referencing them.
        if (!fn->is_live)
            continue;

        returnType = Code::Type();
        pc = 0;
        infunc = 1;

        // NOTE: static is not supported by ECS; therefore getName provides some unique mangling
        e->Begin(Code::Section::Code, getName(fn) );
        labels.clear();
        clabels.clear();
        Label lret = e->CreateLabel();
        return_label = &lret;

        current_fn = fn;

        const int isMain = !fn->is_static && strcmp(fn->name,"main") == 0;

        print_var_names(fn);

        // Prologue
        if( !isMain && target_has_linkregister )
            e->Push(Code::Reg(types[fun],Code::RLink)); // push fun $lnk

        e->Enter(fn->stack_size); // enter %d
        // TODO println("  ; alloca_bottom offset: %d", fn->alloca_bottom->offset);

        // Emit code
        gen_stmt(fn->body);
        if(depth != 0)
            error("stack depth not zero when leaving function %s", fn->name);

        // Epilogue
        lret(); // .L.return.%s:", fn->name
        if( fn->ty->return_ty && fn->ty->return_ty->kind != TY_VOID )
        {
            if( returnType.model == Code::Type::Void )
                e->Move(Code::Reg(types[s4],Code::RRes),Code::Imm(types[s4],0));
        }
        e->Leave();
        if( isMain )
        {
            if( returnType.model == Code::Type::Void )
                e->Push(Code::Reg {types[s4], Code::RRes});
            else
                e->Push(Code::Reg {returnType, Code::RRes});
            e->Call(Code::Adr(types[fun],"_Exit"),0); // call fun @_Exit, 0
        }else
            e->Return();
        depth = 0;
        infunc = 0;
        return_label = 0;
        clabels.clear();
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
void codegen(Obj *prog, FILE *out) {
    output_file = out;

    Layout layout(
        { basic_type(TY_INT)->size, 1, 8},
        {4, 4, 8},
        target_pointer_width,
        target_pointer_width,
        {0, target_stack_align, target_stack_align},
        true
    );
    Code::Platform platform(layout,target_has_linkregister);
    MyEmitter emitter(diagnostics,stringPool,charset,platform);
    e = &emitter.ctx;

    init_types();

    assign_lvar_offsets(prog);
    emit_data(prog);
    emit_text(prog);
    e = 0;

    println("; this is Eigen intermediate code, generated by ECC");
    println("; see https://github.com/rochus-keller/EiGen/tree/master/ecc for more information");
    println("; assuming pointer size %d, int size %d, long size %d, stack alignment %d bytes, %s link reg",
            target_pointer_width, basic_type(TY_INT)->size, basic_type(TY_LONG)->size, target_stack_align,
            target_has_linkregister ? "with" : "no" );

    fdostream out_stream(out);
    Code::Generator cdgen(layout,platform);

    cdgen.Generate(emitter.s,targets[target].name,out_stream);
}
}
