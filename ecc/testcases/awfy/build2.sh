# Author: Rochus Keller, 2024

for t in *.c
do
    echo "compiling $t"
    ./compiler $t -g -c -w -I/home/me/Entwicklung/Modules/EiGen/ecc/include
done

./compiler *.obf -g libc.lib -L/home/me/Entwicklung/Modules/EiGen/runtime 
