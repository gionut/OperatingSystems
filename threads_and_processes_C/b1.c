#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>
#include<string.h>

pthread_mutex_t* m;
pthread_cond_t* c;

typedef struct
{
	int j;
	int x;
	char* fn;
	char chr;
}Pair;

void* a(void* arg)
{
	Pair* pair = (Pair*)arg;
	int n;
	FILE* fd = fopen(pair->fn, "r");
	fscanf(fd, "%d", &n);

	char character;
	while(fscanf(fd, "%c", &character) != EOF)
	{
		if(strchr("aeiou", character) != NULL)
		{

			pair->x++;
					
			if(pair->x == n)
			{
				pair->chr = character;
			       	pthread_mutex_lock(&m[pair->j]);
				printf("A: I caught the mutex!\n");
				pthread_cond_signal(&c[pair->j]);
				printf("A: sending the signal!\n");
				pthread_mutex_unlock(&m[pair->j]);
				printf("A: Being nice and unlock the mutex!\n");
				printf("notify! %d\n", n);
			}
		}
	}
	if(n > pair->x)
	{
		pthread_mutex_lock(&m[pair->j]);
		pthread_cond_signal(&c[pair->j]);
		pthread_mutex_unlock(&m[pair->j]);
	}
	fclose(fd);
	printf("A: finnishing...\n");
	return 0;
}

void* b(void* arg)
{
	Pair* pair = (Pair*)arg;
	FILE* fd = fopen(pair->fn, "r");
	int n;
	fscanf(fd, "%d", &n);
	pthread_mutex_lock(&m[pair->j]);
	printf("B: getting the mutex!\n");
	while(pair->x <= n)
	{	
		printf("B: unlocking the mutex and wait for signal!\n");
		pthread_cond_wait(&c[pair->j], &m[pair->j]);
		printf("B: got the signal and lock the mutex!\n");
	}
	if( n > pair->x)
		printf("There are less then %d vowels in file %s (only %d)\n", n, pair->fn, pair->x);
	else
		printf("%d -> %c\n", pair->x, pair->chr);
	pthread_mutex_unlock(&m[pair->j]);
	printf("B: being nice and unlocking the mutex again!\n");
	printf("B: finnishing...\n");
	return 0;
}

int main(int argc, char** argv)
{
	pthread_t* p = (pthread_t*)malloc(2*(argc-1)*sizeof(pthread_t));
	m = (pthread_mutex_t*)malloc((argc-1)*sizeof(pthread_mutex_t));
	c = (pthread_cond_t*)malloc((argc-1)*sizeof(pthread_cond_t));

	Pair** pairs = (Pair**)malloc((argc-1)*sizeof(Pair*));
	
	for(int i = 0; i < argc-1; i++)
	{	
		pthread_mutex_init(&m[i], 0);
		pthread_cond_init(&c[i], 0);
	}
	int j = 1;
	for(int i = 0; i < 2*(argc-1); i+=2)
	{
		pairs[j] = (Pair*)malloc(sizeof(Pair*));
		pairs[j]->fn = argv[j];
		pairs[j]->x = 0;
		pairs[j]->j = j;
		pthread_create(&p[i], 0, a, (void*)pairs[j]);
		pthread_create(&p[i+1], 0, b, (void*)pairs[j]);
		j++;
	}

	for(int i = 0; i < 2*(argc - 1); i+=2)
		pthread_join(p[i], 0);
	
	for(int i = 0; i < argc - 1; i++)
	{
		pthread_mutex_destroy(&m[i]);
		pthread_cond_destroy(&c[i]);
	}

	free(p);
//	for(int i = 0; i < argc-1; i++)
//		free(pairs[i]);
	free(m);
	free(c);
	free(pairs);
	return 0;
}
