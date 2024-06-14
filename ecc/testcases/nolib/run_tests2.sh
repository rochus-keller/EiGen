# Author: Rochus Keller, 2024

for t in *.c
do
    echo "compiling $t"
    ./compiler $t -o ${t%.*} -L/home/me/Programme/ecs/lib/ecs/runtime
    ./${t%.*}; echo $?
done
