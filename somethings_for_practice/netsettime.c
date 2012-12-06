#include "mysock.h"
#include <time.h>
time_t string_to_uint(char *buf)
{
	int i;
	int len=strlen(buf);
	time_t t=0;
	/*while(buf[i])
		i++;
	i++;
	while(i)
	{
		t*=10;
		t+=buf[i--]-'0';
	}*/
	for(i=0;i<len;i++)
	{
		t*=10;
		t+=buf[i]-'0';
	}
	return t;
}
void set_local_time(char *buf)
{
	time_t t;
	t=string_to_uint(buf);
	//printf("I get %s %d\n",buf,strlen(buf));
	//printf("%u\n",(unsigned)t);
	stime(&t);
	printf("%s\n",ctime(&t));
	printf("Set Time Successed. . .\n");
}
int main(int argc,char **argv)
{
	int sock_fd;
	struct sockaddr_in client_addr;
	char buf[20];
	if(argc!=3)
		error_quit("Argument");
	if((sock_fd=socket(AF_INET,SOCK_STREAM,0))==-1)
		error_quit("socket");
	init_data_with_client(&client_addr,atoi(argv[2]),argv[1]);
	if(connect(sock_fd,(struct sockaddr *)&client_addr,sizeof(struct sockaddr))==-1)
		error_quit("connect");
	if(recv(sock_fd,buf,sizeof(buf),0)>0)
		set_local_time(buf);
	else
		printf("Recv Error!\n");
	printf("Close With %s. . .\n",argv[1]);
	close_with_safe(sock_fd);
	return 0;
}
