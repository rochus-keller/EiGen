# Author: Rochus Keller, 2024

for t in *.c
do
    echo "running $t"
    ./${t%.*}; echo $?
done
