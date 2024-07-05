# Author: Rochus Keller, 2024

t=binarytrees.c
echo "** compiling $t"
./compiler -I../../include -L../../../runtime -o ${t%.*} libc.lib $t 
./${t%.*}; echo $?

