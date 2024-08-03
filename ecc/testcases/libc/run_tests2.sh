# Author: Rochus Keller, 2024

#./compiler ./lib/libc.c -I../../include -c
./compiler ./lib/libc.c -I../../include -lib -w -o libc.lib

declare -i count=0
declare -i succs=0

for t in *.c
do
    echo "compiling $t"
	count+=1
    #./compiler $t -I../../include -c
    #./compiler ${t%.*}.obf lib/libc.obf -L/home/me/Programme/ecs/lib/ecs/runtime -o ${t%.*}
    ./compiler $t -w -I../../include libc.lib -L/home/me/Programme/ecs/lib/ecs/runtime -o ${t%.*}
    ./${t%.*}
    if [ $? -eq 0 ]; then
		echo 0
		succs+=1
	else
		echo $? "#error"
	fi 
done

echo "result: $succs of $count succeeded"
