#include "chibicc.h"

#define ECC_BASIC_TYPE_COUNT TY_LDOUBLE+6
static Type* basic_types[ECC_BASIC_TYPE_COUNT] = {0};

void cleanup_base_types()
{
    for( int i = 0; i < ECC_BASIC_TYPE_COUNT; i++ )
    {
        if(basic_types[i])
            free(basic_types[i]);
    }
}

static Type* new_basic_type(TypeKind k)
{
    assert( k >= TY_VOID && k <= TY_LDOUBLE);

    Type* t = (Type*)calloc(1,sizeof(Type));
    t->kind = k;
    switch(k)
    {
    case TY_VOID:
    case TY_BOOL:
    case TY_CHAR:
        t->size = t->align = 1;
        break;
    case TY_SHORT:
        t->size = t->align = 2;
        break;
    case TY_INT:
        // CHIBICC_INT_WIDTH
        t->size = t->align = sizeof(int); // default to compiled host
        break;
    case TY_LONG:
        // CHIBICC_LONG_WIDTH
        t->size = t->align = sizeof(long);
        break;
    case TY_LONGLONG:
#ifdef CHIBICC_HAVE_LLONG
        t->size = 8;
        // on 32 bit system is 4 byte aligned, two 32 bit regs in use:
        t->align = new_basic_type(TY_LONG)->align;
#else
        // TODO: this is a temporary work-around because of a bug in ECS 32 bit code gen:
        t->size = t->align = sizeof(long);
        t->kind = TY_LONG;
#endif
        break;
    case TY_FLOAT:
        t->size = t->align = 4;
        break;
    case TY_DOUBLE:
        t->size = t->align = 8;
        break;
    case TY_LDOUBLE:
        t->size = t->align = 8;
        break;
    }
    return t;
}

Type *basic_type(TypeKind k)
{
    assert( k >= TY_VOID && k <= TY_LDOUBLE);

    Type* res = basic_types[k];
    if( res != 0 )
        return res;

    res = new_basic_type(k);
    basic_types[k] = res;

    return res;
}

Type *basic_utype(TypeKind k)
{
    assert( k >= TY_CHAR && k <= TY_LONGLONG);

    const int idx = k - TY_CHAR + TY_LDOUBLE + 1;
    Type* res = basic_types[idx];
    if( res != 0 )
        return res;

    res = new_basic_type(k);
    res->is_unsigned = 1;
    basic_types[idx] = res;

    return res;
}


static Type *new_type(TypeKind kind, int size, int align) {
  Type *ty = calloc(1, sizeof(Type));
  ty->kind = kind;
  ty->size = size;
  ty->align = align;
  return ty;
}

bool is_integer(Type *ty) {
  TypeKind k = ty->kind;
  return k == TY_BOOL || k == TY_CHAR || k == TY_SHORT ||
         k == TY_INT  || k == TY_LONG || k == TY_LONGLONG || k == TY_ENUM;
}

bool is_flonum(Type *ty) {
  return ty->kind == TY_FLOAT || ty->kind == TY_DOUBLE ||
         ty->kind == TY_LDOUBLE;
}

bool is_numeric(Type *ty) {
  return is_integer(ty) || is_flonum(ty);
}

bool is_compatible(Type *t1, Type *t2) {
  if (t1 == t2)
    return true;

  if (t1->origin)
    return is_compatible(t1->origin, t2);

  if (t2->origin)
    return is_compatible(t1, t2->origin);

  if (t1->kind != t2->kind)
    return false;

  switch (t1->kind) {
  case TY_CHAR:
  case TY_SHORT:
  case TY_INT:
  case TY_LONG:
  case TY_LONGLONG:
    return t1->is_unsigned == t2->is_unsigned;
  case TY_FLOAT:
  case TY_DOUBLE:
  case TY_LDOUBLE:
    return true;
  case TY_PTR:
    return is_compatible(t1->base, t2->base);
  case TY_FUNC: {
    if (!is_compatible(t1->return_ty, t2->return_ty))
      return false;
    if (t1->is_variadic != t2->is_variadic)
      return false;

    Type *p1 = t1->params;
    Type *p2 = t2->params;
    for (; p1 && p2; p1 = p1->next, p2 = p2->next)
      if (!is_compatible(p1, p2))
        return false;
    return p1 == NULL && p2 == NULL;
  }
  case TY_ARRAY:
    if (!is_compatible(t1->base, t2->base))
      return false;
    return t1->array_len < 0 && t2->array_len < 0 &&
           t1->array_len == t2->array_len;
  }
  return false;
}

Type *copy_type(Type *ty) {
  Type *ret = calloc(1, sizeof(Type));
  *ret = *ty;
  ret->origin = ty;
  return ret;
}

Type *pointer_to(Type *base) {
  Type *ty = new_type(TY_PTR, target_pointer_width, target_pointer_width);
  ty->base = base;
  ty->is_unsigned = true;
  return ty;
}

Type *func_type(Type *return_ty) {
  // The C spec disallows sizeof(<function type>), but
  // GCC allows that and the expression is evaluated to 1.
  Type *ty = new_type(TY_FUNC, 1, 1);
  ty->return_ty = return_ty;
  return ty;
}

Type *array_of(Type *base, int len) {
  Type *ty = new_type(TY_ARRAY, base->size * len, base->align);
  ty->base = base;
  ty->array_len = len;
  return ty;
}

Type *vla_of(Type *base, Node *len) {
  Type *ty = new_type(TY_VLA, target_pointer_width, target_pointer_width);
  ty->base = base;
  ty->vla_len = len;
  return ty;
}

Type *enum_type(void) {
  return new_type(TY_ENUM, 4, 4);
}

