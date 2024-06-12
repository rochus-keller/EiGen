# Author: Rochus Keller, 2024

export PATH=$PATH:/home/me/Programme/ecs/bin

for t in *.c
do
    echo "compiling $t"
    ./ecc -S $t
    ecsd -g -t amd64linux "${t%.*}.cod"
done
