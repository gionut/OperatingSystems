#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
	int p[2], i = 0;
	char c, s[20];

	pipe(p);

	if(fork() == 0)
	{
		close(p[1]);
		while( read(p[0], &c, sizeof(char)) )
		{
			
			if( i < 5 || i > 8 )
			{
				printf("%c", c);
			}
			i++;
		}
		close(p[0]);
		printf("\n");
		exit(0);
	}
	
	close(p[0]);
	printf("Result: \n");
	strcpy(s, "exam not passed!");
	write(p[1], s, strlen(s)*sizeof(char));
	close(p[1]);
	wait(0);
	return 0;
}

