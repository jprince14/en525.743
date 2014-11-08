#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <liquid/liquid.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct command {
	unsigned char cmd;
	unsigned int param;
}__attribute__((packed));

struct tcp_socket {
	struct sockaddr_in servaddr;
	int sockfd;
	bool receiverexitflag;

};

void tcp_setaddress(struct tcp_socket, char*);
void tcp_setport(struct tcp_socket, int);

void tcp_createsocket(struct tcp_socket);
bool tcp_opensocket(struct tcp_socket);

int receive(uint8_t*, int, char*);
void closesocket(struct tcp_socket);

void set_freq(struct tcp_socket, int);
void set_sample_rate(struct tcp_socket, int);
