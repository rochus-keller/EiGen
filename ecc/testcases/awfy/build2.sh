# Author: Rochus Keller, 2024

flags=" -w -DOBX_USE_BOEHM_GC" 
# apparently the debugger crashes on GC_ calls, so debug witout -DOBX_USE_BOEHM_GC

for t in *.c
do
    echo "compiling $t"
    ./compiler $(readlink -m $t) $flags -c -I../../include
done

./compiler *.obf $flags libc.lib -L../../../runtime 
