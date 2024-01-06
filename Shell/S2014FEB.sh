#!/bin/bash

for H in 09 10 11 12 13 14 15 16 17 18 19 20 21 22; do
	N=0
	for F in *.log; do
		K=`cut -d" " -f2 $F | grep "^$H:" | wc -l`
		N=`expr $N + $K`
	done
	echo $H $N
done
