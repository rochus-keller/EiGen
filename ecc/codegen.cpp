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
#include "layout.hpp"
#include "cdemitter2.hpp"
#include "stdcharset.hpp"
#include "stringpool.hpp"
#include "strdiagnostics.hpp"
#include "cdgenerator.hpp"
using namespace ECS;

using Smop = Code::Emitter2::SmartOperand;

extern "C" {
#include "chibicc.h"
}

static Code::Emitter2* e = 0;
static std::unordered_map<const char*, Code::Emitter2::Label*> labels;
static std::deque<Code::Emitter2::Label> clabels;
static Code::Emitter2::Label* return_label = 0;

static Smop r0;

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


static void gen_expr(Node *node);
static void gen_stmt(Node *node);


static int count(void) {

    static int i = 1;
    return i++;
}

static void pushRes(const Code::Type& type) {

    e->Push(e->Convert(type,r0));
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
static void gen_addr(Node *node) {

    switch (node->kind) {
    case ND_VAR:
        // Variable-length array, which is always local.
        if (node->var->ty->kind == TY_VLA) {
            r0 = e->Move(Code::Reg(types[ptr],Code::RFP, node->var->offset)); // mov ptr $0, ptr $fp%+d"
            return;
        }

        // Local variable
        if (node->var->is_local) {
            r0 = e->Move(Code::Reg(types[ptr],Code::RFP, node->var->offset)); // mov ptr $0, ptr $fp%+d"
              return;
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
            r0 = e->Move(Code::Adr(types[fun],node->var->name)); // mov fun $0, fun @%s
            return;
        }

        // Global variable
        r0 = e->Move(Code::Adr(types[ptr],node->var->name)); // mov ptr $0, ptr @%s
        return;
    case ND_DEREF:
        gen_expr(node->lhs);
        return;
    case ND_COMMA:
        gen_expr(node->lhs);
        gen_addr(node->rhs);
        return;
    case ND_MEMBER:
        gen_addr(node->lhs);
        r0 = e->Add(e->Convert(types[ptr],r0), Code::Imm(types[ptr],node->member->offset)); // add ptr $0, ptr $0, ptr %d
        return;
    case ND_FUNCALL:
        if (node->ret_buffer) {
            gen_expr(node);
            return;
        }
        break;
    case ND_ASSIGN:
    case ND_COND:
        if (node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION) {
            gen_expr(node);
            return;
        }
        break;
    case ND_VLA_PTR:
        r0 = e->Move(Code::Reg(types[ptr], Code::RFP,node->var->offset)); // mov ptr $0, ptr $fp%+d
        return;
    }

    error_tok(node->tok, "not an lvalue");
}

// Load a value from where $0 is pointing to.
static void load(Type *ty) {

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
    r0 = e->MakeRegister(e->MakeMemory(type,r0)); // mov %s $0, %s [$0]
    // like Move, but reuses the register of r0 instead of allocating another one and really move
}

// Store $0 to the address on top of the stack
static void store(Type *ty) {

    Smop tmpReg = pop(types[ptr]);

    switch (ty->kind) {
    case TY_STRUCT:
    case TY_UNION:
        // copy ptr %s, ptr $0, ptr %d", tmp, ty->size);
        e->Copy(tmpReg, r0, Code::Imm(types[ptr],ty->size));
        return;
    }

    const Code::Type type = getCodeType(ty);
    // mov %s [%s], %s $0", type, tmp, type );
    e->Move(e->MakeMemory(type,tmpReg),r0);
}

static void cast(Type *from, Type *to, Smop& reg) {


    if (to->kind == TY_VOID)
        return;

    if (to->kind == TY_BOOL) {
        Code::Type type = getCodeType(from);
        Code::Emitter2::Label yes = e->CreateLabel();
        e->BranchEqual(yes,Code::Imm(type,0),reg); // breq +2, %s 0, %s %s", type, type, reg
        type = getCodeType(to);
        reg = e->Move(Code::Imm(type,0)); // mov %s %s, %s 0", type, reg, type
        Code::Emitter2::Label end = e->CreateLabel();
        e->Branch(end); // br +1
        yes();
        reg = e->Move(Code::Imm(type,1)); // mov %s %s, %s 1", type, reg, type
        end();
        return;
    }

    const Code::Type t1 = getCodeType(from);
    const Code::Type t2 = getCodeType(to);
    if( t1 != t2 )
        reg = e->Convert(t2,reg); // conv %s %s, %s %s", ecsTypes[t2].name, reg, ecsTypes[t1].name, reg
}

static int push_struct(Type *ty) {

    int sz = align_to(ty->size, target_stack_align);
    e->Subtract(Code::Reg(types[ptr],Code::RSP), Code::Reg(types[ptr],Code::RSP),
                Code::Imm(types[ptr],sz)); // sub	ptr $sp, ptr $sp, ptr %d
    const int res = sz / target_stack_align;
    depth += res;
    e->Copy(Code::Reg(types[ptr],Code::RSP), r0, Code::Imm(types[ptr],sz)); // copy	ptr $sp, ptr $0, ptr %d"
    return res;
}

static int push_args2(Node *args) {

    if (!args)
        return 0;

    // invert order of arguments
    int res = push_args2(args->next);

    gen_expr(args);

    switch (args->ty->kind) {
    case TY_STRUCT:
    case TY_UNION:
        res += push_struct(args->ty);
        break;
    default:
        pushRes(getCodeType(args->ty));
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
        r0 = e->Move(Code::Reg(types[ptr], Code::RFP,node->ret_buffer->offset)); // mov ptr $0, ptr $fp%+d
        pushRes(types[ptr]);
        stack++;
    }

    return stack;
}

// copy struct pointed to by $0 to the local var at offset
static void copy_struct_mem(void) {

    Type *ty = current_fn->ty->return_ty;
    Obj *var = current_fn->params;

    e->Copy(Code::Reg(types[ptr],Code::RFP, var->offset),
            r0,Code::Imm(types[ptr],ty->size)); // copy ptr $fp%+d, ptr $0, ptr %d
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

static const char* file_path(int file_no)
{

    File **files = get_input_files();
    for (int i = 0; files[i]; i++)
        if( files[i]->file_no == file_no )
            return files[i]->name;
    return "";
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
#if 0
        println("  loc \"%s\", %d, 1", file_path(tok->file->file_no), tok->line_no);
#else
        // TODO println("  ; line %s:%d", file_name(file_path(tok->file->file_no)), tok->line_no);
#endif
        file_no = tok->file->file_no;
        line_no = tok->line_no;
    }
}

static void setInt(uint32_t i, Smop& reg)
{
    Code::Type sn(Code::Type::Signed,target_pointer_width);
    reg = e->Move(Code::Imm(sn,i)); // mov s%d %s, s%d %d"

    // using s instead of u: 111 of 149 success with cdrun instead 65
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
static void gen_expr(Node *node) {

    loc(node->tok);

    switch (node->kind) {
    case ND_NULL_EXPR:
        return;
    case ND_NUM: {

        const Code::Type ty = getCodeType(node->ty);
        switch (node->ty->kind)
        {
        case TY_FLOAT:
        case TY_DOUBLE:
        case TY_LDOUBLE: {
            r0 = e->Move(Code::FImm(ty,node->fval)); // mov %s $0, %s %Lf
            return;
        }
        }
        r0 = e->Move(Code::Imm(ty,node->val)); // mov %s $0, %s %Ld
        return;
    }
    case ND_NEG: {

        gen_expr(node->lhs);
        const Code::Type type = getCodeType(node->ty);
        r0 = e->Negate(e->Convert(type,r0)); // neg %s $0, %s $0
        return;
    }
    case ND_VAR:

        gen_addr(node);
        load(node->ty);
        return;
    case ND_MEMBER: {

        gen_addr(node);
        load(node->ty);

        Member *mem = node->member;
        if (mem->is_bitfield) {
            const uint8_t w = getTypeWidth(mem->ty);
            const Code::Type nm = getCodeType(mem->ty);
            // align the bitfield to the msb of the underlying type
            r0 = e->ShiftLeft(e->Convert(nm,r0), Code::Imm(nm,w - mem->bit_width - mem->bit_offset)); // lsh %s $0, %s $0, %s %d
            r0 = e->ShiftRight(r0, Code::Imm(nm,w - mem->bit_width)); // rsh %s $0, %s $0, %s %d
        }
        return;
    }
    case ND_DEREF:

        gen_expr(node->lhs);
        load(node->ty);
        return;
    case ND_ADDR:

        gen_addr(node->lhs);
        return;
    case ND_ASSIGN:

        gen_addr(node->lhs);
        pushRes(types[ptr]);
        gen_expr(node->rhs);

        if (node->lhs->kind == ND_MEMBER && node->lhs->member->is_bitfield) {

            const Code::Type rty = getCodeType(node->rhs->ty);

            // save to r8:
            Smop r8 = e->Move(e->Convert(rty,r0)); // mov %s %s, %s $0

            // If the lhs is a bitfield, we need to read the current value
            // from memory and merge it with a new value.
            Member *mem = node->lhs->member;
            const Code::Type mty = getCodeType(mem->ty);

            Smop rdi = e->Move(e->Convert(rty,r0)); // mov %s %s, %s $0
            rdi = e->And(rdi, Code::Imm(rty,(1L << mem->bit_width) - 1)); // and  %s %s, %s %s,  %s %ld
            cast(node->rhs->ty,mem->ty, rdi);
            rdi = e->ShiftLeft(rdi, Code::Imm(mty,mem->bit_offset)); // lsh %s %s, %s %s, %s %d

            r0 = e->Move(Code::Mem(types[ptr],Code::RSP)); // mov ptr $0, ptr [$sp]
            // $0 is now adr(lhs)
            load(mem->ty);
            // $0 is now val(lhs)

            const unsigned long mask = ((1L << mem->bit_width) - 1) << mem->bit_offset;
            Smop r9;
            if( mem->ty->is_unsigned ) {
                const unsigned long mask2 = ((1L << (mem->ty->size-1)*8) - 1) | (255 << (mem->ty->size-1)*8);
                r9 = e->Move(Code::UImm(mty, ~mask & mask2)); // mov %s %s, %s %lu
            } else
                r9 = e->Move(Code::Imm(mty,~mask)); // mov %s %s, %s %ld
            r0 = e->And(e->Convert(mty,r0), r9); // and %s $0, %s $0, %s %s
            r0 = e->Or(r0, rdi); // or %s $0, %s $0, %s %s
            store(node->ty);

            // restore from r8:
            r0 = e->Move(r8); // mov %s $0, %s %s
            return;
        }else {
            store(node->ty);
            return;
        }
    case ND_STMT_EXPR:

        for (Node *n = node->body; n; n = n->next)
            gen_stmt(n);
        return;
    case ND_COMMA:

        gen_expr(node->lhs);
        gen_expr(node->rhs);
        return;
    case ND_CAST:

        gen_expr(node->lhs);
        cast(node->lhs->ty, node->ty, r0);
        return;
    case ND_MEMZERO:

        r0 = e->Move(Code::Reg(types[ptr],Code::RFP,node->var->offset)); // mov ptr $0, ptr $fp%+d
        e->Fill(r0,Code::Imm(types[ptr],node->var->ty->size), Code::Imm(types[u1],0)); // fill ptr $0, ptr %d, u1 0
        return;
    case ND_COND: {

        gen_expr(node->cond);
        const Code::Type type = getCodeType(node->cond->ty);
        Code::Emitter2::Label lelse = e->CreateLabel();
        Code::Emitter2::Label lend = e->CreateLabel();
        e->BranchEqual(lelse,Code::Imm(type,0),e->Convert(type,r0)); // breq .L.else.%d, %s 0, %s $0
        gen_expr(node->then);
        e->Branch(lend); // br .L.end.%d
        lelse();
        gen_expr(node->els);
        lend();
        return;
    }
    case ND_NOT: {

        gen_expr(node->lhs);
        const Code::Type type = getCodeType(node->lhs->ty);
        Code::Emitter2::Label ltrue = e->CreateLabel();
        Code::Emitter2::Label lend = e->CreateLabel();
        e->BranchEqual(ltrue,Code::Imm(type,0),e->Convert(type,r0)); // breq +2, %s 0, %s $0
        setInt(0,r0);
        e->Branch(lend); // br +1
        ltrue();
        setInt(1,r0);
        lend();
        return;
    }
    case ND_BITNOT: {

        gen_expr(node->lhs);
        const Code::Type type = getCodeType(node->lhs->ty);
        r0 = e->Complement(e->Convert(type,r0)); // not %s $0, %s $0
        return;
    }
    case ND_LOGAND: {

        gen_expr(node->lhs);
        Code::Type type = getCodeType(node->lhs->ty);
        Code::Emitter2::Label lfalse = e->CreateLabel();
        Code::Emitter2::Label lend = e->CreateLabel();
        e->BranchEqual(lfalse,Code::Imm(type,0),e->Convert(type,r0)); // breq .L.false.%d, %s 0, %s $0
        gen_expr(node->rhs);
        type = getCodeType(node->rhs->ty);
        e->BranchEqual(lfalse,Code::Imm(type,0),e->Convert(type,r0)); // breq .L.false.%d, %s 0, %s $0
        setInt(1,r0);
        e->Branch(lend); // br .L.end.%d
        lfalse();
        setInt(0,r0);
        lend();
        return;
    }
    case ND_LOGOR: {

        gen_expr(node->lhs);
        Code::Type type = getCodeType(node->lhs->ty);
        Code::Emitter2::Label ltrue = e->CreateLabel();
        Code::Emitter2::Label lend = e->CreateLabel();
        e->BranchNotEqual(ltrue,Code::Imm(type,0),e->Convert(type,r0)); // brne .L.true.%d, %s 0, %s $0
        gen_expr(node->rhs);
        type = getCodeType(node->rhs->ty);
        e->BranchNotEqual(ltrue,Code::Imm(type,0),e->Convert(type,r0)); // brne .L.true.%d, %s 0, %s $0
        setInt(0,r0);
        e->Branch(lend); // br .L.end.%d
        ltrue();
        setInt(1,r0);
        lend();
        return;
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


        const int stack_slots = push_args(node);
        gen_expr(node->lhs);

        e->Call(r0,stack_slots * target_stack_align); // call fun $0, %d
        Type* ret = getFuncReturn(node->lhs->ty);
        if( ret )
        {
            const Code::Type type = getCodeType(ret);
            r0 = e->Move(Code::Reg(type,Code::RRes)); // mov %s $0, %s $res
        }

        depth -= stack_slots;

        return;
    }
    case ND_LABEL_VAL:
#if 0
        println("  lea %s(%%rip), %%rax", node->unique_label);
#else
        error_tok(node->tok,"label-as-value not yet supported"); // TODO
#endif
        return;
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
        return;
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
        return;
    }
    }

    gen_expr(node->rhs);
    Code::Type rhsT = getCodeType(node->rhs->ty);
    pushRes(rhsT);
    gen_expr(node->lhs);
    Smop tmp = pop(rhsT);

    const Code::Type lhsT = getCodeType(node->lhs->ty);

    if( lhsT != rhsT )
    {
        cast(node->rhs->ty, node->lhs->ty, tmp);
        rhsT = lhsT;
    }

    switch (node->kind) {
    case ND_ADD:
        r0 = e->Add(e->Convert(lhsT,r0),tmp);
        // add %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    case ND_SUB:
        r0 = e->Subtract(e->Convert(lhsT,r0),tmp);
        // sub %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    case ND_MUL:
        r0 = e->Multiply(e->Convert(lhsT,r0),tmp);
        // mul %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    case ND_DIV:
        r0 = e->Divide(e->Convert(lhsT,r0),tmp);
        // div %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    case ND_MOD:
        r0 = e->Modulo(e->Convert(lhsT,r0),tmp);
        // mod %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    case ND_BITAND:
        r0 = e->And(e->Convert(lhsT,r0),tmp);
        // and %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    case ND_BITOR:
        r0 = e->Or(e->Convert(lhsT,r0),tmp);
        // or %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    case ND_BITXOR:
        r0 = e->ExclusiveOr(e->Convert(lhsT,r0),tmp);
        // xor %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    case ND_EQ:
    case ND_NE:
    case ND_LT:
    case ND_LE:
    {
        Code::Emitter2::Label ltrue = e->CreateLabel();
        Code::Emitter2::Label lend = e->CreateLabel();
        if (node->kind == ND_EQ) {
            e->BranchEqual(ltrue,e->Convert(lhsT,r0),tmp);
            // breq +2, %s $0, %s %s", lhsT, rhsT, tmpname
        } else if (node->kind == ND_NE) {
            e->BranchNotEqual(ltrue,e->Convert(lhsT,r0),tmp);
            // brne +2, %s $0, %s %s", lhsT, rhsT, tmpname
        } else if (node->kind == ND_LT) {
            e->BranchLessThan(ltrue,e->Convert(lhsT,r0),tmp);
            // brlt +2, %s $0, %s %s", lhsT, rhsT, tmpname
        } else if (node->kind == ND_LE) {
            e->BranchGreaterEqual(ltrue,tmp,e->Convert(lhsT,r0));
            // brge +2, %s %s, %s $0", rhsT, tmpname, lhsT
        }

        setInt(0,r0);
        e->Branch(lend); //  br +1
        ltrue();
        setInt(1,r0);
        lend();
    } break;
    case ND_SHL:
        r0 = e->ShiftLeft(e->Convert(lhsT,r0),tmp);
        // lsh %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    case ND_SHR:
        r0 = e->ShiftRight(e->Convert(lhsT,r0),tmp);
        // rsh %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname
        break;
    default:
        error_tok(node->tok, "invalid expression");
        break;
    }
}

static void gen_stmt(Node *node) {


    loc(node->tok);

    switch (node->kind) {
    case ND_IF: {

        gen_expr(node->cond);
        const Code::Type type = getCodeType(node->cond->ty);
        Code::Emitter2::Label lelse = e->CreateLabel();
        Code::Emitter2::Label lend = e->CreateLabel();
        e->BranchEqual(lelse,Code::Imm(type,0),e->Convert(type,r0));
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
        Code::Emitter2::Label lbegin = e->CreateLabel();
        Code::Emitter2::Label lbreak = e->CreateLabel();
        labels[node->brk_label] = &lbreak;
        Code::Emitter2::Label lcont = e->CreateLabel();
        labels[node->cont_label] = &lcont;
        lbegin();
        if (node->cond) {
            gen_expr(node->cond);
            const Code::Type type = getCodeType(node->cond->ty);
            e->BranchEqual(lbreak,Code::Imm(type,0),e->Convert(type,r0));
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

        Code::Emitter2::Label lbegin = e->CreateLabel();
        Code::Emitter2::Label lbreak = e->CreateLabel();
        labels[node->brk_label] = &lbreak;
        Code::Emitter2::Label lcont = e->CreateLabel();
        labels[node->cont_label] = &lcont;
        lbegin();
        gen_stmt(node->then);
        lcont();
        gen_expr(node->cond);
        const Code::Type type = getCodeType(node->cond->ty);
        e->BranchNotEqual(lbegin,Code::Imm(type,0),e->Convert(type,r0));
        // brne .L.begin.%d, %s 0, %s $0", c, type, type
        lbreak();
        labels.erase(node->brk_label);
        labels.erase(node->cont_label);
        return;
    }
    case ND_SWITCH: {

        gen_expr(node->cond);

        const Code::Type cond_type = getCodeType(node->cond->ty);

        std::deque<const char*> kk;
        std::deque<Code::Emitter2::Label> ll;
        for (Node *n = node->case_next; n; n = n->case_next) {
            kk.push_back(n->label); ll.push_back(e->CreateLabel());
            labels[n->label] = &ll.back();
            if (n->begin == n->end) {
                e->BranchEqual(ll.back(),Code::Imm(cond_type,n->begin),e->Convert(cond_type,r0));
                // breq %s, %s %ld, %s $0", n->label, cond_type, n->begin, cond_type
                continue;
            }

            // [GNU] Case ranges
            Smop tmp = e->Move(e->Convert(cond_type,r0)); // mov %s %s, %s $0
            tmp = e->Subtract(tmp, Code::Imm(cond_type,n->begin));
                   // sub %s %s, %s %s, %s %ld", cond_type, di, cond_type, di, cond_type, n->begin
            // lhs <= rhs -> rhs >= lhs
            e->BranchGreaterEqual(ll.back(),tmp, Code::Imm(cond_type,n->end - n->begin));
                //  brge %s, %s %s, %s %ld", n->label, cond_type, di, cond_type, n->end - n->begin
        }

        if (node->default_case)
        {
            kk.push_back(node->default_case->label); ll.push_back(e->CreateLabel());
            labels[node->default_case->label] = &ll.back();
            e->Branch(ll.back());
            // br %s", node->default_case->label
        }

        Code::Emitter2::Label lbrk = e->CreateLabel();
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
            gen_expr(node->lhs);
            Type *ty = node->lhs->ty;

            switch (ty->kind) {
            case TY_STRUCT:
            case TY_UNION:
                copy_struct_mem();
                break;
            }
            returnType = getCodeType(ty);
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
        e->Begin(Code::Section::Data, var->name, var->align);

        // Common symbol
        if (opt_fcommon && var->is_tentative) {
            e->Reserve(var->ty->size);
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

        // TODO if (fn->is_static)
        e->Begin(Code::Section::Code, fn->name );
        labels.clear();
        clabels.clear();
        Code::Emitter2::Label lret = e->CreateLabel();
        return_label = &lret;

        current_fn = fn;

        const int isMain = strcmp(fn->name,"main") == 0;

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
            {
                Smop res = Code::Reg(returnType,Code::RRes);
                setInt(0,res);
            }else
                e->Move(Code::Reg(returnType,Code::RRes), e->Convert(returnType,r0));
        }
        e->Leave();
        if( isMain )
        {
            pushRes(types[s4]);
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
    fdoutbuf (FILE* _fd) : fd(_fd) {
    }
  protected:
    // write one character
    virtual int_type overflow (int_type c) {
        return fputc(c,fd);
    }
    // write multiple characters
    virtual
    std::streamsize xsputn (const char* s,
                            std::streamsize num) {
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

static std::bitset<3> inputs(Code::Instruction::Mnemonic m)
{
    switch(m)
    {
    case Code::Instruction::PUSH:
        return 0b100;
    case Code::Instruction::CALL:
        return 0b100;
    case Code::Instruction::ADD:
    case Code::Instruction::AND:
    case Code::Instruction::DIV:
    case Code::Instruction::MOD:
    case Code::Instruction::MUL:
    case Code::Instruction::SUB:
    case Code::Instruction::OR:
    case Code::Instruction::XOR:
        return 0b011;
#if 0
    case Code::Instruction::BREQ:
    case Code::Instruction::BRGE:
    case Code::Instruction::BRLT:
    case Code::Instruction::BRNE:
        return 0b011;
    case Code::Instruction::CONV:
        return 0b010;
    case Code::Instruction::COPY:
        return 0b111;
    case Code::Instruction::FILL:
        return 0b111;
    case Code::Instruction::LSH:
        return 0b011;
    case Code::Instruction::MOV:
        return 0b010;
    case Code::Instruction::NEG:
        return 0b010;
    case Code::Instruction::NOT:
        return 0b010;
    case Code::Instruction::RSH:
        return 0b011;
#endif
    default:
        return 0;
    }
}

class MyEmitter : public Code::Emitter2
{
public:
    MyEmitter(Diagnostics& d, StringPool& sp, Charset& c, Code::Platform& p, Code::Sections &s):
        Emitter2(d,sp,c,p,s) {}
protected:
    virtual void Emit (const Code::Instruction& instruction)
    {
        Code::Instruction last;
        if( !current->section->instructions.empty() )
            last = current->section->instructions.back();

        Code::Instruction cur = instruction;

#if 1
        // check whether last and present can be combined
        if( last.mnemonic == Code::Instruction::MOV )
        {
            bool found = false;
            std::bitset<3> ins = inputs(cur.mnemonic);
            if( ins.any() )
            {
                if( ins.test(2) && cur.operand1 == last.operand1 )
                {
                    std::cout << "mov-" << cur.mnemonic << "-op1 " << std::endl;
                    cur.operand1 = last.operand2;
                    found = true;
                }else if( ins.test(1) && cur.operand2 == last.operand1 )
                {
                    std::cout << "mov-" << cur.mnemonic << "-op2 " << std::endl;
                    cur.operand2 = last.operand2;
                    found = true;
                }else if( ins.test(0) && cur.operand3 == last.operand1 )
                {
                    std::cout << "mov-" << cur.mnemonic << "-op3 " << std::endl;
                    cur.operand3 = last.operand2;
                    found = true;
                }
                // TODO: if more than one op would match, also the others have to be replaced
            }
            if(found)
            {
                current->section->instructions.back() = cur;
                return;
            }
        }
#endif
        // else
        // no matching rule found
        EmitImp(cur);
    }
};

extern "C" {
void codegen(Obj *prog, FILE *out) {
    output_file = out;

    Layout layout( // TODO: why do we need this at all?
        { basic_type(TY_INT)->size, 1, 8},
        {4, 4, 8},
        target_pointer_width,
        target_pointer_width,
        {0, target_stack_align, target_stack_align},
        true
    );
    Code::Platform platform(layout,target_has_linkregister);
    Code::Sections sections;
    MyEmitter emitter(diagnostics,stringPool,charset,platform,sections);
    e = &emitter;

    init_types();

    assign_lvar_offsets(prog);
    emit_data(prog);
    emit_text(prog);
    e = 0;

#if 0
    // TODO temprorarily deactivated
    println("; this is Eigen intermediate code, generated by ECC");
    println("; see https://github.com/rochus-keller/EiGen/tree/master/ecc for more information");
    println("; assuming pointer size %d, int size %d, long size %d, stack alignment %d bytes, %s link reg",
            target_pointer_width, basic_type(TY_INT)->size, basic_type(TY_LONG)->size, target_stack_align,
            target_has_linkregister ? "with" : "no" );
#endif

    fdostream out_stream(out);
    Code::Generator cdgen(layout,platform);

    cdgen.Generate(sections,targets[target].name,out_stream);
}
}
