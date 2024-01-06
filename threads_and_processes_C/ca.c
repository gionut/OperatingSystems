#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
int main(int argc, char** argv)
{
	int p[2];
	pipe(p);
	mkfifo("fifocarina", 0666);
	if (fork() == 0)
	{											close(p[0]);
												int n, nr;
												scanf("%d", &n);
												printf("%d\n", n);
												write(p[1], &n, sizeof(int));
												for (int i = 0; i < n; i++)
		{
			scanf("%d", &nr);
			write(p[1], &nr, sizeof(int));
		}
	close(p[1]);
	exit(0);
}
	else
	{												if (fork() == 0)
													{
													close(p[1]);
			int n, nr;
			int sum = 0;
			read(p[0], &n, sizeof(int));
			for (int i = 0; i < n; i++)
			{
				read(p[0], &nr, sizeof(int));
				sum += nr;
			}
													printf("aicia la suma %d\n", sum);
		close(p[0]);
		int f = open("fifocarina", O_WRONLY);
		write(f, &sum, sizeof(int));
		close(f);
		exit(0);
												}
												else
											{
																						close(p[0]);
																									close(p[1]);
																												wait(0);
																															wait(0);
																																	}
																}
									return 0;
}
