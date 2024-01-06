#include <stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h> 
int main()
{
	mkfifo("/tmp/fifop", 0666);
	int fd = open("/tmp/fifop", O_RDONLY);
	int noLetters;
	read(fd, &noLetters, sizeof(int));
	printf("Am Primit de la programul A: %d\n", noLetters);
	close(fd);
	return 0;
}
