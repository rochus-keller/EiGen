# Author: Rochus Keller, 2024

for t in *.c
do
    echo "compiling $t"
    ./cparser -std=c99 -O2 -c -w -DOBX_USE_BOEHM_GC -I/usr/include/i386-linux-gnu -I/usr/lib/gcc/i686-linux-gnu/4.8/include $t 
done

./cparser *.o -lm -lgc -o awfy
