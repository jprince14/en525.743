#ifndef UDPSOCKET_H
#define UDPSOCKET_H


#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <liquid/liquid.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct udp_socket {
	struct sockaddr_in servaddr;
	int sockfd;
};


void udp_setaddress(struct udp_socket* inputsocket, char* inputstring);
void udp_setport(struct udp_socket* inputsocket, int port);
void udp_createsocket(struct udp_socket* inputsocket);
int udp_opensocket(struct udp_socket* inputsocket);
void udp_senddata(struct udp_socket* inputsocket);
void udp_receive(struct udp_socket* inputsocket);
void closeudpsocket(struct udp_socket* inputsocket);



#endif
