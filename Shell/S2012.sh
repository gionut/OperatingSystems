#!/bin/bash

for F in *.txt; do
	if grep -i "[aeiou]\{3\}" $F; then
		echo $F
	fi
done
