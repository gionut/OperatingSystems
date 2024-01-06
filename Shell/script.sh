#!/bin/bash

N=$1
shift

while [ $1 ]; do
	K=`find $1 -maxdepth 1 -type d | tail -n+2 | wc -l`
	if [ $K -ge $N ];then
		echo $1
	fi
	shift
done
