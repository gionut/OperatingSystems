#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>

int f[10];// define global variable
pthread_mutex_t m[10];// define mutexes

void* fnc(void* a)
{
	char* filename = (char*)a;
	int fd = open(filename, O_RDONLY);
	int digit;
	 
	char c;
	while(read(fd, &c, sizeof(char)))
	{
		digit = c - '0';
		if(digit >= 0 && digit <=9)
		{
			pthread_mutex_lock(&m[digit]);
			f[digit]++;
			pthread_mutex_unlock(&m[digit]);
		}
	}

	close(fd);
	return 0;
}

int main(int argc, char** argv)
{
	pthread_t* p; // define thread
	p = malloc((argc-1)*sizeof(pthread_t));// initialize thread

	int i;
	for(i = 0; i < argc - 1; i++)
		pthread_mutex_init(&m[i], 0);// initialize mutxes

	for(i = 0; i < argc - 1; i++)
	{
		pthread_create(&p[i], 0, fnc, (void**)argv[i+1]);// create threads
	}

	for(i = 0; i < argc -1; i++)
		pthread_join(p[i], 0); // join threads

	free(p); // free threads

	for(i = 0; i < argc - 1; i++)
		pthread_mutex_destroy(&m[i]); // destroy mutexes

	for(i = 0; i <= 9; i++)
		printf("%d -> %d\n", i, f[i]);

	return 0;
}
