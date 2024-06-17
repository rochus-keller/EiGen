# Author: Rochus Keller, 2024

#./compiler ./lib/libc.c -I../../include -c
./compiler ./lib/libc.c -I../../include -lib -o libc.lib

for t in *.c
do
    echo "compiling $t"
    #./compiler $t -I../../include -c
    #./compiler ${t%.*}.obf lib/libc.obf -L/home/me/Programme/ecs/lib/ecs/runtime -o ${t%.*}
    ./compiler $t -I../../include libc.lib -L/home/me/Programme/ecs/lib/ecs/runtime -o ${t%.*}
    ./${t%.*}; echo $?
done
