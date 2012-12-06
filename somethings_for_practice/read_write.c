#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
typedef struct
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int val[100];
}THREAD;
void read_data(THREAD *val)
{
	int i;
	pthread_mutex_lock(&val->mutex);
	while(val->val[0]==0)
		pthread_cond_wait(&val->cond,&val->mutex);
	printf("Read Now . . .\n\n\t\t");
	for(i=0;i<100;i++)
	{
		printf("%5d",val->val[i]);
		if((i+1)%10==0)
			printf("\n\t\t");
	}
	pthread_mutex_unlock(&val->mutex);
	printf("\nRead OK. . .\n");
	pthread_exit(NULL);
}
void write_data(THREAD *val)
{
	pthread_mutex_lock(&val->mutex);
	int i;
	printf("Write Now . . .\n\n");
	srand(time(NULL));
	for(i=0;i<100;i++)
		val->val[i]=rand()%100+1;
	printf("Write OK . . .\n\n");
	pthread_cond_signal(&val->cond);
	pthread_mutex_unlock(&val->mutex);
	pthread_exit(NULL);
}
int main(int argc,char **argv)
{
	pthread_t write;
	pthread_t read;
	THREAD val;
	pthread_mutex_init(&val.mutex,NULL);
	pthread_cond_init(&val.cond,NULL);
	memset(val.val,0,sizeof(val.val));
	pthread_create(&read,NULL,(void *)read_data,&val);
	sleep(3);
	pthread_create(&write,NULL,(void *)write_data,&val);
	pthread_join(read,NULL);
	pthread_join(write,NULL);
	pthread_mutex_destroy(&val.mutex);
	pthread_cond_destroy(&val.cond);
	return 0;
}
