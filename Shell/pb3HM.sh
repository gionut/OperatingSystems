#Write a script that receives as command line arguments pairs consisting of a filename and a word. For each pair, check if the given word appears at least 3 times in the file and print a corresponding message.

#!/bin/bash

while [ $1 ];do
	if [ -f $1 ];then
		occurences=`cat $1 | grep -c "\<$2\>"`
		if [ $occurences -ge 3 ];then
			echo "$1 contains at least 3 occurences of $2"
		fi
	fi
	shift
	shift
done
	
