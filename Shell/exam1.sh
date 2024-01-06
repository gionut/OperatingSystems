#!/bin/bash

files=""

while [ $1 ];do
	if [ `grep $1 $files` ];then
		echo  "stop"
		exit 1
	fi
	echo $1 >> $files
	shift
done

