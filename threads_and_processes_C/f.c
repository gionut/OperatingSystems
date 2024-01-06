#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

pthread_mutex_t m[10];
void* dostuff(void *arg)
{
	        char *fn = (char *)arg;
		int fd = open (fn, O_RDONLY);
		        char c = 0;
			        printf("\nintrat\n");
				        while (read(fd,&c, 1))
						        {
								 int i = c - '0';
								 pthread_mutex_lock(&m[i]);
								                 f[i]++;
										 pthread_mutex_unlock(&m[i]);
										         }
					        //printf("file = %s\n",fn);
						//        return 0;
						//        }
int main(int argc, char** argv)
{
	        pthread_t *p;
		        p = malloc((argc - 1) * sizeof(pthread_t));
			        int i;
				        for (i =0; i<10;i++)
						        {
								pthread_mutex_init(&m[i],0);
								        }
					        for (i=0; i < argc - 1; i++)
							        {
									                pthread_create(&p[i],0,dostuff,(void **)argv[i+1]);
											        }
}
        for (i=0;i< argc-1; i++)
	        {
			                pthread_join(p[i],0);
					        }
        free(p);
	        for (i =0; i<10;i++)
		        {
				                pthread_mutex_destroy(&m[i]);
						        }
        for (i =0; i<10;i++)
	        {
			                printf("f[%d]=%d\n",i,f[i]);
					        }
        return 0;
	}
