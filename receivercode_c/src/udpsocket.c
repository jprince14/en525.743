#include "udpsocket.h"

void udp_setaddress(struct udp_socket* inputsocket, char* inputstring) {
	inputsocket->servaddr.sin_addr.s_addr = inet_addr(inputstring);
}

void udp_setport(struct udp_socket* inputsocket, int port) {
	inputsocket->servaddr.sin_port = htons(port);
}

void udp_createsocket(struct udp_socket* inputsocket) {
	inputsocket->servaddr.sin_family = AF_INET;
	inputsocket->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
}

int udp_opensocket(struct udp_socket* inputsocket) {
	bool returnFlag = -1;
	if (connect(inputsocket->sockfd, (struct sockaddr *) &inputsocket->servaddr, sizeof(struct sockaddr_in)) == 0) {
		//Success opening socket
		returnFlag = 0;
	}
	return returnFlag;
}

void udp_senddata(struct udp_socket* inputsocket) {

}

void udp_receive(struct udp_socket* inputsocket) {

}

void closeudpsocket(struct udp_socket* inputsocket) {
	close(inputsocket->sockfd);

}
