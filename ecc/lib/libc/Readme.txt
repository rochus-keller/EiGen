This is a refactored version of PDCLib, commit 6f9869e by 2024-05-27, as 
downloaded from https://github.com/DevSolar/pdclib on 2024-06-24.

Many changes were necessary so it compiles with ecc (which is a tiny C
compiler based on chibicc). The files which not yet compile with ecc
are in the pending subfolder.

All C files of the original "functions" directory have been copied here
so they can easily be compiled by "ecc *.c". The subdirectories
_dtoa and _dlmalloc have not yet been considered since this code
depends on functions not part of PDCLIB.

The goal of this migration is to have a stand-alone libc version with
no dependencies to operating system headers and libraries, but only
to the OS adapters implemented in the ECC runtime library.

The glue_imp.c and glue_consts.c file currently include all declarations
required to build a complete application with the test.c and BUSY files
in the super directory, with no missing symbols. The application
doesn't do anything yet, but there is no dependency on system
headers or libraries.
