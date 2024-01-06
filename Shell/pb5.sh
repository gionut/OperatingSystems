#!/bin/bash

echo "">reportPB5.txt

while [ $1 ]; do
	if [ -d $1 ]; then
		for F in `find $1 -maxdepth 1 -type f -name "*.c"`; do
			grep "^#include" $F>>reportPB5.txt
		done	
	fi
	shift
done

