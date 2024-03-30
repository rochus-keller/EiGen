This project aims to develop a reusable cross-platform compiler backend for the i386, x86_64, ARM and AArch64 architectures based on 
the Eigen Compiler Suite (see https://ecs.openbrace.org/).

The original code is written in C++17 and doesn't compile with MSVC.

The contribution of this project is the migration to C++11 and (eventually) MSVC compatibility.

NOTE that this project is work in progress.

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
made available under GPL v3 or later by its author, copyright (C) Florian Negele.



