#!/bin/bash

while [ -n "$1" ]; do
	if echo $1 | grep -q '^[0-9]*[02468]$'; then
		echo $1
		break
	fi	
	shift
done


