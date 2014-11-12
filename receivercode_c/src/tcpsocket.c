#include "tcpsocket.h"

void tcp_setaddress(struct tcp_socket* inputsocket, char* inputstring) {
	inputsocket->servaddr.sin_addr.s_addr = inet_addr(inputstring);
}

void tcp_setport(struct tcp_socket* inputsocket, int port) {
	inputsocket->servaddr.sin_port = htons(port);
}

void tcp_createsocket(struct tcp_socket* inputsocket) {
	inputsocket->servaddr.sin_family = AF_INET;
	inputsocket->sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

int tcp_opensocket(struct tcp_socket* inputsocket) {
	bool returnFlag = -1;

	if (connect(inputsocket->sockfd, (struct sockaddr *) &inputsocket->servaddr, sizeof(struct sockaddr_in)) == 0) {
		//Success opening socket
		returnFlag = 0;
	}
	return returnFlag;
}

void tcp_sendcommand(struct tcp_socket* inputsocket, struct command cmd) {
	send(inputsocket->sockfd, (const char*) &cmd, sizeof(cmd), 0);
}

void tcp_receive(struct tcp_socket* inputsocket) {
	inputsocket->receivesize = recv(inputsocket->sockfd, (char*) inputsocket->buffer, 1000, 0);
}

void tcp_closesocket(struct tcp_socket* inputsocket) {
	close(inputsocket->sockfd);
}

void set_freq(struct tcp_socket* inputsocket, int freq) {
	struct command cmd = { 0x01, htonl(freq) };
	tcp_sendcommand(inputsocket, cmd);
}
void set_sample_rate(struct tcp_socket* inputsocket, int samplerate) {
	struct command cmd = { 0x02, htonl(samplerate) };
	tcp_sendcommand(inputsocket, cmd);
}

void set_cb_freq(struct tcp_socket* socketstruct, int cbchannel) {

	printf("channel passed in = %d", cbchannel);
	switch (cbchannel) {

	case 1:
		set_freq(socketstruct, CB_CHANNEL_1);
		break;
	case 2:
		set_freq(socketstruct, CB_CHANNEL_2);
		break;
	case 3:
		set_freq(socketstruct, CB_CHANNEL_3);
		break;
	case 4:
		set_freq(socketstruct, CB_CHANNEL_4);
		break;
	case 5:
		set_freq(socketstruct, CB_CHANNEL_5);
		break;
	case 6:
		set_freq(socketstruct, CB_CHANNEL_6);
		break;
	case 7:
		set_freq(socketstruct, CB_CHANNEL_7);
		break;
	case 8:
		set_freq(socketstruct, CB_CHANNEL_8);
		break;
	case 9:
		set_freq(socketstruct, CB_CHANNEL_9);
		break;
	case 10:
		set_freq(socketstruct, CB_CHANNEL_10);
		break;
	case 11:
		set_freq(socketstruct, CB_CHANNEL_11);
		break;
	case 12:
		set_freq(socketstruct, CB_CHANNEL_12);
		break;
	case 13:
		set_freq(socketstruct, CB_CHANNEL_13);
		break;
	case 14:
		set_freq(socketstruct, CB_CHANNEL_14);
		break;
	case 15:
		set_freq(socketstruct, CB_CHANNEL_15);
		break;
	case 16:
		set_freq(socketstruct, CB_CHANNEL_16);
		break;
	case 17:
		set_freq(socketstruct, CB_CHANNEL_17);
		break;
	case 18:
		set_freq(socketstruct, CB_CHANNEL_18);
		break;
	case 19:
		set_freq(socketstruct, CB_CHANNEL_19);
		break;
	case 20:
		set_freq(socketstruct, CB_CHANNEL_20);
		break;
	case 21:
		set_freq(socketstruct, CB_CHANNEL_21);
		break;
	case 22:
		set_freq(socketstruct, CB_CHANNEL_22);
		break;
	case 23:
		set_freq(socketstruct, CB_CHANNEL_23);
		break;
	case 24:
		set_freq(socketstruct, CB_CHANNEL_24);
		break;
	case 25:
		set_freq(socketstruct, CB_CHANNEL_25);
		break;
	case 26:
		set_freq(socketstruct, CB_CHANNEL_26);
		break;
	case 27:
		set_freq(socketstruct, CB_CHANNEL_27);
		break;
	case 28:
		set_freq(socketstruct, CB_CHANNEL_28);
		break;
	case 29:
		set_freq(socketstruct, CB_CHANNEL_29);
		break;
	case 30:
		set_freq(socketstruct, CB_CHANNEL_30);
		break;
	case 31:
		set_freq(socketstruct, CB_CHANNEL_31);
		break;
	case 32:
		set_freq(socketstruct, CB_CHANNEL_32);
		break;
	case 33:
		set_freq(socketstruct, CB_CHANNEL_33);
		break;
	case 34:
		set_freq(socketstruct, CB_CHANNEL_34);
		break;
	case 35:
		set_freq(socketstruct, CB_CHANNEL_35);
		break;
	case 36:
		set_freq(socketstruct, CB_CHANNEL_36);
		break;
	case 37:
		set_freq(socketstruct, CB_CHANNEL_37);
		break;
	case 38:
		set_freq(socketstruct, CB_CHANNEL_38);
		break;
	case 39:
		set_freq(socketstruct, CB_CHANNEL_30);
		break;
	case 40:
		set_freq(socketstruct, CB_CHANNEL_40);
		break;
	}

}

