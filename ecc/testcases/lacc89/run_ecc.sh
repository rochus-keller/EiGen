# Author: Rochus Keller, 2024

for t in *.c
do
    echo "*** compiling $t"
    ./compiler $(readlink -m $t) -g -w -I../../include libc.lib -L../../../runtime -o ${t%.*}
    ./${t%.*}; echo $?
done
