#!/bin/bash

cat $1 | while read line; do
	v = `$line | grep "( *[A-Z][a-z]* *)`
	if [ $v -ge 1 ]; then 
		echo "$NF. $v"  
	fi
done
