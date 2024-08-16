#include "tv.h"
#include "irmode.h"
#include "target.h"

#include <inttypes.h>
#include <alloca.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include <stdbool.h>

static bool do_check_mode_compat = false;

struct ir_tarval {
    ir_mode      *mode;    /**< the mode of the stored value */
    union {
        double d;
        uint64_t u;
        int64_t l;
    };
};

int tarval_is_null(const ir_tarval *tv)
{
    if( mode_is_float(tv->mode) )
        return tv->d == 0.0;
    return tv->l == 0;
}

int tarval_is_negative(const ir_tarval *tv)
{
    if( mode_is_float(tv->mode) )
        return tv->d < 0.0;
    if( mode_is_signed(tv->mode) )
        return tv->l < 0;
    return 0;
}

int tarval_is_constant(const ir_tarval *tv)
{
    return 1;
}

static ir_tarval bad = { 0, 0 };
ir_tarval *const tarval_bad = &bad;

int tarval_get_wrap_on_overflow()
{
    return !do_check_mode_compat;
}

static ir_tarval* new_float(double d, ir_mode* m) {
    ir_tarval* res = malloc(sizeof(ir_tarval)); // RISK
    res->mode = m;
    res->d = d;
    return res;
}

static ir_tarval* new_signed(int64_t l, ir_mode* m) {
    ir_tarval* res = malloc(sizeof(ir_tarval)); // RISK
    res->mode = m;
    res->l = l;
    return res;
}

static ir_tarval* new_unsigned(uint64_t u, ir_mode* m) {
    ir_tarval* res = malloc(sizeof(ir_tarval)); // RISK
    res->mode = m;
    res->u = u;
    return res;
}

void tarval_set_wrap_on_overflow(int wrap_on_overflow)
{
    do_check_mode_compat = !wrap_on_overflow;
}

ir_tarval *tarval_neg(const ir_tarval *a)
{
    if( mode_is_float(a->mode) )
        return new_float(-a->d, a->mode);
    if( mode_is_signed(a->mode) )
        return new_signed(-a->l,a->mode);
    return tarval_bad;
}

ir_tarval *tarval_not(const ir_tarval *a)
{
    if( mode_is_float(a->mode) )
        return tarval_bad;
    if( mode_is_signed(a->mode) )
        return new_signed(!a->l,a->mode);
    else
        return new_unsigned(!a->u,a->mode);
}

long get_tarval_long(const ir_tarval *tv)
{
    if( mode_is_float(tv->mode) )
        return tv->d;
    if( mode_is_signed(tv->mode) )
        return tv->l;
    else
        return tv->u;
}

int get_tarval_highest_bit(const ir_tarval *tv)
{
    if( mode_is_float(tv->mode) )
        return tarval_bad;
    if( tv->u > 0xfffffffffffffff )
        return 63;
    if( tv->u > 0xffffffffffffff )
        return 59;
    if( tv->u > 0xfffffffffffff )
        return 55;
    if( tv->u > 0xffffffffffff )
        return 51;
    if( tv->u > 0xfffffffffff )
        return 47;
    if( tv->u > 0xffffffffff )
        return 43;
    if( tv->u > 0xfffffffff )
        return 39;
    if( tv->u > 0xffffffff )
        return 35;
    if( tv->u > 0xfffffff )
        return 31;
    if( tv->u > 0xffffff )
        return 27;
    if( tv->u > 0xfffff )
        return 23;
    if( tv->u > 0xffff )
        return 19;
    if( tv->u > 0xfff )
        return 15;
    if( tv->u > 0xff )
        return 11;
    if( tv->u > 0xf )
        return 7;
    return 3;
}

static bool startswith(char *p, char *q) {
  return strncmp(p, q, strlen(q)) == 0;
}

