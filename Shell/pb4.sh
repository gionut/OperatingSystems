#!/bin/bash

while [ $1 ]; do
	if [ -f $1 ]; then
		NAME=`echo $1 | cut -d"." -f1`
		CONTENT=`wc -w $1 | cut -d" " -f1`
		echo $CONTENT>$NAME.info
	elif [ -d $1 ]; then
		NAME=`echo $1 | awk -F/ '{print $NF}'` 
		CONTENT=`ls -l $1 | tail -n+2 | wc -l`
		echo $CONTENT>$NAME.info
	else
		echo $1 > error_report
	fi
	shift
done
