# Author: Rochus Keller, 2024

for t in *.c
do
    echo "compiling $t"
    ./compiler -g -S -w  $t -Iinclude
done
