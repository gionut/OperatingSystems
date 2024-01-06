#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>

pthread_mutex_t es;
pthread_mutex_t no; 
pthread_mutex_t os;

int EvenSum = 0;
int OddSum = 0;
int NoNo = 0;

typedef struct
{
	char* x;
       	char* y;
}Pair;

void* a(void* arg)
{
	Pair* pair = (Pair*)arg;
	
	int n1 = atoi(pair->x);
	int n2 = atoi(pair->y);
	
	if(n1 == 0 || n2 == 0)
	{
		pthread_mutex_lock(&no);
		NoNo++;
		pthread_mutex_unlock(&no);
		return 0;
	}	
	else if((n1+n2)%2 == 0)
	{
		pthread_mutex_lock(&es);
		EvenSum++;
		pthread_mutex_unlock(&es);
		return 0;
	}
	else
	{
		pthread_mutex_lock(&os);
		OddSum++;
		pthread_mutex_unlock(&os);
		return 0;
	}	
	return 0;
}

int main( int argc, char** argv)
{
	pthread_t* p = malloc((argc-1)/2*sizeof(pthread_t));
	Pair* pairs = malloc((argc-1)/2*sizeof(Pair));

	pthread_mutex_init(&es, 0);
	pthread_mutex_init(&no, 0);
	pthread_mutex_init(&os, 0);

	int i;
	int j = 0;
	for(i = 0; i < (argc-1); i+=2)
	{
		pairs[j].x = argv[i+1];
		pairs[j].y = argv[i+2];
		pthread_create(&p[j], 0, a, (void*)&pairs[j]);
	 	j++;
	}
	
	for(i = 0; i < (argc-1)/2; i++)
		pthread_join(p[i], 0);

	pthread_mutex_destroy(&es);
	pthread_mutex_destroy(&no);
	pthread_mutex_destroy(&os);
	
	printf("Non-numerical pairs: %d\n", NoNo);
	printf("Even sum: %d\n", EvenSum);
	printf("Odd sum: %d\n", OddSum);

	free(p);
	free(pairs);

	return 0;
}
