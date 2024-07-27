# Author: Rochus Keller, 2024

export PATH=$PATH:/home/me/Programme/ecs/bin

for t in *.c
do
    echo "compiling $t"
    ./compiler -S -w $t
    ecsd -g "${t%.*}.cod"
    ./${t%.*}; echo $?
done
