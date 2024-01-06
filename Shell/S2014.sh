#!/bin/bash
echo $#: $*

p=`echo $1 | grep "^[^0-9]*[0-9]$"`
if [ "$p" != "" ]; then
	shift
	./S2014.sh $*
fi

