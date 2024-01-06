#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
pthread_t th[7];
int sum[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int** nrSum;
int nrSumSize[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
pthread_mutex_t m[11];
int nrGen = 0;
void* generate(void* a)
{
	while(1)
	{
		pthread_mutex_lock(&m[10]);
	   	if(nrGen == 5)
		{
		        pthread_mutex_unlock(&m[10]);
	     		return NULL;
		}
	       	int nr = rand()%100;
		if(nr%10 == 5)
				nrGen++;
			 pthread_mutex_unlock(&m[10]);
			     int r = nr%10;
			       pthread_mutex_lock(&m[r]);
			         sum[r] += nr;
				   int* vct= (int*)malloc(sizeof(int)*(nrSumSize[r]+1));
				     for(int i=0; i<nrSumSize[r]; i++)
					         vct[i] = nrSum[r][i];
				       vct[nrSumSize[r]] = nr;
				         free(nrSum[r]);
					   nrSum[r] = vct;
					     nrSumSize[r]++;
					       pthread_mutex_unlock(&m[r]);
					        }
	   return NULL;
}
int main(int argc, char** argv)
{
	  srand(time(NULL));
	    nrSum = (int**)malloc(sizeof(int*)*10);
	      int i;
	        for(i=0; i<11; i++)
			    pthread_mutex_init(&m[i], NULL);
		  for(i=0; i<7; i++)
			      pthread_create(&th[i], NULL, generate, NULL);
		    for(i=0; i<7; i++)
			        pthread_join(th[i], NULL);
		      for(i=0; i<11; i++)
			          pthread_mutex_destroy(&m[i]);
		        for(i=0; i<10; i++){
				    printf("sum[%d] = ", i);
				        for(int j=0; j<nrSumSize[i]; j++){
						      if(j == nrSumSize[i]-1)
							              printf("%d = ", nrSum[i][j]);
						           else
								           printf("%d + ", nrSum[i][j]);
							       }
					    printf("%d\n", sum[i]);
					        free(nrSum[i]);
						  }
			  free(nrSum);
			    return 0;
}

