BEGIN { sum=0 count=0 }

sum+=$2
count++

END { print sum/count }
