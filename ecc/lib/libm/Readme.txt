This is a refactored version of the libm part of uClibc-ng 1.0.49, as 
downloaded from https://downloads.uclibc-ng.org/releases/1.0.49/
on 2024-06-22.

The e_, s_ and w_ versions of the files have been merged so that each
group of same functions (just differing in double vs float arguments)
are in one file. 
Legacy preprocessor directives have been removed as well as dependencies
on the configuration mechanisms required for multi-target support.
The result is a set of plain, platform independent C files which
nicely compile with ecc.
