# Author: Rochus Keller, 2024

for t in *.c
do
    echo "*** compiling $t"
    gcc $t -std=c99 -w -o ${t%.*}
    ./${t%.*}; echo $?
done