Type *struct_type(void) {
  return new_type(TY_STRUCT, 0, 1);
}

static Type *get_common_type(Type *ty1, Type *ty2) {
  if (ty1->base)
    return pointer_to(ty1->base);

  if (ty1->kind == TY_FUNC)
    return pointer_to(ty1);
  if (ty2->kind == TY_FUNC)
    return pointer_to(ty2);

  if (ty1->kind == TY_LDOUBLE || ty2->kind == TY_LDOUBLE)
    return basic_type(TY_LDOUBLE);
  if (ty1->kind == TY_DOUBLE || ty2->kind == TY_DOUBLE)
    return basic_type(TY_DOUBLE);
  if (ty1->kind == TY_FLOAT || ty2->kind == TY_FLOAT)
    return basic_type(TY_FLOAT);

  if (ty1->size < 4)
    ty1 = basic_type(TY_INT);
  if (ty2->size < 4)
    ty2 = basic_type(TY_INT);

  if (ty1->size != ty2->size)
    return (ty1->size < ty2->size) ? ty2 : ty1;

  if (ty2->is_unsigned)
    return ty2;
  return ty1;
}

// For many binary operators, we implicitly promote operands so that
// both operands have the same type. Any integral type smaller than
// int is always promoted to int. If the type of one operand is larger
// than the other's (e.g. "long" vs. "int"), the smaller operand will
// be promoted to match with the other.
//
// This operation is called the "usual arithmetic conversion".
static void usual_arith_conv(Node **lhs, Node **rhs) {
  Type *ty = get_common_type((*lhs)->ty, (*rhs)->ty);
  *lhs = new_cast(*lhs, ty);
  *rhs = new_cast(*rhs, ty);
}

void add_type(Node *node) {
  if (!node || node->ty)
    return;

  add_type(node->lhs);
  add_type(node->rhs);
  add_type(node->cond);
  add_type(node->then);
  add_type(node->els);
  add_type(node->init);
  add_type(node->inc);

  for (Node *n = node->body; n; n = n->next)
    add_type(n);
  for (Node *n = node->args; n; n = n->next)
    add_type(n);

  switch (node->kind) {
  case ND_NUM:
    node->ty = basic_type(TY_INT);
    return;
  case ND_ADD:
  case ND_SUB:
  case ND_MUL:
  case ND_DIV:
  case ND_MOD:
  case ND_BITAND:
  case ND_BITOR:
  case ND_BITXOR:
    usual_arith_conv(&node->lhs, &node->rhs);
    node->ty = node->lhs->ty;
    return;
  case ND_NEG: {
    Type *ty = get_common_type(basic_type(TY_INT), node->lhs->ty);
    node->lhs = new_cast(node->lhs, ty);
    node->ty = ty;
    return;
  }
  case ND_ASSIGN:
    if (node->lhs->ty->kind == TY_ARRAY)
      error_tok(node->lhs->tok, "not an lvalue");
    if (node->lhs->ty->kind != TY_STRUCT)
      node->rhs = new_cast(node->rhs, node->lhs->ty);
    node->ty = node->lhs->ty;
    return;
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
    usual_arith_conv(&node->lhs, &node->rhs);
    node->ty = basic_type(TY_INT);
    return;
  case ND_FUNCALL:
    node->ty = node->func_ty->return_ty;
    return;
  case ND_NOT:
  case ND_LOGOR:
  case ND_LOGAND:
    node->ty = basic_type(TY_INT);
    return;
  case ND_BITNOT:
  case ND_SHL:
  case ND_SHR:
    node->ty = node->lhs->ty;
    return;
  case ND_VAR:
  case ND_VLA_PTR:
    node->ty = node->var->ty;
    return;
  case ND_COND:
    if (node->then->ty->kind == TY_VOID || node->els->ty->kind == TY_VOID) {
      node->ty = basic_type(TY_VOID);
    } else {
      usual_arith_conv(&node->then, &node->els);
      node->ty = node->then->ty;
    }
    return;
  case ND_COMMA:
    node->ty = node->rhs->ty;
    return;
  case ND_MEMBER:
    node->ty = node->member->ty;
    return;
  case ND_ADDR: {
    Type *ty = node->lhs->ty;
    if (ty->kind == TY_ARRAY)
      node->ty = pointer_to(ty->base);
    else
      node->ty = pointer_to(ty);
    return;
  }
  case ND_DEREF:
    if (!node->lhs->ty->base)
      error_tok(node->tok, "invalid pointer dereference");
    if (node->lhs->ty->base->kind == TY_VOID)
      error_tok(node->tok, "dereferencing a void pointer");

    node->ty = node->lhs->ty->base;
    return;
  case ND_STMT_EXPR:
    if (node->body) {
      Node *stmt = node->body;
      while (stmt->next)
        stmt = stmt->next;
      if (stmt->kind == ND_EXPR_STMT) {
        node->ty = stmt->lhs->ty;
        return;
      }
    }
    error_tok(node->tok, "statement expression returning void is not supported");
    return;
  case ND_LABEL_VAL:
    node->ty = pointer_to(basic_type(TY_VOID));
    return;
  case ND_CAS:
    add_type(node->cas_addr);
    add_type(node->cas_old);
    add_type(node->cas_new);
    node->ty = basic_type(TY_BOOL);

    if (node->cas_addr->ty->kind != TY_PTR)
      error_tok(node->cas_addr->tok, "pointer expected");
    if (node->cas_old->ty->kind != TY_PTR)
      error_tok(node->cas_old->tok, "pointer expected");
    return;
  case ND_EXCH:
    if (node->lhs->ty->kind != TY_PTR)
      error_tok(node->cas_addr->tok, "pointer expected");
    node->ty = node->lhs->ty->base;
    return;
  }
}
