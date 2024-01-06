#!/bin/bash

sum=0

for F in *.txt; do
	echo `wc -l $F`
	nr=`wc -l $F | cut -d" " -f1`
	if [ $nr -gt 50 ]; then
		sum=`expr $sum + $nr`
	fi
done

echo $sum
