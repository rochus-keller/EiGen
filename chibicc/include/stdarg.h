#ifndef __STDARG_H
#define __STDARG_H

#include <stddef.h>

/* this code is ECS chibicc specific! */
#ifdef __ecs_chibicc__
#define __va_size(type) (sizeof(type) < __STACK_ALIGNMENT__ ? __STACK_ALIGNMENT__ : sizeof(type))

typedef unsigned char *va_list;
#define va_start(list, param) (list = (((va_list)&param) + __va_size(param)))
#define va_arg(list, type)    (*(type *)((list += __va_size(type)) - __va_size(type)))
#define va_end(ap) (ap = NULL)
#endif

#endif
