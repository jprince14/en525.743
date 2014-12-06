#include "tcpsocket.h"

void tcp_setaddress(struct tcp_socket* inputsocket, char* inputstring) {
	inputsocket->servaddr.sin_addr.s_addr = inet_addr(inputstring);
}

void tcp_setport(struct tcp_socket* inputsocket, int port) {
	inputsocket->servaddr.sin_port = htons(port);
}

void tcp_createsocket(struct tcp_socket* inputsocket) {
	inputsocket->sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    bzero((char *) &inputsocket->servaddr, sizeof(inputsocket->servaddr));
	inputsocket->servaddr.sin_family = AF_INET;

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	setsockopt(inputsocket->sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*) &tv, sizeof(struct timeval));

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
	listen(inputsocket->sockfd, 50);
	inputsocket->clilen = sizeof(inputsocket->cli_addr);

	while (sdr->receiverexitflag == false) {

		bool connected = false;

		inputsocket->newsockfd = accept(inputsocket->sockfd, (struct sockaddr *) &inputsocket->cli_addr,
				&inputsocket->clilen);
		if (inputsocket->newsockfd < 0) {
			//Waiting for connectoin
//			printf("Waiting for connection\n");
		} else {
			printf("Client Accepted!\n");
			connected = true;
		}

		while ((connected == true) && (sdr->receiverexitflag == false)) {
			int n;
			bzero(inputsocket->receivebuffer, (100 * sizeof(uint32_t)));
			//receive in loop until a disconnect is received
			n = read(inputsocket->newsockfd, inputsocket->receivebuffer, (1000 * sizeof(char)));

			if (n < 0) {
//				printf("ERROR reading from socket");
				//it was a timeout do nothing
			} else {
				//command received, process command

				uint32_t part1;
				uint32_t part2;
				memcpy(&part1, inputsocket->receivebuffer, 4);
				memcpy(&part2, inputsocket->receivebuffer + 4, 4);

				printf("Command received; %d:%d\n", part1, part2);

				connected = processcommand(inputsocket, sdr, dsp, part1, part2);
			}
		}
	}

}

bool processcommand(struct tcp_socket* inputsocket, struct rtlsdrstruct* sdr, struct liquidobjects* dsp, uint32_t part1,
		uint32_t part2) {
	bool returnFlag;

	if (part1 == 1) {
//Tune Fm frequency
		tune_sdr(sdr, part2, dsp);
		printf("SDR Tuned to frequency %d\n", part2);
		returnFlag = true;
	}

	else if (part1 == 2) {
//set cb channel
		set_cb_freq_sdr(sdr, part2, dsp);
		printf("SDR Tuned to CB channel %d\n", part2);
		returnFlag = true;
	} else if (part1 == 3) {
//		change modulation type

		if (part2 == 0) {
			printf("Modulation type set to FM-mono\n");
			dsp->demodtype = mono_FM;
//		} else if (part2 == 1) {
//			printf("Modulation type set to FM-stereo\n");
//			dsp->demodtype = stereo_FM;
		} else if (part2 == 2) {
			printf("Modulation type set to CB-AM\n");
			dsp->demodtype = cb_AM;
		}

		dsp->buffercounter = 0;
		returnFlag = true;

	} else if (part1 == 4) {
		//Exit
//		inputsocket->bufferrunning = false;
//		sdr->receiverexitflag = true;
		printf("Receiver has exited, waiting for new receivers\n");
		returnFlag = false;

	} else if (part1 == 5) {
		if (part2 == 0) {
			printf("Now sending PCM Audio\n");
			pthread_mutex_lock(&sdr->sdrlock);
			//send the raw IQ data
			sdr->sendaudio = true;
			pthread_mutex_unlock(&sdr->sdrlock);

		} else if (part2 == 1) {
			printf("Now sending RAW IQ data\n");
			pthread_mutex_lock(&sdr->sdrlock);
			//send the raw IQ data
			sdr->sendaudio = false;
			pthread_mutex_unlock(&sdr->sdrlock);
		}
		returnFlag = true;

	} else if ((part1 == 0) && (part2 == 0)) {
		printf("FIN Command received\n");
		returnFlag = false;
	}

	return returnFlag;
}
