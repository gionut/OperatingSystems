#!/bin/bash

D=$1
if [ ! -d "$D" ]; then
	exit 1
fi

MAX_DIR_NAME=""
MAX_FILE_NAME=""
MAX_DIR_LEN=0
MAX_FILE_LEN=0

for F in $D/*; do
       if [ -f $F ]; then
	       if [ `expr length $F` -gt $MAX_FILE_LEN ];then
		       MAX_FILE_LEN=`expr length $F`
		       MAX_FILE_NAME="$F"
	       fi
       
       elif [ -d $F ];then
	       if [ `expr length $F` -gt $MAX_DIR_LEN ];then
		       MAX_DIR_LEN=`expr length $F`
		       MAX_DIR_NAME="$F"
	       fi
       fi
done       

echo "File with longest name: $MAX_FILE_NAME"
echo "Directory with longest name: $MAX_DIR_NAME"


