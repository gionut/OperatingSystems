#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>

pthread_mutex_t m, s;
int minSum = 0;

void* f(void* a)
{
	int* array = (int*)a;
	int sum = 0;
	pthread_mutex_lock(&m);
		if(array[0] % 7 == 0 && array[1] % 7 == 0)
			sum = array[0] + array[1];
	pthread_mutex_unlock(&m);
	
	if(sum != 0)
	{
		printf("%d\n", sum);
		pthread_mutex_lock(&s);
			if(sum < minSum)
				minSum = sum;
		pthread_mutex_unlock(&s);
	}
	return 0;
}

int main(int argc, char** argv)
{
	char* fn = argv[1];
	FILE *fd = fopen(fn, "r");

	pthread_t p[1000];
	pthread_mutex_init(&m, 0);
	pthread_mutex_init(&s, 0);
	int a[2];
	int i;

	for(i = 0; i < 1000; i++)
	{
		fscanf(fd, "%d", &a[0]);
		fscanf(fd, "%d", &a[1]);
		pthread_create(&p[i], 0, f, (void*)a);
	}

	for(i = 0; i < 1000; i++)
		pthread_join(p[i], 0);
	printf("%d", minSum);
	pthread_mutex_destroy(&m);
	pthread_mutex_destroy(&s);	
	return 0;
}
