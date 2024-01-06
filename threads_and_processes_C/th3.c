#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>

pthread_t p[7];

int SUM[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int places = 5;
int nrSUM[10][100];

void*a (void* arg)
{
	while(1)
	{
		int nr = rand()%100;
		int n = nr%10;
		if( n == 5)
		{
			places--;
		}

		int firstEmpty = nrSUM[n][0];// get the last free position in the specific array of numbers
		if(firstEmpty >= 100)
			break;
		printf("%d -> %d\n", n, nr);
		SUM[n]+=nr;// add to the SUM
		nrSUM[n][firstEmpty] = nr;// insert the number on the free position
	       	nrSUM[n][0]++;// go to the next empty position in the array

		if(!places)
		{
			break;
		}
	}
	return 0;
}

int main(int argc, char** argv)
{
	int i;
	for(i = 0; i < 10; i++)
		nrSUM[i][0] = 0;

	for(i = 0; i < 1; i++)
		pthread_create(&p[i], 0, a, 0);

	for(i = 0; i < 1; i++)
		pthread_join(p[i], 0);

	for(i = 0; i < 10; i++)
	{
		printf("SUM[%d]=", i);
		int j;
		for(j = 0; j < nrSUM[i][0]; j++)
			if(nrSUM[i][j]!=0)
				printf("%d+", nrSUM[i][j]);
			else if(j == nrSUM[i][0]-1)
				printf("%d=", nrSUM[i][j]);
		printf("%d\n", SUM[i]);
	}
	return 0;
}
