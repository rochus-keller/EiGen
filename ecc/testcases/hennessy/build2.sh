# Author: Rochus Keller, 2024

flags=" -w"

for t in *.c
do
    echo "compiling $t"
    ./compiler $(readlink -m $t) $flags -c -I../../include
done

./compiler *.obf $flags libc.lib -L../../../runtime 
