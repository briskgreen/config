#ifndef _MYSOCK_H
#define _MYSOCK_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifdef _WIN32_NT
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#endif
#define error_continue(msg)\
{\
	perror(msg);\
	continue;\
}
void error_quit(const char *msg);
void init_data_with_server(struct sockaddr_in *server_addr,int port);
void init_data_with_client(struct sockaddr_in *client_addr,int port,const char *hostname);
void close_with_safe(int sock);
#endif
