#!/bin/bash

CURRENTDATE=`date "+%D" | awk -F/ '{print $1 "/" $2}'`

echo -n "">reportTEST.txt

while [ $1 ]; do
	while read a; do
		DATE=`echo $a | awk -F/ '{print $1 "/" $2}'`
		NAME=`echo $a | awk -F- '{print $2}'`

		if [ $DATE == $CURRENTDATE ]; then
			echo $NAME>>reportTEST.txt	
		fi
	done<$1
	shift
done

