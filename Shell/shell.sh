#!/bin/bash

while [ $1 ]; do
	NAME=`cat passwd.fake | grep "$1" | awk -F: '{print $1}'`
	if [ ! -z $NAME ];then
		echo $1
	fi
	shift
done
