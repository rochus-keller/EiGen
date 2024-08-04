# Author: Rochus Keller, 2024

for t in libm/*.c
do
    echo "compiling $t"
    ./compiler $t -c -w -I../include 
done

for t in libc/*.c
do
    echo "compiling $t"
    ./compiler $t -c -w -I../include 
done

./compiler ../../runtime/runtime.c -ar *.obf -I../include -L/home/me/Programme/ecs/lib/ecs/runtime -o libc.lib

