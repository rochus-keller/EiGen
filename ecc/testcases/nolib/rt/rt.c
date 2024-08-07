#include <eigen/lib_adapter.h>
#include <stdlib.h>

#include "../../../../runtime/runtime.c"

void _Exit(int code)
{
	exit(code);
}

#if defined(__unix__) || defined(__linux__)
LIBRARY(libc, "libc.so.6");
#elif defined(__APPLE__)
LIBRARY(libc, "/usr/lib/libSystem.B.dylib");
#else
#error "no libc available for given OS"
#endif
FUNCTION(libc, putchar,1);
FUNCTION(libc, exit,1);
