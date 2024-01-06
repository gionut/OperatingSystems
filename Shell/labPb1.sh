#!/bin/bash

EXTENSII=`cat extern.txt`
echo "$EXTENSII"
#while [ $1 ]; do

	for extensie in $EXTENSII; do
		for file in $1; do
			echo $file
			#N=`grep - q "^[^.].$extensie"`
			#echo $N
		done	
	done
#shift
#done
