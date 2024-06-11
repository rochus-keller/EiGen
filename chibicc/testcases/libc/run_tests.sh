# Author: Rochus Keller, 2024

export PATH=$PATH:/home/me/Programme/ecs/bin

for t in *.c
do
    echo "compiling $t"
    ./chibicc -S $t -I../../include
    ecsd -g "${t%.*}.cod"
   # ./${t%.*}; echo $?
done
