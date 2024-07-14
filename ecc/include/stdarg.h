#ifndef __STDARG_H
#define __STDARG_H

#include <stddef.h>

/* this code is ECS chibicc specific! */
#if defined __ECS_C__ || defined __ECS2_C__

#define __va_size(type) (sizeof(type) < __STACK_ALIGNMENT__ ? __STACK_ALIGNMENT__ : sizeof(type))

typedef unsigned char *va_list;
#define va_start(list, param) (list = (((va_list)&param) + __va_size(param)))
#define va_arg(list, type)    (*(type *)((list += __va_size(type)) - __va_size(type)))
#define va_end(ap) (ap = NULL)
#define va_copy( dest, src ) ( (dest) = (src), (void)0 )

#else

#include "pdclib/_PDCLIB_config.h"

typedef _PDCLIB_va_list va_list;

#define va_arg( ap, type )    _PDCLIB_va_arg( ap, type )
#define va_copy( dest, src )  _PDCLIB_va_copy( dest, src )
#define va_end( ap )          _PDCLIB_va_end( ap )
#define va_start( ap, parmN ) _PDCLIB_va_start( ap, parmN )

#endif

#endif
