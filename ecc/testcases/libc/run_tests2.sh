# Author: Rochus Keller, 2024

flags="-g -w"

./compiler $(readlink -m ./lib/libc.c) -I../../include $flags -c 
./compiler $(readlink -m ../../../runtime/runtime.c) -I../../include $flags -c
./compiler libc.obf runtime.obf -lib $flags -o libc.lib

for t in *.c
do
    echo "compiling $t"
    ./compiler $(readlink -m $t) $flags -I../../include libc.lib -L../../../runtime -o ${t%.*}
    ./${t%.*}; echo $?
done


