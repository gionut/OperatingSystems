#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>

int* a;
pthread_mutex_t* m;

void* f(void* arg)
{
	int i;
	for(i = 0; i < 100; i++) 
	{
		int nr = rand()%100;
		pthread_mutex_lock(&m[nr%10]);
		a[nr%10] += nr;
		pthread_mutex_unlock(&m[nr%10]);
	}
	return 0;
}

int main()
{
	
	pthread_t p[7];
	int i = 0;
	a = (int*)malloc(10*sizeof(int));
	m = (pthread_mutex_t*)malloc(10*sizeof(pthread_mutex_t));
	for(i = 0; i < 10; i++)
		a[i] = 0;
	for(i = 0; i < 10; i++)
		pthread_mutex_init(&m[i], 0);

	for(i = 0; i < 7; i++)
	{
		pthread_create(&p[i], 0, f, NULL);
	}
	for(i = 0; i < 7; i++)
		pthread_join(p[i], 0);
	for(i = 0; i < 10; i++)
		pthread_mutex_destroy(&m[i]);

	for(i = 0; i < 10; i++)
		printf("%d -> %d\n", i, a[i]);
	return 0;
}
	

