#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>

pthread_mutex_t* m;

void* f(void* a)
{
	int tmp = a;
	int inv = 0;
	while(tmp != 0)
	{
		inv = inv*10 + tmp%10;
		tmp = tmp/10;
	}
	printf("%d -> %d\n", a, inv);
	return 0;
}

int main(int argc, char** argv)
{
	pthread_t *p;
	
	FILE *fd = fopen("b.txt", "r");

	p = malloc((10)*sizeof(pthread_t));
	m = malloc((10)*sizeof(pthread_mutex_t));

	int i;
	for(i = 0; i < 10; i++)
		pthread_mutex_init(&m[i], 0);

	int *number = malloc(10*sizeof(int));
	i = 0;
	while(fscanf(fd, "%d", &number[i]) != EOF)
	{
		pthread_create(&p[i], 0, f, number[i]);
		i++;
	}

	for(i = 0; i < 10; i++)
		pthread_join(p[i], 0);

	free(p);

	for(i = 0; i < 10; i++)
		pthread_mutex_destroy(&m[i]);

	free(m);	
	return 0;
}
