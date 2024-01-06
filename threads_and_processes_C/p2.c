#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
	int p[2];
	int n;
	scanf("n=%d", &n);
	int* a = malloc(n*sizeof(int));
	pipe(p);
	for(int i = 0; i < n; i+=4)
	{
		a[i] += a[i+1];
		if(fork() == 0)
		{
			close(p[0]);
			a[i+2] += a[i+3];
			write(p[1], &a[i+2], sizeof(int));
			close(p[1]);
			exit(0);
		}
		close(p[1]);
		read(p[0], &a[i+2], sizeof(int));
		close(p[0]);
	}
	for(int i = 0; i<n; i+=2)
		wait(0);
	return 0;
}
