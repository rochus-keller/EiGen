# Author: Rochus Keller, 2024

flags=" -w"

./compiler *.c $flags libc.lib -I../../include -L../../../runtime 
