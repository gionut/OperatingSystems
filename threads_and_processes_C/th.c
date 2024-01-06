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
	int fd = open(pair->fn, O_RDONLY);
	
	int count = 0; 
	char c;
	while(count < pair->n && read(fd, &c, 1))
	{
		//printf("%d--%c\n", pair->n, c); 
		count++;
	}
		
	if(count == pair->n)
	{
		printf("The character on position %d in the file %s is %c\n", pair->n, pair->fn, c);
	}
	else
	{
		printf("Error! there are less then %d characters in the file %s (only %d characters)\n", pair->n, pair->fn, count);
	}	
	return 0;
}

int main(int argc, char** argv)
{
	pthread_t* p = malloc((argc-1)/2*sizeof(pthread_t));
	Pair* pairs = malloc((argc-1)/2*sizeof(Pair));
	int i, j = 0;
	for(i = 0; i < (argc - 1); i+=2)
	{
		//pairs[j].n = argv[i+2][0] - '0';
		pairs[j].n = atoi(argv[i+2]);
		pairs[j].fn = argv[i+1];
		pthread_create(&p[j], 0, a, (void*)&pairs[j]);
		j++;
	}

	for(i  = 0; i < (argc-1)/2; i++)
		pthread_join(p[i], 0);

	free(p);
	free(pairs);

	return 0;
}
