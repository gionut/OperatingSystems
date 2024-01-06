#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>

typedef struct
{
	int n;
	char* fn;
}Pair;

void* a (void* arg)
{
	Pair* pair = (Pair*)arg;
	printf("%s -> %d\n", pair->fn, pair->n);
	return 0;
}

int main(int argc, char** argv)
{
	pthread_t* p = malloc((argc-1)*sizeof(pthread_t));
	Pair* pairs = malloc((argc-1)*sizeof(Pair));
	int i, j = 0;
	for(i = 0; i < 2*(argc - 1); i+=2)
	{
		//char c = argv[i+2][0];
		pairs[j].n = atoi(argv[i+2]) - '0';
		pairs[j].fn = argv[i+1];
		pthread_create(&p[j], 0, a, (void*)&pairs[j]);
	}

	for(i  = 0; i < argc-1; i++)
		pthread_join(p[i], 0);

	free(p);
	free(pairs);

	return 0;
}
