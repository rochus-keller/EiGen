# Author: Rochus Keller, 2024

./compiler $(readlink -m ./lib/libc.c) -I../../include -c -g -w -o libc.obf

declare -i count=0
declare -i succs=0

for t in *.c
do
    echo "compiling $t"
	count+=1
    ./compiler $(readlink -m $t) -g -w -I../../include libc.obf libc.dbf -L../../../runtime -o ${t%.*}
    ./${t%.*}
    if [ $? -eq 0 ]; then
		echo 0
		succs+=1
	else
		echo $? "#error"
	fi 
done

echo "result: $succs of $count succeeded"
