#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
	mkfifo("fifo", 0666);

	int fd = open("fifo", O_RDONLY);
	int i;
	int frequency;
	for(i = 1; i <=9; i++)
	{	
		read(fd, &frequency, sizeof(int));
		printf("%d -> %d\n", i, frequency);
	}
	close(fd);	
	return 0;
}
