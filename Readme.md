This project aims to develop a reusable cross-platform compiler backend for the i386, x86_64, ARM and AArch64 architectures based on 
the Eigen Compiler Suite (see https://ecs.openbrace.org/).

The original code is written in C++17 and doesn't compile with MSVC or old GCC versions.

The contribution of this project is the migration of a subset of the ECS code base to a conservative C++11 dialect, so it compiles on old GCC versions as well as on MSVC.

Yet another goal is to make the chibicc C compiler cross-platform (the original version depends on Posix) and generate ECS IR instead of AMD64.


#### Status on April 7, 2024

The source code of the cp*, *asm and linkbin tools has been successfully migrated.

The tools have been successfully tested on Linux i386 with GCC 4.8 and on Windows 10 with MSVC 2015 (compiler version 14.0).
It has to be noted that even when the source code compiled with no errors on the mentioned compilers there were still crashes.
Thus migration and debugging continued until the crashes vanished. 

Therefore the resulting tools (i.e. the ones listed in the BUSY file) seem to be fit for purpose as specified in the official ECS documentation.

The chibicc C compiler was refactored so it no longer depends on Posix; the ECS IR backend is work in progress.

#### Status on June 13, 2024

The chibicc C compiler (renamed to ecc) now generates Eigen IR. The IR generated from 213 testcases successfully runs on x86 and arm linux, both 32 and 64 bit. The compiler was merged with the master branch and is ready for extended testing.

More refactorings and patches have been applied to the Eigen source code. 

#### Status on June 14, 2024

There is now a version of ecc which is integrated with all the ECS generators and linkers in this repository resulting in a single executable which combines the C compiler and the linker; to generate executables still some of the obf files from the ECS runtime directory are required (the latter to be referenced by -L). The compiler can be used in the same way as other C compilers, with options like -c, -o and -I; in addition the target architecture, for which an executable, object file or library is to be created, can be set using the -t option. See -h for the available options.

The generated code by chibicc is not (yet) particularly efficient; others (see e.g. https://github.com/vnmakarov/mir) have chibicc found to generate code which is about factor 0.3 as fast as gcc -O2, and 0.6 as fast as TCC. I intend to add a peephole optimizer to improve performance, but it's not a high priority. The focus is now on a runtime library based on Newlib.

#### Precompiled versions

Not available at this time.

#### How to build

1. Create a new directory; we call it the root directory here
1. Download https://github.com/rochus-keller/EiGen/archive/refs/heads/master.zip and unpack it to the root directory; rename the resulting directory to "EiGen".
1. Download https://github.com/rochus-keller/BUSY/archive/refs/heads/master.zip and unpack it to the root directory; rename the resulting directory to "build".
1. Open a command line in the build directory and type `cc *.c -O2 -lm -o lua` or `cl /O2 /MD /Fe:lua.exe *.c` depending on whether you are on a Unix or Windows machine; wait a few seconds until the Lua executable is built.
1. Now type `./lua build.lua ../EiGen` (or `lua build.lua ../EiGen` on Windows); wait until the executable is built; you find it in the output subdirectory.

Alternatively you can open the BUSY file with LeanCreator (see https://github.com/rochus-keller/LeanCreator/) and build it there using multiple cores.

#### Additional Credits

This project uses a subset of the source code version 0.0.40 (dated 13 March 2024 16:05) 
provided at https://software.openbrace.org/projects/ecs/files
made available under GPL v3 or later by its original author, Florian Negele.



