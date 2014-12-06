#include "tcpclient.hpp"

namespace std {

tcpsocket::tcpsocket() :
		runningflag(false) {
	// TODO Auto-generated constructor stub
	sockfd = 0;
	bzero(&servaddr, sizeof(servaddr));

	if (pthread_mutex_init(&tcprunninglock, NULL) != 0) {
		printf("ERROR: Unable to open TCP running lock\n");
	}

}

void tcpsocket::assignipaddr(std::string ipaddr) {
	servaddr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
}

void tcpsocket::assignport(int port) {
	servaddr.sin_port = htons(port);
}

void tcpsocket::createsocket() {

	servaddr.sin_family = AF_INET;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char*) &tv, sizeof(struct timeval));

//	socketwasopenflag = true;
}

void tcpsocket::closesocket() {
	printf("tcpclosesocket was run\n");

	runningflag = false;
	close(sockfd);

//	if (socketwasopenflag == true) {
//	}
//	socketwasopenflag = false;

}

bool tcpsocket::opensocket() {
	bool returnFlag = false;

//	socketwasopenflag = false;

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == 0) {
		//Success opening socket
		returnFlag = true;
//		socketwasopenflag = true;

	}

	printf("TCP socket return flag = %s\n", returnFlag ? "true" : "false");
	return returnFlag;

}

void tcpsocket::sendcommand(uint32_t command[2]) {

	if (Getrunningflag() == true) {
//		int n;
//		n = write(sockfd, "I got your message", 18);
//		if (n < 0) {
//			printf("ERROR writing to socket\n");
//		}
		int n = write(sockfd, command, 2 * sizeof(uint32_t));
		if (n < 0) {
			printf("ERROR writing to socket\n");
		}
	}
}

int tcpsocket::receive(char* passedinbuffer) {

//	int recv_size = 0;
//	recv_size = recvfrom()
//
//	return recv_size;
	return 0;
}

void tcpsocket::Setrunningflag(bool input) {
	pthread_mutex_lock(&tcprunninglock);

	runningflag = input;
	pthread_mutex_unlock(&tcprunninglock);

}
bool tcpsocket::Getrunningflag() {

	pthread_mutex_lock(&tcprunninglock);

	bool flag = runningflag;
	pthread_mutex_unlock(&tcprunninglock);
	return flag;

}

tcpsocket::~tcpsocket() {

	pthread_mutex_destroy(&tcprunninglock);

// TODO Auto-generated destructor stub

}

} /* namespace std */
