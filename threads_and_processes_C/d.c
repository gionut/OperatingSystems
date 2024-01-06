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
	mkfifo("fifo", 0666);
	if(fork() == 0)
	{
		close(p[0]);
		char path[100];
		int n;
		scanf("%s", path);
		n = strlen(path);
		write(p[1], &n, sizeof(int));
		write(p[1], path, (n+1)*sizeof(char));
		close(p[0]); 
		exit(0);
	}
	if(fork() == 0)
	{
		close(p[1]);
		char path[100];
		int n;
		read(p[0], &n, sizeof(int));
		read(p[0], path, (n+1)*sizeof(char));
		printf("%d %s", n, path);
		close(p[0]);

		int f[10];                                          
		int i;
		for(i = 1; i <= 9; i+=2)
	                f[i] = 0;

               	FILE* fn = fopen(path, "r");
		int number;
		while(fscanf(fn, "%d", &number) != EOF)
               	{
			while(number != 0) 
			{
                        	f[number%10]++;
	                        number/=10;
                        }
               	}

              	int fd = open("fifo", O_WRONLY);
                for(i = 1; i <= 9; i+=2)
			write(fd, &f[i], sizeof(int));
		
		close(fd);
		exit(0);
	}
	close(p[0]); close(p[1]);
	wait(0);
	wait(0);
	return 0;
}