static ir_tarval * convert_to_int(char* str, int len) {
  char *p = str;

  // Read a binary, octal, decimal or hexadecimal number.
  int base = 10;
  if ( p[0] == '0' && ( p[1] == 'x' || p[1] == 'X') && isxdigit(p[2])) {
    p += 2;
    base = 16;
  } else if (p[0] == '0' && ( p[1] == 'b' || p[1] == 'B') && (p[2] == '0' || p[2] == '1')) {
    p += 2;
    base = 2;
  } else if (*p == '0') {
    base = 8;
  }

  int64_t val = strtoull(p, &p, base);

  // Read U, L or LL suffixes.
  bool l = false;
  bool u = false;

  char tmp[3] = "xy";
  tmp[0] = tolower(p[0]);
  tmp[1] = tolower(p[1]);

  if (startswith(p, "LLU") || startswith(p, "LLu") ||
      startswith(p, "llU") || startswith(p, "llu") ||
      startswith(p, "ULL") || startswith(p, "Ull") ||
      startswith(p, "uLL") || startswith(p, "ull")) {
    p += 3;
    l = u = true;
  } else if (startswith(tmp, "lu") || startswith(tmp, "ul")) {
    p += 2;
    l = u = true;
  } else if (startswith(tmp, "LL") || startswith(tmp, "ll")) {
    p += 2;
    l = true;
  } else if (*p == 'L' || *p == 'l') {
    p++;
    l = true;
  } else if (*p == 'U' || *p == 'u') {
    p++;
    u = true;
  }

  if (p != str + len)
    return tarval_bad;

  // Infer a type.
  ir_mode* ty = 0;
  if (base == 10) {
    if (l && u)
      ty = ir_platform_type_mode(IR_TYPE_LONG_LONG,false);
    else if (l)
      ty = ir_platform_type_mode(IR_TYPE_LONG_LONG,true);
    else if (u)
      ty = (val >> 32) ? ir_platform_type_mode(IR_TYPE_LONG_LONG,false) : ir_platform_type_mode(IR_TYPE_INT,false);
    else
      ty = (val >> 31) ? ir_platform_type_mode(IR_TYPE_LONG_LONG,true) : ir_platform_type_mode(IR_TYPE_INT,true);
  } else {
    if (l && u)
      ty = ir_platform_type_mode(IR_TYPE_LONG_LONG,false);
    else if (l)
      ty = ir_platform_type_mode(IR_TYPE_LONG_LONG, !(val >> 63));
    else if (u)
      ty = (val >> 32) ? ir_platform_type_mode(IR_TYPE_LONG_LONG,false) : ir_platform_type_mode(IR_TYPE_INT,false);
    else if (val >> 63)
      ty = ir_platform_type_mode(IR_TYPE_LONG_LONG,false);
    else if (val >> 32)
      ty = ir_platform_type_mode(IR_TYPE_LONG_LONG,true);
    else if (val >> 31)
      ty = ir_platform_type_mode(IR_TYPE_INT,false);
    else
      ty = ir_platform_type_mode(IR_TYPE_INT,true);
  }

  return new_signed(val, ty);
}

static ir_tarval * convert_to_number(char* str, int len) {
  // Try to parse as an integer constant.
    ir_tarval * res = convert_to_int(str,len);
  if (res != tarval_bad)
    return res;

  // If it's not an integer, it must be a floating point constant.
  char *end;
  long double val = strtold(str, &end);

  ir_mode* ty;
  if (*end == 'f' || *end == 'F') {
    ty = ir_platform_type_mode(IR_TYPE_FLOAT,true);
    end++;
  } else if (*end == 'l' || *end == 'L') {
    ty = ir_platform_type_mode(IR_TYPE_LONG_DOUBLE,true);
    end++;
  } else {
    ty = ir_platform_type_mode(IR_TYPE_DOUBLE,true);
  }

  if (str + len != end)
      return tarval_bad;

  return new_float(val, ty);
}

// this is not only to convert from string to any number, but it is supposed to
// check whether the read number fits the given mode, and return bad otherwise
ir_tarval *new_tarval_from_str(const char *str, size_t len, ir_mode *mode)
{
    if( do_check_mode_compat )
    {
        ir_tarval * res = convert_to_number(str,len);
        if( res->mode == mode )
            return res;
        else
            return tarval_bad;
    }else
    {
        if( mode_is_float(mode) )
            return new_float(strtod(str,0), mode);
        if( mode_is_signed(mode) ) {
            if( get_mode_size_bytes(mode) <= 4 )
                return new_signed(strtol(str,0,0), mode);
            else
                return new_signed(strtoll(str,0,0), mode);
        }else
            return new_unsigned(strtoull(str,0,0), mode);
    }
}

ir_tarval *new_tarval_from_long(long l, ir_mode *mode)
{
    if( mode_is_float(mode) )
        return new_float(l, mode);
    if( mode_is_signed(mode) )
        return new_signed(l, mode);
    return new_unsigned(l, mode);
}

ir_mode *get_tarval_mode(const ir_tarval *tv)
{
    return tv->mode;
}

int tarval_is_long(const ir_tarval *tv)
{
    if( mode_is_float(tv->mode) )
        return 0;
    return get_mode_size_bytes(tv->mode) <= get_mode_size_bytes(mode_Ls);
}

