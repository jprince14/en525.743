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
	char buffer[1000];
	int receivesize;
};

void tcp_setaddress(struct tcp_socket inputsocket, char* inputstring);
void tcp_setport(struct tcp_socket inputsocket, int port);
void tcp_createsocket(struct tcp_socket inputsocket);
bool tcp_opensocket(struct tcp_socket inputsocket);
void tcp_sendcommand(struct tcp_socket inputsocket, struct command cmd);
void tcp_receive(struct tcp_socket inputsocket);
void closesocket(struct tcp_socket inputsocket);
void set_freq(struct tcp_socket inputsocket, int freq);
void set_sample_rate(struct tcp_socket inputsocket, int samplerate);
