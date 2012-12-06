#include "mysock.h"
#include <time.h>
#include <pthread.h>
int get_num_len(time_t t)
{
	int i=1;
	while(t>10)
	{
		t/=10;
		i++;
	}
	return i;
}
char *uint_to_string(time_t t)
{
	char *buf;
	int len;
	len=get_num_len(t);
	buf=malloc(sizeof(len));
	buf[len]='\0';
	while(len)
	{
		buf[--len]=t%10+'0';
		t/=10;
	}
	return buf;
}
void send_time(int *client_fd)
{
	time_t t;
	char *buf;
	t=time(NULL);
	buf=uint_to_string(t);
	if(send(*client_fd,buf,strlen(buf)+1,0)>0)
		printf("Send %s Successed!\n",buf);
	else
		printf("Send Error!\n");
	free(buf);
	printf("Close Now. . .\n");
	close_with_safe(*client_fd);
	pthread_exit(NULL);
}
int main(int argc,char **argv)
{
	int sock_fd,client_fd;
	int sin=sizeof(struct sockaddr);
	struct sockaddr_in server_addr,client_addr;
	if(argc!=2)
		error_quit("Argument!");
	if((sock_fd=socket(AF_INET,SOCK_STREAM,0))==-1)
		error_quit("socket");
	init_data_with_server(&server_addr,atoi(argv[1]));
	if(bind(sock_fd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1)
		error_quit("bind");
	if(listen(sock_fd,10)==-1)
		error_quit("listen");
	while(1)
	{
		if((client_fd=accept(sock_fd,(struct sockaddr *)&client_addr,&sin))==-1)
			error_continue("accept");
		printf("Connect With %s Now\n",inet_ntoa(client_addr.sin_addr));
		pthread_t thread;
		pthread_create(&thread,NULL,(void *)send_time,&client_fd);
		pthread_detach(thread);
	}
	close_with_safe(sock_fd);
	return 0;

}
