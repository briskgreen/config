#include "mysock.h"
void error_quit(const char *msg)
{
	perror(msg);
	exit(1);
}
void init_data_with_server(struct sockaddr_in *server_addr,int port)
{
	memset(server_addr,0,sizeof(struct sockaddr_in));
	server_addr->sin_family=AF_INET;
	server_addr->sin_port=htons(port);
	server_addr->sin_addr.s_addr=INADDR_ANY;
}
void init_data_with_client(struct sockaddr_in *client_addr,int port,const char *host)
{
	memset(client_addr,0,sizeof(struct sockaddr_in));
	client_addr->sin_family=AF_INET;
	client_addr->sin_port=htons(port);
	client_addr->sin_addr.s_addr=inet_addr(host);
}
void close_with_safe(int sock)
{
	shutdown(sock,SHUT_RDWR);
	close(sock);
}
