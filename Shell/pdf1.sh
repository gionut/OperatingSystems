#!/bin/bash

for f in `find -type f -name \*.txt`;do
	S=`grep "cat" $f | wc -c`
	if [ $S -gt 0 ];then
		echo $f
	fi
done
