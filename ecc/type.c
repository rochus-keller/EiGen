#include "widcc.h"

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
    case TY_PCHAR:
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

Type *new_type(TypeKind kind, int size, int align) {
  Type *ty = calloc(1, sizeof(Type));
  ty->kind = kind;
  ty->size = size;
  ty->align = align;
  return ty;
}

bool is_integer(Type *ty) {
  TypeKind k = ty->kind;
  return k == TY_BOOL || k == TY_PCHAR || k == TY_CHAR || k == TY_SHORT ||
         k == TY_INT  || k == TY_LONG || k == TY_LONGLONG || k == TY_ENUM;
}

bool is_flonum(Type *ty) {
  return ty->kind == TY_FLOAT || ty->kind == TY_DOUBLE ||
         ty->kind == TY_LDOUBLE;
}

bool is_numeric(Type *ty) {
  return is_integer(ty) || is_flonum(ty);
}

bool is_bitfield(Node *node) {
  return node->kind == ND_MEMBER && node->member->is_bitfield;
}

static bool is_bitfield2(Node *node, int *width) {
  switch (node->kind) {
  case ND_ASSIGN:
    return is_bitfield2(node->lhs, width);
  case ND_CHAIN:
  case ND_COMMA:
    return is_bitfield2(node->rhs, width);
  case ND_STMT_EXPR: {
    Node *stmt = node->body;
    while (stmt->next)
      stmt = stmt->next;
    if (stmt->kind == ND_EXPR_STMT)
      return is_bitfield2(stmt->lhs, width);
  }
  case ND_MEMBER:
    if (!node->member->is_bitfield)
      return false;
    *width = node->member->bit_width;
    return true;
  }
  return false;
}

