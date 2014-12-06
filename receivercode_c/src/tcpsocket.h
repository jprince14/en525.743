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
#include "sdr.h"
#include "structures.h"
#include <pthread.h>

void tcp_setaddress(struct tcp_socket* inputsocket, char* inputstring);
void tcp_setport(struct tcp_socket* inputsocket, int port);
void tcp_createsocket(struct tcp_socket* inputsocket);
int tcp_opensocket(struct tcp_socket* inputsocket);
void tcp_closesocket(struct tcp_socket* inputsocket);
void tcp_listen(struct tcp_socket* inputsocket, struct rtlsdrstruct* sdr, struct liquidobjects* dsp);
bool processcommand(struct tcp_socket* inputsocket, struct rtlsdrstruct* sdr, struct liquidobjects* dsp, uint32_t part1, uint32_t part2);

#endif