ir_tarval *new_tarval_nan(ir_mode *mode, int signaling, const ir_tarval *payload)
{
    return new_float(NAN,mode);
}

ir_tarval *tarval_convert_to(const ir_tarval *src, ir_mode *mode)
{
    if( mode_is_float(src->mode) ) {
        if( mode_is_float(mode) )
            return new_float(src->d, mode);
        if( mode_is_signed(mode) )
            return new_signed(src->d,mode);
        else
            return new_unsigned(src->d, mode);
    }
    if( mode_is_signed(src->mode) ) {
        if( mode_is_float(mode) )
            return new_float(src->l, mode);
        if( mode_is_signed(mode) )
            return new_signed(src->l,mode);
        else
            return new_unsigned(src->l, mode);
    }
    if( mode_is_float(mode) )
        return new_float(src->u, mode);
    if( mode_is_signed(mode) )
        return new_signed(src->u,mode);
    else
        return new_unsigned(src->u, mode);
}

ir_tarval *get_mode_null(const ir_mode *mode)
{
    if( mode_is_float(mode) )
        return new_float(0,mode);
    if( mode_is_int(mode) )
    {
        if( mode_is_signed(mode) )
            return new_signed(0,mode);
        else
            return new_unsigned(0,mode);
    }
    return tarval_bad;
}

ir_tarval *get_mode_one(const ir_mode *mode)
{
    if( mode_is_float(mode) )
        return new_float(1,mode);
    if( mode_is_int(mode) )
    {
        if( mode_is_signed(mode) )
            return new_signed(1,mode);
        else
            return new_unsigned(1,mode);
    }
    return tarval_bad;
}

static int64_t maxValueOfSigned(int bits)
{
    return (1ll << ( bits - 1 )) - 1;
}

static int64_t maxValueOfUnsigned(int bits)
{
    return (1ll << ( bits )) - 1;
}

ir_tarval *get_mode_max(const ir_mode *mode)
{
    if( mode_is_float(mode) )
        return new_float(DBL_MAX,mode);
    if( mode_is_int(mode) )
    {
        if( mode_is_signed(mode) )
            return new_signed(maxValueOfSigned(get_mode_size_bits(mode)),mode);
        else
            return new_unsigned(maxValueOfUnsigned(get_mode_size_bits(mode)),mode);
    }
    return tarval_bad;
}

ir_tarval *get_mode_min(const ir_mode *mode)
{
    if( mode_is_float(mode) )
        return new_float(-DBL_MAX,mode);
    if( mode_is_int(mode) )
    {
        if( mode_is_signed(mode) )
            return new_signed(-maxValueOfSigned(get_mode_size_bits(mode))-1,mode);
        else
            return new_unsigned(0,mode);
    }
    return tarval_bad;
}

ir_tarval *get_mode_infinite(const ir_mode *mode)
{
    if( mode_is_float(mode) )
        return new_float(INFINITY,mode);
    return tarval_bad;
}

ir_tarval *get_mode_all_one(const ir_mode *mode)
{
    if( mode_is_float(mode) || mode_is_signed(mode) )
        return tarval_bad;
    else
        return new_unsigned(maxValueOfUnsigned(get_mode_size_bits(mode)),mode);
}

ir_relation tarval_cmp(const ir_tarval *a, const ir_tarval *b)
{
    ir_mode* t = ir_common_mode(a->mode,b->mode);
    if( t == 0 )
        return ir_relation_false;
    if (a == tarval_bad || b == tarval_bad || a->mode != b->mode)
        return ir_relation_false;

    if( mode_is_float(t) )
    {
        if( a->d == b->d )
            return ir_relation_equal;
        if( a->d < b->d )
            return ir_relation_less;
        else
            return ir_relation_greater;
    }
    if( mode_is_signed(t) )
    {
        if( a->l == b->l )
            return ir_relation_equal;
        if( a->l < b->l )
            return ir_relation_less;
        else
            return ir_relation_greater;
    }
    if( mode_is_int(t) )
    {
        if( a->u == b->u )
            return ir_relation_equal;
        if( a->u < b->u )
            return ir_relation_less;
        else
            return ir_relation_greater;
    }
    panic("cannot compare");
}

ir_tarval *tarval_add(const ir_tarval *a, const ir_tarval *b)
{
    ir_mode* t = ir_common_mode(a->mode,b->mode);
    if( t == 0 )
        return tarval_bad;
    if( mode_is_float(t) )
        return new_float(a->d + b->d,t);
    if( mode_is_signed(t) )
        return new_signed(a->l + b->l,t);
    else
        return new_unsigned(a->u + b->u,t);
}

