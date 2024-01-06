#!/bin/bash
sum=0

for A in $*; do
	result=`echo $A | grep "^[0-9]$"`
	if [ "$result" != "" ] ; then
		sum=`expr $sum + $result`
	fi
done

echo $sum
