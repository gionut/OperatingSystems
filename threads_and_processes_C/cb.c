#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
		int f;
			mkfifo("fifocarina", 0666);
				f = open("fifocarina", O_RDONLY);
					int nr = 0;
						read(f, &nr, sizeof(int));
							close(f);
								printf("The sum is %d\n", nr);
									return 0;
}
