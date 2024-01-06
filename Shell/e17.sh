D=$1
if [ ! -d $D ]; then
	echo "You Need to provide a directory as argument"
	exit 1
fi

find $D -type f | while read F; do
	if file $F | grep -q "\<ASCII\>"; then
		echo $F
	fi
done

