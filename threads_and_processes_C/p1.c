#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	for(int i = 0; i < 3; i++)
	{
		printf("i=%d ppid=%d pid=%d\n", i, getppid(), getpid());
		if(fork() == 0)
		{
			for(int j = 0; j < 3; j++)
				if(fork() == 0)
				{
					printf("i=%d j=%d ppid=%d pid=%d\n",i, j ,getppid(), getpid());
					exit(0);
				}
			for(int j = 0; j < 3; j++)
			      wait(0);
			exit(0);	
				
		}
	}
	for(int i = 0; i <3; i++)
		wait(0);
		
	return 0;
}
