#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
	int p2c[2], c2p[2];
	pipe(p2c);
	pipe(c2p);
	if( fork() == 0)
	{
		close(c2p[1]);
		close(p2c[0]);
		int n;
		scanf("%d", &n);
		write(p2c[1], &n, sizeof(int));
		while(n >= 1)
		{	
			read(c2p[0], &n, sizeof(int));
			printf("A recieved %d sends %d\n", n, n-3);
			n = n-3;
			write(p2c[1], &n,  sizeof(int));
		}
		close(c2p[0]);
		close(p2c[1]);
		exit(0);
	}
	if(fork() == 0)
	{
		close(p2c[1]);
		close(c2p[0]);
		int n;
		read(p2c[0], &n, sizeof(int));
		while(n >= 1)
		{
			write(c2p[1], &n, sizeof(int));
			printf("B recieved %d sends %d\n", n, n/2);
		       	n = n/2;
			read(p2c[0], &n, sizeof(int));
		}
		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}
	close(p2c[0]); close(p2c[1]);
	close(c2p[0]); close(c2p[1]);
	wait(0);
	wait(0);
	printf("Parent terminating...");
	return 0;
}
