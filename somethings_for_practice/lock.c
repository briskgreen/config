#include <stdio.h>
#include <string.h>
#include <pthread.h>
typedef struct 
{
	const char *file_name;
	pthread_mutex_t mutex;
}ARG;
void write_to_file(ARG *arg)
{
	FILE *fp;
	const char *buf="Hello! If You See It That mean I'm Successed!\n";
	pthread_mutex_lock(&arg->mutex);
	//printf("This is write.. .\n");
	if((fp=fopen(arg->file_name,"wb"))==NULL)
	{
		pthread_mutex_unlock(&arg->mutex);
		pthread_exit(NULL);
	}
	//printf("Plesae Input Somethings:");
	//scanf("%d\n",buf);
	fwrite(buf,strlen(buf)+1,1,fp);
	fclose(fp);
	pthread_mutex_unlock(&arg->mutex);
	pthread_exit(NULL);
}
void read_from_file(ARG *arg)
{
	FILE *fp;
	char buf;
	pthread_mutex_lock(&arg->mutex);
	//printf("This is Read. . .\n");
	if((fp=fopen(arg->file_name,"rb"))==NULL)
	{
		pthread_mutex_unlock(&arg->mutex);
		pthread_exit(NULL);
	}
	while(!feof(fp))
	{
		fread(&buf,sizeof(char),1,fp);
		printf("%c",buf);
	}
	fclose(fp);
	pthread_mutex_unlock(&arg->mutex);
	pthread_exit(NULL);
}
int main(void)
{
	pthread_t read,write;
	ARG arg;
	const char *file_name="lock.txt";
	arg.file_name=file_name;
	//printf("OK\n");
	pthread_mutex_init(&arg.mutex,NULL);
	//printf("ok\n");
	pthread_create(&write,NULL,(void *)write_to_file,&arg);
	pthread_create(&read,NULL,(void *)read_from_file,&arg);
	pthread_join(read,NULL);
	pthread_join(write,NULL);
	pthread_mutex_destroy(&arg.mutex);
	return 0;
}
