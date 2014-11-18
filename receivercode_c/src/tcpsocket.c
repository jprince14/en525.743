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

	if (bind(inputsocket->sockfd, (struct sockaddr *) &inputsocket->servaddr, sizeof(inputsocket->servaddr)) == 0) {
		//Success opening socket
		returnFlag = 0;
	}
	return returnFlag;
}

void tcp_closesocket(struct tcp_socket* inputsocket) {
	close(inputsocket->sockfd);
}

void tcp_listen(struct tcp_socket* inputsocket, struct rtlsdrstruct* sdr, struct liquidobjects* dsp) {
printf("listen 1\n");
	listen(inputsocket->sockfd, 5);
	inputsocket->clilen = sizeof(inputsocket->cli_addr);
	inputsocket->newsockfd = accept(inputsocket->sockfd, (struct sockaddr *) &inputsocket->cli_addr,
			&inputsocket->clilen);
	if (inputsocket->newsockfd < 0)
		error("ERROR on accept");
	bzero(inputsocket->receivebuffer, (100 * sizeof(uint32_t)));
	int n;
	printf("listen 2\n");
	n = read(inputsocket->newsockfd, inputsocket->receivebuffer, (100 * sizeof(uint32_t)));
	if (n < 0)
		error("ERROR reading from socket");
	processcommand(inputsocket, sdr, dsp);
	printf("listen 3\n");
}

void processcommand(struct tcp_socket* inputsocket, struct rtlsdrstruct* sdr, struct liquidobjects* dsp) {

	if (inputsocket->receivebuffer[0] == 0) {
//		change modulation type

		if (inputsocket->receivebuffer[1] == 0) {
			dsp->demodtype = mono_FM;
		} else if (inputsocket->receivebuffer[1] == 1) {
			dsp->demodtype = stereo_FM;
		} else if (inputsocket->receivebuffer[1] == 2) {
			dsp->demodtype = cb_AM;
		}

		dsp->buffercounter = 0;

	} else if (inputsocket->receivebuffer[0] == 1) {
//Tune Fm frequency
		tune_sdr(sdr, inputsocket->receivebuffer[1], dsp);
	}

	if (inputsocket->receivebuffer[0] == 2) {
//set cb channel
		set_cb_freq_sdr(dsp, inputsocket->receivebuffer[1], dsp);

	}

	if (inputsocket->receivebuffer[0] == 3) {
		//Exit
		sdr->receiverexitflag = true;

	}

}
