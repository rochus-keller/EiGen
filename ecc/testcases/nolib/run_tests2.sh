# Author: Rochus Keller, 2024

declare -i count=0
declare -i succs=0

for t in *.c
do
    echo "compiling $t"
	count+=1
    ./compiler $t -w -o ${t%.*} -L/home/me/Programme/ecs/lib/ecs/runtime
    ./${t%.*}
	if [ $? -eq 0 ]; then
		echo 0
		succs+=1
	else
		echo $? "#error"
	fi 
done

echo "result: $succs of $count succeeded"
