#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int p[2];
	pipe(p);
	mkfifo("/tmp/fifop", 0666);
	
	if(fork() == 0)
	{
		close(p[0]);
		int n;
		char s[100];

		fgets(s, sizeof(s), stdin);
		n = strlen(s);
		printf("Trimit din P1: %s, cu lungimea %d\n", s, n-1);
		write(p[1], &n, sizeof(int));
		write(p[1], s, n);
		close(p[1]);
		exit(0);
	}
	if(fork() == 0)
	{
		close(p[1]);
		int n;
		char s[100];

		read(p[0], &n, sizeof(int));
		read(p[0], s, n);
		close(p[0]);
		printf("Am primit in P2: %s, cu lungimea %d\n", s, n-1);
		
		int noLetters = 0;
		for(int i = 0; i < n; i++)
			if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
				noLetters++;
		
		printf("Trimit la programul b: %d\n", noLetters);
		int fd = open("/tmp/fifop", O_WRONLY);
		write(fd, &noLetters, sizeof(int)); 
		close(fd);
		exit(0);
	}
	wait(0);
	wait(0);
	printf("Parent process terminated!\n");
	return 0;
}
