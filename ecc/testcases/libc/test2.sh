# Author: Rochus Keller, 2024

./compiler ./lib/libc.c -I../../include -lib -o libc.lib

t=00187.c
echo "compiling $t"
./compiler $t -I../../include libc.lib -L/home/me/Programme/ecs/lib/ecs/runtime -o ${t%.*}
./${t%.*}; echo $?
