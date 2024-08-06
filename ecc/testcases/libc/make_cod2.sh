# Author: Rochus Keller, 2024

./compiler -S ./lib/libc.c -I../../include 

for t in *.c
do
    echo "compiling $t" 
    ./compiler -g -S  $t  -I../../include
done
