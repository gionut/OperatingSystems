#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>

typedef struct{
	char* fn;
}Pair;

void* a(void* arg)
{
	Pair* pair =  (Pair*)arg;
	
	int x;
	int f[10];
	FILE* fd = fopen(pair->fn, "r");
	while(fscanf(fd, "%d", &x) != EOF)
	{
		while(x != 0)
		{
			f[x%10]++;
			x/=10;
		}
	}

	int i;
	for(i = 1; i <= 9; i+=2)
		printf("%s : %d -> %d\n", pair->fn, i, f[i]);

	return 0;
}

int main(int argc, char** argv)
{
	pthread_t* p = malloc((argc-1)*sizeof(pthread_t));
	Pair* pairs = malloc((argc-1)*sizeof(Pair));

	int i;
	for(i = 0; i < (argc-1); i++)
	{
			pairs[i].fn = argv[i+1];
			pthread_create(&p[i], 0, a, (void*)&pairs[i]);
	}

	for(i = 0; i < argc-1; i++)
		pthread_join(p[i], 0);

	free(p);
	free(pairs);

	return 0;
}
