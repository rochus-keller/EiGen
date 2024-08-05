# Author: Rochus Keller, 2024

for t in libm/*.c
do
    echo "compiling $t"
    ./compiler $t -g -S -w -I../include 
done

for t in libc/*.c
do
    echo "compiling $t"
    ./compiler $t -g -S -w -I../include 
done


