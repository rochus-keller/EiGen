# Author: Rochus Keller, 2024

./compiler ./lib/libc.c -I../../include -lib -o libc.lib

t=struct_return2.c
echo "compiling $t"
./compiler -S $t -I../../include
./compiler $t -I../../include libc.lib -L/home/me/Programme/ecs/lib/ecs/runtime -o ${t%.*}
./${t%.*}; echo $?
