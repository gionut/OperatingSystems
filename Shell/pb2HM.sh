#Write a script that reads filenames until the word "stop" is entered. For each filename, check if it is a text file and if it is, print the number of words on the first line.
#!/bin/bash

while true;do
	read input
       	if [ $input == "stop" ];then
		exit 0
	fi
	if [ -f "$input" ];then
		istext=`file $input | grep -c "text"`
		if [ $istext -eq 1 ];then
			echo `head -n1 $input | wc -w`
		fi
	fi
done	
