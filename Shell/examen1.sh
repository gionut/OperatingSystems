#!/bin/bash

if [ $# -lt 2 ]; then
	echo $'Numar insuficient de argumente!\nUtilizare: ./examen.sh rw- dir1_ dir_2 ...'
	exit 1
fi

drepturi=$1

shift
while [ $1 ];do
	if [ ! -e $1 ];then
		echo "Director: $1"
		echo "Directorul dat nu exista."
	else
		for FILE in `find $1 -type f`;do
			drepturiFisier=`ls -l $FILE | cut -d" " -f1`
			if [[ $drepturiFisier = *"$drepturi"* ]] ;then
				cat $FILE>$FILE.bak
				chmod 200 $FILE
				echo "Director $1"
				echo "Fisier: $FILE"
				echo "Permisiuni: $drepturiFisier"
				echo "Copie: $FILE.bak"
				echo "Permisiuni: -r-------"
			fi
		done
	fi
	shift
done


