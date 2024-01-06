#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int p[2], n;
	pipe(p);
	mkfifo("/tmp/fifo1", 0666);
	int pid = fork();
	if( pid == 0 )
	{
		close(p[1]);
		
		int m, sum = 0;
		
		read(p[0], &n, sizeof(int));
		
		for(int i = 0; i < n; i++)
		{
			read(p[0], &m, sizeof(int));
			sum += m;
		}
		
		close(p[0]);

		int fd = open("/tmp/fifo1", O_WRONLY);
		write(fd, &sum, sizeof(int));
		close(fd);	
		
		exit(0);
	}

	int pid2 = fork();
	if( pid2 == 0 )
	{
		close(p[0]);
		
		printf("n=");
		scanf("%d", &n);
		
		
		write(p[1], &n, sizeof(int));
		
		int m;
		for(int i = 0; i < n; i++)
		{
			printf("p2: m%d=", i);
			scanf("%d", &m);
			write(p[1], &m, sizeof(int));
		}
		
		close(p[1]);
		exit(0);
	}
	
	close(p[0]);
	close(p[1]);
	
	wait(0);
	wait(0);
	
	printf("parent: Terminated...");
	
	return 0;
}
