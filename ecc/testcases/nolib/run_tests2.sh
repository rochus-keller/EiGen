# Author: Rochus Keller, 2024

declare -i count=0
declare -i succs=0

./compiler $(readlink -m ./rt/rt.c) -lib -I../../include -w -o rt.lib

for t in *.c
do
    echo "compiling $t"
	count+=1
    ./compiler $(readlink -m $t) -g -w -o ${t%.*} rt.lib -L../../../runtime
    ./${t%.*}
	if [ $? -eq 0 ]; then
		echo 0
		succs+=1
	else
		echo $? "#error"
	fi 
done

echo "result: $succs of $count succeeded"
