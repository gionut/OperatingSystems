BEGIN{
	sum=0
}
{
	sum += $3
}
END{
	print sum
}