bool is_compatible(Type *t1, Type *t2) {
  if( t1 == 0 || t2 == 0 )
     return false;
  if (t1 == t2)
    return true;

  if (t1->origin)
    return is_compatible(t1->origin, t2);

  if (t2->origin)
    return is_compatible(t1, t2->origin);

  if (t1->kind != t2->kind)
    return false;

  switch (t1->kind) {
  case TY_PCHAR:
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

    Obj *p1 = t1->param_list;
    Obj *p2 = t2->param_list;
    for (; p1 && p2; p1 = p1->param_next, p2 = p2->param_next)
      if (!is_compatible(p1->ty, p2->ty))
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

Type *array_to_pointer(Type *ty) {
  if (ty->base && ty->kind != TY_PTR)
    return pointer_to(ty->base);
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

int int_rank(Type *t) {
  switch (t->kind) {
    case TY_ENUM:
    case TY_BOOL:
    case TY_CHAR:
    case TY_SHORT:
      return 0;
    case TY_INT:
      return 1;
    case TY_LONG:
      return 2;
    case TY_LONGLONG:
      return 3;
  }
  internal_error();
}

static bool is_nullptr(Node *node) {
  if (node->kind == ND_CAST &&
    node->ty->kind == TY_PTR && node->ty->base->kind == TY_VOID)
    node = node->lhs;

  int64_t val;
  if (is_integer(node->ty) && is_const_expr(node, &val) && val == 0)
    return true;
  return false;
}

static void int_promotion(Node **node) {
  Type *ty = (*node)->ty;
  int bit_width;

  if (is_bitfield2(*node, &bit_width)) {
    int int_width = basic_type(TY_INT)->size * 8;

    if (bit_width == int_width && ty->is_unsigned) {
      *node = new_cast(*node, basic_utype(TY_INT));
    } else if (bit_width <= int_width) {
      *node = new_cast(*node, basic_type(TY_INT));
    } else {
      *node = new_cast(*node, ty);
    }
    return;
  }

  if (ty->size < basic_type(TY_INT)->size) {
    *node = new_cast(*node, basic_type(TY_INT));
    return;
  }

  if (ty->size == basic_type(TY_INT)->size && int_rank(ty) < int_rank(basic_type(TY_INT))) {
    if (ty->is_unsigned)
      *node = new_cast(*node, basic_utype(TY_INT));
    else
      *node = new_cast(*node, basic_type(TY_INT));
    return;
  }
}

static Type *get_common_type(Node **lhs, Node **rhs, bool handle_ptr) {
  Type *ty1 = (*lhs)->ty;
  Type *ty2 = (*rhs)->ty;

  if (handle_ptr) {
    if (ty1->kind == TY_FUNC)
      ty1 = pointer_to(ty1);
    if (ty2->kind == TY_FUNC)
      ty2 = pointer_to(ty2);

    if (ty1->base && is_nullptr(*rhs))
      return array_to_pointer(ty1);
    if (ty2->base && is_nullptr(*lhs))
      return array_to_pointer(ty2);

    if (ty1->base && ty2->base) {
      if (is_compatible(ty1->base, ty2->base))
        return array_to_pointer(ty1);
      return pointer_to(basic_type(TY_VOID));
    }
  }

  if (!is_numeric(ty1) || !is_numeric(ty2))
    error_tok((*rhs)->tok,"invalid operand");

  if (ty1->kind == TY_LDOUBLE || ty2->kind == TY_LDOUBLE)
    return basic_type(TY_LDOUBLE);
  if (ty1->kind == TY_DOUBLE || ty2->kind == TY_DOUBLE)
    return basic_type(TY_DOUBLE);
  if (ty1->kind == TY_FLOAT || ty2->kind == TY_FLOAT)
    return basic_type(TY_FLOAT);

  int_promotion(lhs);
  int_promotion(rhs);
  ty1 = (*lhs)->ty;
  ty2 = (*rhs)->ty;

  if (ty1->size != ty2->size)
    return (ty1->size < ty2->size) ? ty2 : ty1;

  Type *ranked_ty = int_rank(ty1) > int_rank(ty2) ? ty1 : ty2;

  if (ty1->is_unsigned == ty2->is_unsigned)
    return ranked_ty;

  // If same size but different sign, the common type is unsigned
  // variant of the highest-ranked type between the two.
  switch (ranked_ty->kind) {
    case TY_INT:
      return basic_utype(TY_INT);
    case TY_LONG:
      return basic_utype(TY_LONG);
    case TY_LONGLONG:
      return basic_utype(TY_LONGLONG);
  }
  internal_error();
}

// For many binary operators, we implicitly promote operands so that
// both operands have the same type. Any integral type smaller than
// int is always promoted to int. If the type of one operand is larger
// than the other's (e.g. "long" vs. "int"), the smaller operand will
// be promoted to match with the other.
//
// This operation is called the "usual arithmetic conversion".
static void usual_arith_conv(Node **lhs, Node **rhs, bool handle_ptr) {
  Type *ty = get_common_type(lhs, rhs, handle_ptr);
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

  switch (node->kind) {
  case ND_NUM:
    node->ty = basic_type(TY_INT);
    return;
  case ND_ADD:
  case ND_SUB:
    if (node->lhs->ty->base) {
      if (node->lhs->ty->kind != TY_PTR)
        node->lhs = new_cast(node->lhs, pointer_to(node->lhs->ty->base));
      node->rhs = new_cast(node->rhs, basic_utype(TY_LONGLONG));
      node->ty = node->lhs->ty;
      return;
    }
    usual_arith_conv(&node->lhs, &node->rhs, false);
    node->ty = node->lhs->ty;
    return;
  case ND_MUL:
  case ND_DIV:
  case ND_MOD:
  case ND_BITAND:
  case ND_BITOR:
  case ND_BITXOR:
    usual_arith_conv(&node->lhs, &node->rhs, false);
    node->ty = node->lhs->ty;
    return;
  case ND_POS:
  case ND_NEG:
    if (!is_numeric(node->lhs->ty))
      error_tok(node->lhs->tok, "invalid operand");
    if (is_integer(node->lhs->ty))
      int_promotion(&node->lhs);
    node->ty = node->lhs->ty;
    return;
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
    usual_arith_conv(&node->lhs, &node->rhs, true);
    node->ty = basic_type(TY_INT);
    return;
  case ND_FUNCALL:
    assert(!!node->ty);
    return;
  case ND_NOT:
  case ND_LOGOR:
  case ND_LOGAND:
    node->ty = basic_type(TY_INT);
    return;
  case ND_BITNOT:
  case ND_SHL:
  case ND_SHR:
  case ND_SAR:
    if (!is_integer(node->lhs->ty))
      error_tok(node->lhs->tok, "invalid operand");
    int_promotion(&node->lhs);
    node->ty = node->lhs->ty;
    return;
  case ND_VAR:
    node->ty = node->var->ty;
    return;
  case ND_COND:
    if (node->then->ty->kind == TY_VOID || node->els->ty->kind == TY_VOID) {
      node->ty = basic_type(TY_VOID);
    } else if (!is_numeric(node->then->ty) && is_compatible(node->then->ty, node->els->ty)) {
      node->ty = array_to_pointer(node->then->ty);
    } else {
      usual_arith_conv(&node->then, &node->els, true);
      node->ty = node->then->ty;
    }
    return;
  case ND_CHAIN:
    node->ty = node->rhs->ty;
    return;
  case ND_COMMA:
    node->ty = array_to_pointer(node->rhs->ty);
    return;
  case ND_MEMBER:
    node->ty = node->member->ty;
    return;
  case ND_ADDR:
    node->ty = pointer_to(node->lhs->ty);
    return;
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
        node->ty = array_to_pointer(stmt->lhs->ty);
        return;
      }
    }
    node->ty = basic_type(TY_VOID);
    return;
  case ND_LABEL_VAL:
    node->ty = pointer_to(basic_type(TY_VOID));
    return;
  }
}
