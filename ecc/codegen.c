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

#include "chibicc.h"

enum EcsRegs { R0, R1, R2, R3, R4, R5, R6, R7,
               Res, Sp, Fp, Lnk };
static struct EcsReg {
    uint8_t reg;
    uint8_t used;
    const char* name;
} ecsRegs[] = {
    { R0, 0, "$0" }, // is used here as expression result
    { R1, 0, "$1" },
    { R2, 0, "$2" },
    { R3, 0, "$3" },
    { R4, 0, "$4" },
    { R5, 0, "$5" },
    { R6, 0, "$6" },
    { R7, 0, "$7" },
    { Res,0, "$res" },
    { Sp, 0, "$sp" },
    { Fp, 0, "$fp" },
    { Lnk,0, "$lnk" }
};

static uint8_t buy()
{
    for( uint8_t i = 1; i <= R7; i++ )
    {
        if( ecsRegs[i].used == 0 )
        {
            ecsRegs[i].used = 1;
            return i;
        }
    }
    fprintf(stderr,"no more free registers");
    exit(-1);
}

static void sell(uint8_t reg)
{
    assert( reg > R0 && reg <= R7 && ecsRegs[reg].used );
    ecsRegs[reg].used = 0;
}

static FILE *output_file;
static int depth;
static Obj *current_fn;
static const char* returnType = 0;
static int pc, infunc = 0;

__attribute__((format(printf, 1, 2)))
static void println(char *fmt, ...) {
    // ok
    va_list ap;
    va_start(ap, fmt);
    vfprintf(output_file, fmt, ap);
    va_end(ap);
    if( infunc && fmt[0] == ' ' && fmt[1] == ' ' && fmt[2] != ';' )
    {
        pc++;
        if( pc % 10 == 0 )
            ; // TODO fprintf(output_file,"\t; pc %d", pc ); temporarily deactivated
    }
    fprintf(output_file, "\n");
}

enum EcsTypes { u1, u2, u4, u8, s1, s2, s4, s8, f4, f8, ptr, fun };

struct EcsType {
    uint8_t type;
    uint8_t width;
    const char* name;
} ecsTypes[] = {
    { u1, 8, "u1" },
    { u2, 16, "u2" },
    { u4, 32, "u4" },
    { u8, 64, "u8" },
    { s1, 8, "s1" },
    { s2, 16, "s2" },
    { s4, 32, "s4" },
    { s8, 64, "s8" },
    { f4, 32, "f4" },
    { f8, 64, "f8" },
    { ptr, 0, "ptr" },
    { fun, 0, "fun" },
};

