#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>                                                                                                 
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	mkfifo("/tmp/fifo1", 0666);
	int fd = open("/tmp/fifo1", O_RDONLY);

	int sum;

	read(fd, &sum, sizeof(int));

	printf("The sum is: %d\n", sum);

	close(fd);

	return 0;
}
