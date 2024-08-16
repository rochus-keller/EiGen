# Author: Rochus Keller, 2024

flags="-g -w " 

for t in *.c
do
    echo "compiling $t"
    ./compiler $(readlink -m $t) $flags -c -Iinclude
done

./compiler *.obf $flags libc.lib -L../runtime 