static uint8_t getTypeId(Type *ty) {
    // ok
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

static const char* getTypeName(Type *ty) {
    // ok
    return ecsTypes[ getTypeId(ty) ].name;
}

static uint8_t getTypeWidth(Type *ty) {
    // ok
    return ecsTypes[ getTypeId(ty) ].width;
}

#define name_buffer_len 128
static char name_buffer[name_buffer_len];

static char* make_name(int is_static, const char* in)
{
    if( is_static && in[0] != '.' )
    {
        const char* fileName = file_name(base_file);
        const int fnameLen = strlen(fileName);
        const int nameLen = strlen(in);
        const int hashLen = 9;
        assert( fnameLen + hashLen + nameLen + 4 <= name_buffer_len );

        name_buffer[0] = '.';
        name_hash(base_file,name_buffer+1,hashLen);
        name_buffer[hashLen-1] = '#';

        strcpy(name_buffer+1+hashLen,fileName);
        for(int i = hashLen; i < hashLen + fnameLen; i++ )
        {
            const char ch = name_buffer[i];
            if( !isalnum(ch) && ch != '_' && ch != '.' )
                name_buffer[i] = '_';
        }
        name_buffer[hashLen + fnameLen + 1] = '#';
        strcpy(name_buffer + hashLen + fnameLen + 2, in);

        return name_buffer;
    }else
        return in;
}

static void gen_expr(Node *node);
static void gen_stmt(Node *node);


static int count(void) {
    // ok
    static int i = 1;
    return i++;
}

static void pushRes(const char* type) {
    // ok
    println("  push %s $0", type); // was %rax
    depth++;
}

static void pop(const char* type, const char *arg) {
    // ok
    println("  pop %s %s", type, arg);
    depth--;
}

// Round up `n` to the nearest multiple of `align`. For instance,
// align_to(5, 8) returns 8 and align_to(11, 8) returns 16.
int align_to(int n, int align) {
    // ok
    return (n + align - 1) / align * align;
}

// Compute the absolute address of a given node.
// It's an error if a given node does not reside in memory.
static void gen_addr(Node *node) {
    // ok
    switch (node->kind) {
    case ND_VAR:
        // Variable-length array, which is always local.
        if (node->var->ty->kind == TY_VLA) {
            error_tok(node->tok,"VLA not yet supported");
            println("  mov ptr $0, ptr $fp%+d", node->var->offset);
            return;
        }

        // Local variable
        if (node->var->is_local) {
            println("  mov ptr $0, ptr $fp%+d", node->var->offset);
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
        if (node->ty && node->ty->kind == TY_FUNC) {
            println("  mov fun $0, fun @%s", make_name(node->var->is_static, node->var->name));
            return;
        }

        // Global variable
        println("  mov ptr $0, ptr @%s", make_name(node->var->is_static, node->var->name));
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
        println("  add ptr $0, ptr $0, ptr %d", node->member->offset);
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
        error_tok(node->tok,"VLA not yet supported");
        println("  mov ptr $0, ptr $fp%+d", node->var->offset);
        return;
    }

    error_tok(node->tok, "not an lvalue");
}

// Load a value from where $0 is pointing to.
static void load(Type *ty) {
    // ok
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

    const char* type = getTypeName(ty);
    println("  mov %s $0, %s [$0]", type, type );
}

// Store $0 to the address on top of the stack
static void store(Type *ty) {
    // ok
    const uint8_t tmpReg = buy();
    const char* tmp = ecsRegs[tmpReg].name;
    pop("ptr", tmp);

    switch (ty->kind) {
    case TY_STRUCT:
    case TY_UNION:
        println("  copy ptr %s, ptr $0, ptr %d", tmp, ty->size);
        sell(tmpReg);
        return;
    }

    const char* type = getTypeName(ty);
    println("  mov %s [%s], %s $0", type, tmp, type );
    sell(tmpReg);
}

static void cast(Type *from, Type *to, const char* reg) {
    // ok

    if (to->kind == TY_VOID)
        return;

    const uint8_t fromType = getTypeId(from);
    const uint8_t toType = getTypeId(to);

    if (to->kind == TY_BOOL) {
        const char* type = ecsTypes[fromType].name;
        println("  breq +2, %s 0, %s %s", type, type, reg );
        type = ecsTypes[toType].name;
        println("  mov %s %s, %s 0", type, reg, type);
        // TODO: do we need setBool here?
        println("  br +1");
        println("  mov %s %s, %s 1", type, reg, type);
        return;
    }

    if( fromType != toType )
        println("  conv %s %s, %s %s", ecsTypes[toType].name, reg, ecsTypes[fromType].name, reg);
}

static int push_struct(Type *ty) {
    // ok
    int sz = align_to(ty->size, target_stack_align);
    println("  sub	ptr $sp, ptr $sp, ptr %d", sz);
    const int res = sz / target_stack_align;
    depth += res;
    println("  copy	ptr $sp, ptr $0, ptr %d", sz);
    return res;
}

static int push_args2(Node *args) {
    // ok
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
        pushRes(getTypeName(args->ty));
        res += align_to(args->ty->size, target_stack_align) / target_stack_align;
        break;
    }
    return res;
}

static int push_args(Node *node) {
    // ok
    int stack = 0;

    for (Node *arg = node->args; arg; arg = arg->next) {
        arg->pass_by_stack = true;
    }

    stack += push_args2(node->args);

    // If the return type is a large struct/union, the caller passes
    // a pointer to a buffer as if it were the first argument.
    if (node->ret_buffer) {
        println("  mov ptr $0, ptr $fp%+d", node->ret_buffer->offset);
        pushRes("ptr");
        stack += align_to(target_pointer_width, target_stack_align) / target_stack_align;
    }

    return stack;
}

static int firstParamOffset();

// copy struct pointed to by $0 to the local var at offset
static void copy_struct_mem(void) {
    // ok
    Type *ty = current_fn->ty->return_ty;

    const uint8_t tmp = buy();
    const char* to = ecsRegs[tmp].name;

    println("  mov ptr %s, ptr $fp%+d", to, firstParamOffset());
                                        // the pointer to result is the first (invisible) param
    println("  copy ptr [%s], ptr $0, ptr %d", to, ty->size);

    sell(tmp);
}

static void builtin_alloca(void) {
    // TODO
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
}

static const char* file_path(int file_no)
{
    // ok
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
static void loc(Token * tok)
{
    static int file_no = 0, line_no = 0;

    if( tok->file->file_no != file_no || tok->line_no != line_no )
    {
#if 0
        println("  loc \"%s\", %d, 1", file_path(tok->file->file_no), tok->line_no);
#else
        // TODO println("  ; line %s:%d", file_name(file_path(tok->file->file_no)), tok->line_no); temporarily deactivated
#endif
        file_no = tok->file->file_no;
        line_no = tok->line_no;
    }
}

static void setInt(uint32_t i, const char* reg)
{
    println("  mov s%d %s, s%d %d", target_pointer_width, reg, target_pointer_width, i);
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
    // ok
    loc(node->tok);

    switch (node->kind) {
    case ND_NULL_EXPR:
        return;
    case ND_NUM: {
        // ok
        const char* type = getTypeName(node->ty);
        switch (node->ty->kind)
        {
        case TY_FLOAT:
        case TY_DOUBLE:
        case TY_LDOUBLE: {
            println("  mov %s $0, %s %Lf", type, type, node->fval );
            return;
        }
        }

        println("  mov %s $0, %s %Ld", type, type, node->val);
        return;
    }
    case ND_NEG: {
        // ok
        gen_expr(node->lhs);
        const char* type = getTypeName(node->ty);
        println("  neg %s $0, %s $0", type, type );
        return;
    }
    case ND_PLUS:
        gen_expr(node->lhs);
        return;
    case ND_VAR:
        // ok
        gen_addr(node);
        load(node->ty);
        return;
    case ND_MEMBER: {
        // ok
        gen_addr(node);
        load(node->ty);

        Member *mem = node->member;
        if (mem->is_bitfield) {
            const uint8_t w = getTypeWidth(mem->ty);
            const char* nm = getTypeName(mem->ty);
            // align the bitfield to the msb of the underlying type
            println("  lsh %s $0, %s $0, %s %d", nm, nm, nm, w - mem->bit_width - mem->bit_offset);
            println("  rsh %s $0, %s $0, %s %d",  nm, nm, nm, w - mem->bit_width );
        }
        return;
    }
    case ND_DEREF:
        // ok
        gen_expr(node->lhs);
        load(node->ty);
        return;
    case ND_ADDR:
        // ok
        gen_addr(node->lhs);
        return;
    case ND_ASSIGN:
        // ok
        gen_addr(node->lhs);
        pushRes("ptr");
        gen_expr(node->rhs);

        if (node->lhs->kind == ND_MEMBER && node->lhs->member->is_bitfield) {
            const uint8_t r8 = buy();

            const char* rhsty = getTypeName(node->rhs->ty);

            println("  mov %s %s, %s $0", rhsty, ecsRegs[r8].name, rhsty ); // save to r8

            // If the lhs is a bitfield, we need to read the current value
            // from memory and merge it with a new value.
            Member *mem = node->lhs->member;
            const char* memty = getTypeName(mem->ty);

            const uint8_t rdi = buy();
            println("  mov %s %s, %s $0", rhsty, ecsRegs[rdi].name, rhsty );
            println("  and  %s %s, %s %s,  %s %ld", rhsty, ecsRegs[rdi].name, rhsty, ecsRegs[rdi].name,
                    rhsty, (1L << mem->bit_width) - 1);
            cast(node->rhs->ty,mem->ty, ecsRegs[rdi].name);
            println("  lsh %s %s, %s %s, %s %d", memty, ecsRegs[rdi].name, memty, ecsRegs[rdi].name,
                    memty, mem->bit_offset);

            println("  mov ptr $0, ptr [$sp]"); // $0 is now adr(lhs)
            load(mem->ty); // $0 is now val(lhs)

            const unsigned long mask = ((1L << mem->bit_width) - 1) << mem->bit_offset;
            const uint8_t r9 = buy();
            if( mem->ty->is_unsigned ) {
                const unsigned long mask2 = ((1L << (mem->ty->size-1)*8) - 1) | (255 << (mem->ty->size-1)*8);
                println("  mov %s %s, %s %lu", memty, ecsRegs[r9].name, memty, (~mask & mask2));
            } else
                println("  mov %s %s, %s %ld", memty, ecsRegs[r9].name, memty, ~mask);
            println("  and %s $0, %s $0, %s %s", memty, memty, memty, ecsRegs[r9].name);
            println("  or %s $0, %s $0, %s %s", memty, memty, memty, ecsRegs[rdi].name);
            store(node->ty);

            println("  mov %s $0, %s %s", rhsty, rhsty, ecsRegs[r8].name); // restore from r8

            sell(r9);
            sell(rdi);
            sell(r8);
            return;
        }else {
            store(node->ty);
            return;
        }
    case ND_STMT_EXPR:
        // ok
        for (Node *n = node->body; n; n = n->next)
            gen_stmt(n);
        return;
    case ND_COMMA:
        // ok
        gen_expr(node->lhs);
        gen_expr(node->rhs);
        return;
    case ND_CAST:
        // ok
        gen_expr(node->lhs);
        cast(node->lhs->ty, node->ty, "$0");
        return;
    case ND_MEMZERO:
        // ok
        println("  mov ptr $0, ptr $fp%+d", node->var->offset);
        println("  fill ptr $0, ptr %d, u1 0", node->var->ty->size );
        return;
    case ND_COND: {
        // ok
        int c = count();
        gen_expr(node->cond);
        const char* type = getTypeName(node->cond->ty);
        println("  breq .L.else.%d, %s 0, %s $0", c, type, type );
        gen_expr(node->then);
        println("  br .L.end.%d", c);
        println(".L.else.%d:", c);
        gen_expr(node->els);
        println(".L.end.%d:", c);
        return;
    }
    case ND_NOT: {
        // ok
        gen_expr(node->lhs);
        const char* type = getTypeName(node->lhs->ty);
        println("  breq +2, %s 0, %s $0", type, type );
        setInt(0,"$0");
        println("  br +1");
        setInt(1,"$0");
        return;
    }
    case ND_BITNOT: {
        // ok
        gen_expr(node->lhs);
        const char* type = getTypeName(node->lhs->ty);
        println("  not %s $0, %s $0", type, type);
        return;
    }
    case ND_LOGAND: {
        // ok
        int c = count();
        gen_expr(node->lhs);
        const char* type = getTypeName(node->lhs->ty);
        println("  breq .L.false.%d, %s 0, %s $0", c, type, type );
        gen_expr(node->rhs);
        type = getTypeName(node->rhs->ty);
        println("  breq .L.false.%d, %s 0, %s $0", c, type, type );
        setInt(1,"$0");
        println("  br .L.end.%d", c);
        println(".L.false.%d:", c);
        setInt(0,"$0");
        println(".L.end.%d:", c);
        return;
    }
    case ND_LOGOR: {
        // ok
        int c = count();
        gen_expr(node->lhs);
        const char* type = getTypeName(node->lhs->ty);
        println("  brne .L.true.%d, %s 0, %s $0", c, type, type);
        gen_expr(node->rhs);
        type = getTypeName(node->rhs->ty);
        println("  brne .L.true.%d, %s 0, %s $0", c, type, type);
        setInt(0,"$0");
        println("  br .L.end.%d", c);
        println(".L.true.%d:", c);
        setInt(1,"$0");
        println(".L.end.%d:", c);
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
        // ok

        const int stack_slots = push_args(node);
        gen_expr(node->lhs);

        println("  call fun $0, %d", stack_slots * target_stack_align);
        Type* ret = getFuncReturn(node->lhs->ty);
        if( node->ret_buffer )
        {
            println("  mov ptr $0, ptr $fp%+d", node->ret_buffer->offset);

        }else if( ret )
        {
            const char* type = getTypeName(ret);
            println("  mov %s $0, %s $res", type, type);
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

    // ok ff
    gen_expr(node->rhs);
    const char* rhsT = getTypeName(node->rhs->ty);
    pushRes(rhsT);
    gen_expr(node->lhs);
    const uint8_t tmp = buy();
    pop(rhsT,ecsRegs[tmp].name);

    const char* lhsT = getTypeName(node->lhs->ty);
    const char* tmpname = ecsRegs[tmp].name;

    if( getTypeId(node->lhs->ty) != getTypeId(node->rhs->ty) )
    {
        cast(node->rhs->ty, node->lhs->ty, ecsRegs[tmp].name);
        rhsT = lhsT;
    }

    switch (node->kind) {
    case ND_ADD:
        println("  add %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    case ND_SUB:
        println("  sub %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    case ND_MUL:
        println("  mul %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    case ND_DIV:
        println("  div %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    case ND_MOD:
        println("  mod %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    case ND_BITAND:
        println("  and %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    case ND_BITOR:
        println("  or %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    case ND_BITXOR:
        println("  xor %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    case ND_EQ:
    case ND_NE:
    case ND_LT:
    case ND_LE:
        if (node->kind == ND_EQ) {
            println("  breq +2, %s $0, %s %s", lhsT, rhsT, tmpname );
        } else if (node->kind == ND_NE) {
            println("  brne +2, %s $0, %s %s", lhsT, rhsT, tmpname );
        } else if (node->kind == ND_LT) {
            println("  brlt +2, %s $0, %s %s", lhsT, rhsT, tmpname );
        } else if (node->kind == ND_LE) {
            println("  brge +2, %s %s, %s $0", rhsT, tmpname, lhsT );
        }

        setInt(0,"$0");
        println("  br +1");
        setInt(1,"$0");
        break;
    case ND_SHL:
        println("  lsh %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    case ND_SHR:
        println("  rsh %s $0, %s $0, %s %s", lhsT, lhsT, rhsT, tmpname );
        break;
    default:
        error_tok(node->tok, "invalid expression");
        break;
    }
    sell(tmp);
}

static void gen_stmt(Node *node) {
    // ok

    loc(node->tok);

    switch (node->kind) {
    case ND_IF: {
        // ok
        int c = count();
        gen_expr(node->cond);
        const char* type = getTypeName(node->cond->ty);
        println("  breq .L.else.%d, %s 0, %s $0", c, type, type );
        gen_stmt(node->then);
        println("  br .L.end.%d", c);
        println(".L.else.%d:", c);
        if (node->els)
            gen_stmt(node->els);
        println(".L.end.%d:", c);
        return;
    }
    case ND_FOR: {
        // ok
        int c = count();
        if (node->init)
            gen_stmt(node->init);
        println(".L.begin.%d:", c);
        if (node->cond) {
            gen_expr(node->cond);
            const char* type = getTypeName(node->cond->ty);
            println("  breq %s, %s 0, %s $0", node->brk_label, type, type );
        }
        gen_stmt(node->then);
        println("%s:", node->cont_label);
        if (node->inc)
            gen_expr(node->inc);
        println("  br .L.begin.%d", c);
        println("%s:", node->brk_label);
        return;
    }
    case ND_DO: {
        // ok
        int c = count();
        println(".L.begin.%d:", c);
        gen_stmt(node->then);
        println("%s:", node->cont_label);
        gen_expr(node->cond);
        const char* type = getTypeName(node->cond->ty);
        println("  brne .L.begin.%d, %s 0, %s $0", c, type, type );
        println("%s:", node->brk_label);
        return;
    }
    case ND_SWITCH:
        // ok
        gen_expr(node->cond);

        const char* cond_type = getTypeName(node->cond->ty);

        for (Node *n = node->case_next; n; n = n->case_next) {
            if (n->begin == n->end) {
                println("  breq %s, %s %ld, %s $0", n->label, cond_type, n->begin, cond_type );
                continue;
            }

            // [GNU] Case ranges
            const uint8_t tmp = buy();
            const char* di = ecsRegs[tmp].name;
            println("  mov %s %s, %s $0", cond_type, di, cond_type);
            println("  sub %s %s, %s %s, %s %ld", cond_type, di, cond_type, di, cond_type, n->begin);
            // lhs <= rhs -> rhs >= lhs
            println("  brge %s, %s %s, %s %ld", n->label, cond_type, di, cond_type, n->end - n->begin);
            sell(tmp);
        }

        if (node->default_case)
            println("  br %s", node->default_case->label);

        println("  br %s", node->brk_label);
        gen_stmt(node->then);
        println("%s:", node->brk_label);
        return;
    case ND_CASE:
        // ok
        println("%s:", node->label);
        gen_stmt(node->lhs);
        return;
    case ND_BLOCK:
        // ok
        for (Node *n = node->body; n; n = n->next)
            gen_stmt(n);
        return;
    case ND_GOTO:
        // ok
        println("  br %s", node->unique_label);
        return;
    case ND_GOTO_EXPR:
        gen_expr(node->lhs);
#if 0
        println("  jmp *%%rax");
#else
        error_tok(node->tok,"goto labels-as-values not yet supported"); // TODO
#endif
        return;
    case ND_LABEL:
        // ok
        println("%s:", node->unique_label);
        gen_stmt(node->lhs);
        return;
    case ND_RETURN:
        // ok
        if (node->lhs) {
            gen_expr(node->lhs);
            Type *ty = node->lhs->ty;

            switch (ty->kind) {
            case TY_STRUCT:
            case TY_UNION:
                copy_struct_mem();
                break;
            }
            returnType = getTypeName(ty);
        }

        println("  br .L.return.%s", current_fn->name);
        return;
    case ND_EXPR_STMT:
        gen_expr(node->lhs);
        return;
    case ND_ASM:
        println("  ; begin inline asm, line %d", node->tok->line_no);
        println(node->asm_str);
        println("  ; end inline asm");
        return;
    }

    error_tok(node->tok, "invalid statement");
}

static int firstParamOffset()
{
    return 2 * target_stack_align; // previous frame and return address;
}

// Assign offsets to local variables.
static void assign_lvar_offsets(Obj *prog) {
    // ok
    for (Obj *fn = prog; fn; fn = fn->next) {
        if (!fn->is_function)
            continue;

        int top = firstParamOffset();

        if( fn->ty->return_ty && ( fn->ty->return_ty->kind == TY_STRUCT || fn->ty->return_ty->kind == TY_UNION ) )
            top += target_stack_align; // if fn has struct return, the first param is a pointer to result

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

static int is_static(Obj *prog, const char* name)
{
    for (Obj *obj = prog; obj; obj = obj->next)
        if( obj->name == name )
            // the name is locally declared
            return obj->is_static;
    // name not found locally, so it cannot be static
    return 0;
}

static void emit_data(Obj *prog) {
    // ok
    for (Obj *var = prog; var; var = var->next) {
        if (var->is_function || !var->is_definition)
            continue;

        // if (var->is_static)
        println(".data %s", make_name(var->is_static, var->name));

        const int align = var->align;

        // Common symbol
        if (opt_fcommon && var->is_tentative) {
            println("  .alignment %d", align );
            //println("  res %d", abs(var->ty->size) );
            continue;
        }

        if( align > 1 )
            println("  .alignment %d", align);

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
                    // println("  ; relocation, addend: %s, %+ld", *rel->label, rel->addend);
                    Type* ty = getTypeOf(prog,*rel->label);
                    const char* type = "ptr";
                    if( ty && ty->kind == TY_FUNC )
                        type = "fun";
                    println("  def %s @%s", type, make_name(is_static(prog,*rel->label),*rel->label));
                    rel = rel->next;
                    pos += target_pointer_width;
                } else {
                    const char d = var->init_data[pos++];
                    if( 0 ) // TODO isprint(d) ) temporarily deactivated
                        println("  def s1 %d \t; '%c'", d, d);
                    else
                        println("  def s1 %d", d);
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
}

static void emit_text(Obj *prog) {
    // ok
    for (Obj *fn = prog; fn; fn = fn->next) {
        if (!fn->is_function || !fn->is_definition)
            continue;

        if( fn->ty == basic_type(TY_VOID) )
        {
            // this must be an assembler function
            assert( *fn->name == 0 );
            const char* code = fn->body->asm_str;
            while( *code && isspace(*code) )
                code++;
            //if( *code != '.' )
            //    error_tok(fn->body->tok,"invalid assembler section");
            if( fn->is_inline )
            {
                println("  asm %s, %d, \"%s\"", base_file, fn->body->tok->line_no, fn->body->asm_str);
            }else
            {
                println("  ; begin inline asm, line %d", fn->body->tok->line_no);
                println(fn->body->asm_str);
                println("  ; end inline asm");
            }
            continue;
        }

        // No code is emitted for "static inline" functions
        // if no one is referencing them.
        if (!fn->is_live)
            continue;

        returnType = 0;
        pc = 0;
        infunc = 1;

        // TODO if (fn->is_static)
        println(".code %s", make_name(fn->is_static, fn->name) );

        current_fn = fn;

        const int isMain = !fn->is_static && strcmp(fn->name,"main") == 0;

        print_var_names(fn);

        // Prologue
        if( !isMain && target_has_linkregister )
            println("  push fun $lnk");

        println("  enter %d", fn->stack_size);
        // TODO println("  ; alloca_bottom offset: %d", fn->alloca_bottom->offset);

        // Emit code
        gen_stmt(fn->body);
        if(depth != 0)
            error("stack depth not zero when leaving function %s", fn->name);

        // Epilogue
        println(".L.return.%s:", fn->name);
        if( fn->ty->return_ty && fn->ty->return_ty->kind != TY_VOID )
        {
            if( returnType == 0 )
                setInt(0,"$res");
            else
                println("  mov %s $res, %s $0", returnType, returnType );
        }
        println("  leave");
        if( isMain )
        {
            pushRes("s4");
            println("  call fun @_Exit, 0");
        }else
            println("  ret");
        depth = 0;
        infunc = 0;
    }
}

void codegen(Obj *prog, FILE *out) {
    output_file = out;
    assign_lvar_offsets(prog);
#if 0
    // TODO: temporarily deactivated
    println("; this is Eigen intermediate code, generated by ECC");
    println("; see https://github.com/rochus-keller/EiGen/tree/master/ecc for more information");
    println("; generated for target '%s'", targets[target].name);
    println("; assuming pointer size %d, int size %d, long size %d, stack alignment %d bytes, %s link reg",
            target_pointer_width, basic_type(TY_INT)->size, basic_type(TY_LONG)->size, target_stack_align,
            target_has_linkregister ? "with" : "no" );
#endif
    emit_data(prog);
    emit_text(prog);
}
