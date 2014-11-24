#include "tcpclient.hpp"

namespace std {

tcpsocket::tcpsocket() :
		socketwasopenflag(false), runningflag(false) {
	// TODO Auto-generated constructor stub
	sockfd = 0;
	bzero(&servaddr, sizeof(servaddr));

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

	socketwasopenflag = true;
}

void tcpsocket::closesocket() {
	printf("tcpclosesocket was run\n");

	runningflag = false;

	if (socketwasopenflag == true) {
		close(sockfd);
	}
	socketwasopenflag = false;

}

bool tcpsocket::opensocket() {
	bool returnFlag = false;
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == 0) {
		//Success opening socket
		returnFlag = true;
	}
	socketwasopenflag = true;

	return returnFlag;

}

void tcpsocket::sendcommand(uint32_t command[2]) {

	if (socketwasopenflag == true) {
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
	runningflag = input;
}
bool tcpsocket::Getrunningflag() {
	return runningflag;
}

tcpsocket::~tcpsocket() {
// TODO Auto-generated destructor stub

}

} /* namespace std */
