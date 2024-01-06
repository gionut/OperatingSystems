#!/bin/bash

sum=0

while [ $sum -le 10 ]; do
	read -p "Value: " k
	if echo $k | grep -q "^[0-9]\+$"; then
	      sum=`expr $sum + $k`	
	fi
done

echo "$sum"
