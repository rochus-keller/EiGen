# Author: Rochus Keller, 2024

for t in *.c
do
    echo "compiling $t"
    ./cparser -S -w -I/home/me/Entwicklung/Modules/EiGen/ecc/include $t 
done
