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

void tcpsocket::sendcommand(struct commandstructure command) {

#warning - come back here
}

int tcpsocket::receive(char* passedinbuffer) {

//	int recv_size = 0;
//	recv_size = recvfrom()
//
//	return recv_size;
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
