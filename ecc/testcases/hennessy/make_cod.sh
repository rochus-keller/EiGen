# Author: Rochus Keller, 2024

for t in *.c
do
    echo "compiling $t"
    ./compiler $t -S -w -I/home/me/Entwicklung/Modules/EiGen/ecc/include
done


