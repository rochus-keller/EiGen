# Author: Rochus Keller, 2024

flags="-g -w"

for t in libm/*.c
do
    echo "compiling $t"
    ./compiler $(readlink -m $t) $flags -c -I../include 
done

for t in libc/*.c
do
    echo "compiling $t"
    ./compiler $(readlink -m $t) $flags -c -I../include 
done

./compiler ../../runtime/runtime.c -lib $flags *.obf -I../include -o libc.lib

