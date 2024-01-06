#Sort all files given as command line arguments descending by size.

#!/bin/bash

echo "SIZES">size.txt

while [ $1 ];do
	size=`wc -c "$1"`
	echo $size>>size.txt
	shift
done

sizes=`cat size.txt | tail -n+2 | sort -n -r`

echo "$sizes"


