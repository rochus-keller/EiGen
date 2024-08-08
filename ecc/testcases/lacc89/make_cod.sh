# Author: Rochus Keller, 2024

for t in *.c
do
    echo "compiling $t"
    ./compiler -S -w  $t -I../../include
done