ir_tarval *tarval_sub(const ir_tarval *a, const ir_tarval *b)
{
    ir_mode* t = ir_common_mode(a->mode,b->mode);
    if( t == 0 )
        return tarval_bad;
    if( mode_is_float(t) )
        return new_float(a->d - b->d,t);
    if( mode_is_signed(t) )
        return new_signed(a->l - b->l,t);
    else
        return new_unsigned(a->u - b->u,t);
}

ir_tarval *tarval_mul(const ir_tarval *a, const ir_tarval *b)
{
    ir_mode* t = ir_common_mode(a->mode,b->mode);
    if( t == 0 )
        return tarval_bad;
    if( mode_is_float(t) )
        return new_float(a->d * b->d,t);
    if( mode_is_signed(t) )
        return new_signed(a->l * b->l,t);
    else
        return new_unsigned(a->u * b->u,t);
}

ir_tarval *tarval_div(const ir_tarval *a, const ir_tarval *b)
{
    ir_mode* t = ir_common_mode(a->mode,b->mode);
    if( t == 0 )
        return tarval_bad;
    if( b->u == 0 )
        return tarval_bad;
    if( mode_is_float(t) )
        return new_float(a->d / b->d,t);
    if( mode_is_signed(t) )
        return new_signed(a->l / b->l,t);
    else
        return new_unsigned(a->u / b->u,t);
}

ir_tarval *tarval_mod(const ir_tarval *a, const ir_tarval *b)
{
    ir_mode* t = ir_common_mode(a->mode,b->mode);
    if( t == 0 )
        return tarval_bad;
    if( b->u == 0 )
        return tarval_bad;
    if( mode_is_float(t) )
        return new_float(fmod(a->d, b->d),t);
    if( mode_is_signed(t) )
        return new_signed(a->l % b->l,t);
    else
        return new_unsigned(a->u % b->u,t);
}

ir_tarval *tarval_and(const ir_tarval *a, const ir_tarval *b)
{
    ir_mode* t = ir_common_mode(a->mode,b->mode);
    if( t == 0 || mode_is_float(t) )
        return tarval_bad;
    if( mode_is_signed(a->mode) )
        return new_signed(a->l & b->l,a->mode);
    else
        return new_unsigned(a->u & b->u,a->mode);
}

ir_tarval *tarval_eor(const ir_tarval *a, const ir_tarval *b)
{
    ir_mode* t = ir_common_mode(a->mode,b->mode);
    if( t == 0 || mode_is_float(t) )
        return tarval_bad;
    if( mode_is_signed(a->mode) )
        return new_signed(a->l ^ b->l,a->mode);
    else
        return new_unsigned(a->u ^ b->u,a->mode);
}

ir_tarval *tarval_or(const ir_tarval *a, const ir_tarval *b)
{
    ir_mode* t = ir_common_mode(a->mode,b->mode);
    if( t == 0 || mode_is_float(t) )
        return tarval_bad;
    if( mode_is_signed(a->mode) )
        return new_signed(a->l | b->l,a->mode);
    else
        return new_unsigned(a->u | b->u,a->mode);
}

ir_tarval *tarval_shl(const ir_tarval *a, const ir_tarval *b)
{
    if( a->mode == 0 || b->mode == 0 ||
            mode_is_float(a->mode) || mode_is_float(b->mode) )
        return tarval_bad;
    if( mode_is_signed(a->mode) )
        return new_signed(a->l << b->l,a->mode);
    else
        return new_unsigned(a->u << b->u,a->mode);
}

ir_tarval *tarval_shr(const ir_tarval *a, const ir_tarval *b)
{
    if( a->mode == 0 || b->mode == 0 ||
            mode_is_float(a->mode) || mode_is_float(b->mode) )
        return tarval_bad;
    if( mode_is_signed(a->mode) )
        return new_signed(a->l >> b->l,a->mode);
    else
        return new_unsigned(a->u >> b->u,a->mode);
}

ir_tarval *tarval_shrs(const ir_tarval *a, const ir_tarval *b)
{
    return tarval_shr(a,b); // TODO
}

ir_tarval *tarval_shr_unsigned(const ir_tarval *a, unsigned b)
{
    if( a->mode == 0 ||  mode_is_float(a->mode) )
        return tarval_bad;
    if( mode_is_signed(a->mode) )
        return new_signed(a->l >> b,a->mode);
    else
        return new_unsigned(a->u >> b,a->mode);
}

ir_tarval *tarval_shrs_unsigned(const ir_tarval *a, unsigned b)
{
    return tarval_shr_unsigned(a,b); // TODO
}
