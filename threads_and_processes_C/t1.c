#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>

pthread_mutex_t m;

int n = 0;

void* f1(void *a)
{
	
	int nr = 1;
	for(int i = 2; i < a; i++)
	       nr*=i;	
	printf("%d! = %d\n",a, nr); 
	return 0;
}
void* f(void* a)
{
	FILE *fd;
	char* filename = (char*)a;
	fd = fopen(filename, "r");
	int noNumbers = 0;
	int number;
	while(fscanf(fd, "%d", &number) != EOF)
  	{    
		noNumbers++;
	}

	fd = fopen(filename, "r");
	
	pthread_t *p1;
	pthread_mutex_t *m1;
	
	p1 = malloc(noNumbers*sizeof(pthread_t));
	m1 = malloc(noNumbers*sizeof(pthread_mutex_t));
	int i;
	for(i = 0; i < noNumbers; i++)
		pthread_mutex_init(&m1[i], 0);

	int* numbers;
	numbers = malloc(noNumbers*sizeof(int));
	i = 0;
	while(fscanf(fd, "%d", &numbers[i]) != EOF)
	{
		if(numbers[i] % 4 == 0)
		{
			pthread_mutex_lock(&m);
			n+=numbers[i];
			pthread_mutex_unlock(&m);
		}
		pthread_create(&p1[i], 0, f1, numbers[i]);
		i++;
	}
	
	for(i = 0; i < noNumbers; i++)
		pthread_join(p1[i], 0);
	
	free(p1);
	free(numbers);

	for(i = 0; i < noNumbers; i++)
		pthread_mutex_destroy(&m1[i]);

	free(m1);
	return 0;
}

int main(int argc, char**argv)
{
	pthread_t *p;
	p = malloc((argc-1)*sizeof(pthread_t));
	
	pthread_mutex_init(&m, 0);

	for(int i = 0; i < argc-1; i++)
	{
		pthread_create(&p[i], NULL, f, (void**)argv[i+1]);
	}

	for(int i = 0; i < argc -1; i++)
	{
		pthread_join(p[i], 0);
	}

	free(p);

	pthread_mutex_destroy(&m);

	printf("%d\n", n);

	return 0;
}
