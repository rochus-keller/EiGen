#include "irmode.h"
#include "target.h"
#include "tv.h"
#include <inttypes.h>

struct ir_mode {
    ir_platform_type_t type;
    uint8_t size; // in bytes
    uint8_t signed_; // false:0 or true:1
};

static struct ir_mode ir_modes[] =
{
{ IR_TYPE_BOOL, 1, 1 },
{ IR_TYPE_CHAR, 1, 1 },
{ IR_TYPE_SHORT, 2, 1 },
{ IR_TYPE_INT, 4, 1 },
{ IR_TYPE_LONG, 4, 1 },
{ IR_TYPE_LONG_LONG, 8, 1 },
{ IR_TYPE_FLOAT, 4, 1 },
{ IR_TYPE_DOUBLE, 8, 1 },
{ IR_TYPE_LONG_DOUBLE, 8, 1 },
};

static struct ir_mode ir_umodes[] =
{
{ IR_TYPE_BOOL, 1, 0 },
{ IR_TYPE_CHAR, 1, 0 },
{ IR_TYPE_SHORT, 2, 0 },
{ IR_TYPE_INT, 4, 0 },
{ IR_TYPE_LONG, 4, 0 },
{ IR_TYPE_LONG_LONG, 8, 0 },
{ IR_TYPE_FLOAT, 4, 0 },
{ IR_TYPE_DOUBLE, 8, 0 },
{ IR_TYPE_LONG_DOUBLE, 8, 0 },
};

ir_mode *mode_Ls = &ir_modes[IR_TYPE_LONG];
ir_mode *mode_Lu = &ir_umodes[IR_TYPE_LONG];

ir_mode *mode_P = &ir_umodes[IR_TYPE_LONG];

unsigned get_mode_size_bytes(const ir_mode *mode)
{
    return mode->size;
}

int mode_is_signed(const ir_mode *mode)
{
    if( mode == 0 )
        return 0;
    return mode->signed_;
}

unsigned get_mode_size_bits(const ir_mode *mode)
{
    if( mode == 0 )
        return 0;
    return mode->size * 8;
}

ir_mode *ir_platform_type_mode(ir_platform_type_t type, int is_signed)
{
    if( is_signed )
        return &ir_modes[type];
    else
        return &ir_umodes[type];
}

ir_platform_type_t ir_platform_wchar_type()
{
    return IR_TYPE_SHORT;
}

int ir_platform_wchar_is_signed()
{
    return 0;
}

ir_mode_arithmetic get_mode_arithmetic(const ir_mode *mode)
{
    if( mode_is_float(mode) )
        return irma_ieee754;
    else
        return irma_twos_complement;
}

int mode_is_float(const ir_mode *mode)
{
    if( mode == 0 )
        return 0;
    return mode->type >= IR_TYPE_FLOAT;
}

unsigned get_mode_exponent_size(const ir_mode *mode)
{
    if( mode == 0 )
        return 0;
    switch(mode->type)
    {
    case IR_TYPE_FLOAT:
        return 8;
    case IR_TYPE_DOUBLE:
    case IR_TYPE_LONG_DOUBLE:
        return 11;
    }
    return 0;
}

unsigned get_mode_mantissa_size(const ir_mode *mode)
{
    if( mode == 0 )
        return 0;
    switch(mode->type)
    {
    case IR_TYPE_FLOAT:
        return 23;
    case IR_TYPE_DOUBLE:
    case IR_TYPE_LONG_DOUBLE:
        return 52;
    }
    return 0;
}

ir_mode *get_reference_offset_mode(const ir_mode *mode)
{
    return mode_Ls;
}

ir_mode *ir_common_mode(const ir_mode *lhs, const ir_mode *rhs)
{
    if( lhs == 0 || rhs == 0 )
        return 0;
    if( mode_is_float(lhs) && mode_is_float(rhs) ||
            mode_is_signed(lhs) && mode_is_signed(rhs) ||
            mode_is_int(lhs) && mode_is_int(rhs) )
    {
        if( lhs->type < rhs->type )
            return rhs;
        else
            return lhs;
    }
    return 0;
}

int mode_is_int(const ir_mode *mode)
{
    if( mode == 0 )
        return 0;
    return mode->type < IR_TYPE_FLOAT;
}
