#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int pfd[2], i, n;
	pipe(pfd);
	for(i=0; i<10000; i++) 
	{
		if(fork() == 0) 
		{
			write(pfd[1], &i, sizeof(int));
			close(pfd[0]); close(pfd[1]);
			exit(0);
		}
	}
	for(i=0; i<1000; i++) {
		wait(0);
		read(pfd[0], &n, sizeof(int));
	 	printf("%d\n", n);
	 }
	 close(pfd[0]); close(pfd[1]);
	 return 0;
}
				
