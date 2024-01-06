#!/bin/bash


if [ $# -eq 0 ]; then
	echo 'Provide Arguments!'
	exit
fi

echo "" > raportPB3.txt

SUM=0
WORDS=0

while [ $1 ]; do
	NR=`echo $1 | grep "^[0-9]*$"`	
	if [ ! -f $1 ]; then
		if [ -z $NR ]; then
			echo 'Arguments must be files or numbers'
			exit
		else
			SUM=`expr $SUM + $NR`
		fi
	else
		W=`wc -w $1 | cut -d" " -f1`
		WORDS=`expr $WORDS + $W`
	fi
	shift
done

echo $SUM>>raportPB3.txt
echo $WORDS>>raportPB3.txt

