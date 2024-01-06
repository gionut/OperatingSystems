#!/bin/bash

if [ $# -eq 0 ]; then
       echo "Arguments are requiered!"	
       exit
fi

echo "" > raport.txt

while read a; do
	echo "$a 0" >> raport.txt
done<extern.txt

while [ $1 ]; do
	if [ ! -d $1 ]; then
		"Arguments must be ONLY directories!"
		exit
	fi
	while read ext; do
		a=`find $1 -type f -name "*.$ext" | wc -l`
		b=`cat raport.txt | grep "$ext" | cut -d" " -f2`
		s=`expr $a + $b`
		sed -ie "s/^\($ext \)[0-9]*/\1$s/g" raport.txt
	done<extern.txt
	shift
done	
