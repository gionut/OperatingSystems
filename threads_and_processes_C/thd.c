#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>

pthread_mutex_t m;

int SUM = 0;

typedef struct
{
	int n;
	char* fn;
}Pair;

void* a(void* arg)
{
	Pair* pair = (Pair*)arg;

	FILE* fd = fopen(pair->fn, "r");

	int count =0;
	int nr;
	while(fscanf(fd, "%d", &nr)!=EOF && count < pair->n)
	{
		pthread_mutex_lock(&m);
		SUM+=nr;
		pthread_mutex_unlock(&m);
		count++;
	}
	fclose(fd);
	free(pair);
	return 0;
}

int main(int argc, char** argv)
{
	pthread_t* p = malloc((argc-1)/2*sizeof(pthread_t));
	pthread_mutex_init(&m, 0);
	
	int i = 0;
	int j = 0;
	for(i = 0; i < argc-1; i+=2)
	{
		Pair* pair = malloc(sizeof(Pair));
		pair->n = atoi(argv[i+2]);
		pair->fn = argv[i+1];
		pthread_create(&p[j], 0, a, (void*)pair);
		j++;
	}

	for( i= 0; i < (argc-1)/2; i++)
		pthread_join(p[i], 0);

	pthread_mutex_destroy(&m);
	
	printf("%d\n", SUM);
	free(p);
	return 0;
}
