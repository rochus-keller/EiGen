#include "tv.h"
#include <inttypes.h>

// TODO: dummy implementation

/**
 * This struct represents the aforementioned tarvals.
 *
 * A tarval struct consists of an internal representation of the
 * value and some additional fields further describing the value.
 *
 * @sa
 *   irmode.h for predefined modes
 */
struct ir_tarval {
    uint16_t      length;  /**< the length of the stored value */
    ir_mode      *mode;    /**< the mode of the stored value */
    unsigned char value[]; /**< the value stored in an internal way */
};


int tarval_is_null(const ir_tarval *tv)
{
    return 0;
}

int tarval_is_negative(const ir_tarval *tv)
{
    return 0;
}

int tarval_is_constant(const ir_tarval *tv)
{
    return 0;
}

ir_relation tarval_cmp(const ir_tarval *a, const ir_tarval *b)
{
    return ir_relation_false;
}

ir_tarval *const tarval_bad = 0;

int tarval_get_wrap_on_overflow()
{
    return 0;
}

void tarval_set_wrap_on_overflow(int wrap_on_overflow)
{

}

ir_tarval *tarval_convert_to(const ir_tarval *src, ir_mode *mode)
{
    return 0;
}

ir_tarval *tarval_neg(const ir_tarval *a)
{
    return 0;
}

ir_tarval *tarval_not(const ir_tarval *a)
{
    return 0;
}

long get_tarval_long(const ir_tarval *tv)
{
    return 0;
}

int get_tarval_highest_bit(const ir_tarval *tv)
{
    return 0;
}

ir_tarval *new_tarval_from_str(const char *str, size_t len, ir_mode *mode)
{
    return 0;
}

ir_tarval *new_tarval_from_long(long l, ir_mode *mode)
{
    return 0;
}

ir_mode *get_tarval_mode(const ir_tarval *tv)
{
    return 0;
}

ir_tarval *tarval_add(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_sub(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_mul(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_div(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_mod(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_shl(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_shrs(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_shr(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_and(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_eor(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *tarval_or(const ir_tarval *a, const ir_tarval *b)
{
    return 0;
}

ir_tarval *new_tarval_nan(ir_mode *mode, int signaling, const ir_tarval *payload)
{
    return 0;
}

int tarval_is_long(const ir_tarval *tv)
{
    return 0;
}

ir_tarval *tarval_shr_unsigned(const ir_tarval *a, unsigned b)
{
    return 0;
}

ir_tarval *tarval_shrs_unsigned(const ir_tarval *a, unsigned b)
{
    return 0;
}
