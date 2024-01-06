#!/bin/bash

if [ $# -eq 0 ];then
	echo "No Args!"
	exit 1
fi

>raport.txt

while [ $1 ]; do
	if [ ! -d "$1" ];then
		echo 'Only directories'
		
	elif [ -d "$1" ];then
		for i in `find $1 -maxdepth 1 -type f`;do
			if [ -x $i ];then
				size=`wc -c $i | cut -d" " -f1`
				echo $i $size>>raport.txt
			fi
		done
	fi
	shift
done
