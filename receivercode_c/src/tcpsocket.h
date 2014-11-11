#ifndef TCPSOCKET_H
#define TCPSOCKET_H


#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <liquid/liquid.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "encoder.h"
#include "structures.h"




void tcp_setaddress(struct tcp_socket* inputsocket, char* inputstring);
void tcp_setport(struct tcp_socket* inputsocket, int port);
void tcp_createsocket(struct tcp_socket* inputsocket);
int tcp_opensocket(struct tcp_socket* inputsocket);
void tcp_sendcommand(struct tcp_socket* inputsocket, struct command cmd);
void tcp_receive(struct tcp_socket* inputsocket);
void tcp_closesocket(struct tcp_socket* inputsocket);
void set_freq(struct tcp_socket* inputsocket, int freq);
void set_sample_rate(struct tcp_socket* inputsocket, int samplerate);

#endif
