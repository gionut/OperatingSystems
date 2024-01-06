#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int p[2];
	pipe(p);
	mkfifo("/tmp/fifo2", 0666);
	if(fork() == 0)
	{
		close(p[0]);

		char s[100];
		int n;
		printf("s=");
		scanf("%s", s);
		n = strlen(s);

		printf("you have written: %s\n", s);
		write(p[1], &n, sizeof(int));
		write(p[1], &s, (n+1)*sizeof(char));
		
		close(p[1]);
		exit(0);
	}
	if(fork() == 0)
	{
		close(p[1]);

		char s[100];
		int n;

		read(p[0], &n, sizeof(int));
		read(p[0], &s, (n+1)*sizeof(char));
		close(p[0]);
		printf("I have recieved %d characters: %s \n", n, s);
		printf("here");
		int noLetters = 0;
		for(int i = 0; i < n; i++)
			if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
				noLetters++;
		
		printf("I send: %d", noLetters);
		int fd = open("/tmp/fifo2", O_WRONLY);
		write(fd, &noLetters, sizeof(int));
		close(fd);
		exit(0);
	}
	wait(0);
	wait(0);
	printf("Process A terminating...");

	return 0;
}
