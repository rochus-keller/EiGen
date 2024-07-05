# Author: Rochus Keller, 2024

./compiler -lib ../../runtime/runtime.c libc/*.c libm/*.c -D__STDC_WANT_LIB_EXT1__ -I../include -o libc.lib
