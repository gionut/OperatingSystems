#Write a bash script that calculates the sum of the sizes of all text files in a given folder.

#!/bin/bash

if [ ! $# -eq 1 ]; then
	echo "PLease, provide exactly one character!"
fi

sum=0

for i in `ls $1`; do
	if [ -f "$i" ]; then
		istxt=`file $i | grep -c "text"`
		if [ $istxt -eq 1 ];then
			size=`wc -c $i | cut -d" " -f1`
			sum=$((sum+size))
		fi
	fi
done

echo $sum
	
