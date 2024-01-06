#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>

void* f(void* a)
{
	char *** args = (char***)a;
	printf("%s", args[0][0]);
	return 0;
}

int main(int argc, char** argv)
{
	pthread_t* p = malloc((argc-1)*sizeof(pthread_t));

	int i;
	char* v[100][2];
	for(i = 0; i < argc -1; i+=2)
	{
		v[i][i] = argv[i+1];
		v[i][i+1] = argv[i+2];
		pthread_create(&p[i], 0, f, (void**)v[i]);
	}

	for(i = 0; i < argc-1; i+=2)
		pthread_join(p[i], 0);

	free(p);
	return 0;
}
