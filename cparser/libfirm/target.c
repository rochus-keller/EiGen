#include "target.h"

// TODO: dummy implementation

ir_mode *ir_platform_type_mode(ir_platform_type_t type, int is_signed)
{
    return 0;
}


ir_platform_type_t ir_platform_wchar_type()
{
    return IR_TYPE_INT;
}

int ir_platform_wchar_is_signed()
{
    return 0;
}
