# Author: Rochus Keller, 2024

export PATH=$PATH:/home/me/Programme/ecs/bin

./chibicc -S ./lib/libc.c -I../../include
ecsd -l ./lib/*.cod

t=test5.c
echo "compiling $t"
./chibicc -S $t -I../../include
ecsd "${t%.*}.cod" libc.lib
./${t%.*}; echo $?

