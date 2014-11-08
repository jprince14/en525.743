#include "tcpsocket.h"

struct tcp_socket {
	struct sockaddr_in servaddr;
	int sockfd;
};

void tcp_setaddress(struct tcp_socket inputsocket, char* inputstring) {
	inputsocket.servaddr.sin_addr.s_addr = inet_addr(inputstring);

}
void tcp_setport(struct tcp_socket inputsocket, int port) {
	inputsocket.servaddr.sin_port = htons(port);
}

void tcp_createsocket(struct tcp_socket inputsocket) {
	inputsocket.servaddr.sin_family = AF_INET;
	inputsocket.sockfd = socket(AF_INET, SOCK_STREAM, 0);

}
bool tcp_opensocket(struct tcp_socket inputsocket) {
	bool returnFlag = false;
	if (connect(inputsocket.sockfd, (struct sockaddr *) &inputsocket.servaddr, sizeof(inputsocket.servaddr)) == 0) {
		//Success opening socket
		returnFlag = true;
	}
	return returnFlag;
}

int receive(uint8_t*, int, char* buffer) {

}

void closesocket(struct tcp_socket inputsocket) {
	close(inputsocket.sockfd);
}

void set_freq(struct tcp_socket inputsocket, int freq) {
	struct command cmd = { 0x01, htonl(freq) };
	sendcommand(inputsocket, cmd);
}
void set_sample_rate(struct tcp_socket inputsocket,  int samplerate) {
	struct command cmd = { 0x02, htonl(samplerate) };
	sendcommand(inputsocket, cmd);
}

void sendcommand(struct tcp_socket inputsocket, struct command cmd)
{
	send(inputsocket.sockfd, (const char*) &cmd, sizeof(cmd), 0);
}
