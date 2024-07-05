# Author: Rochus Keller, 2024


for t in *.c
do
    echo "compiling $t"
    gcc $t -w -std=c99 -o ${t%.*}
    ./${t%.*}; echo $?
done
