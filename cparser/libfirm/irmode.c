#include "irmode.h"

/**
 * A descriptor for an IEEE754 float value.
 */
typedef struct float_descriptor_t {
    unsigned char exponent_size;    /**< size of exponent in bits */
    unsigned char mantissa_size;    /**< size of mantissa in bits */
    unsigned char explicit_one;     /**< set if the leading one is explicit */
} float_descriptor_t;


struct ir_mode {
    ir_mode_arithmetic arithmetic; /**< Class of possible arithmetic ops */
    unsigned           size;       /**< Size of the mode in Bits. */
    unsigned char      sign:1;     /**< Whether mode has a sign bit. */
    float_descriptor_t float_desc; /**< Floatingpoint descriptor */

    ir_tarval          *null;      /**< The value 0 */
    ir_tarval          *one;       /**< The value 1 */
};

ir_mode *mode_Ls = 0;
ir_mode *mode_Lu = 0;

ir_mode *mode_P = 0;

unsigned get_mode_size_bytes(const ir_mode *mode)
{
    unsigned size = mode->size;
    if ((size & 7) != 0) return (unsigned) -1;
    return size >> 3;
}

int mode_is_signed(const ir_mode *mode)
{
    return mode->sign;
}

ir_tarval *get_mode_null(const ir_mode *mode)
{
    return mode->null;
}

ir_tarval *get_mode_one(const ir_mode *mode)
{
    return mode->one;
}

unsigned get_mode_exponent_size(const ir_mode *mode)
{
    return mode->float_desc.exponent_size;
}

unsigned get_mode_mantissa_size(const ir_mode *mode)
{
    return mode->float_desc.mantissa_size;
}

ir_mode_arithmetic get_mode_arithmetic(const ir_mode *mode)
{
    return mode->arithmetic;
}

ir_mode *get_reference_offset_mode(const ir_mode *mode)
{
    return 0; // TODO
}

int mode_is_float(const ir_mode *mode)
{
    return 0;
}

ir_tarval *get_mode_max(const ir_mode *mode)
{
    return 0;
}

ir_tarval *get_mode_min(const ir_mode *mode)
{
    return 0;
}

ir_tarval *get_mode_infinite(const ir_mode *mode)
{
    return 0;
}

unsigned get_mode_size_bits(const ir_mode *mode)
{
    return 0;
}

ir_tarval *get_mode_all_one(const ir_mode *mode)
{
    return 0;
}

