#include "udpclient.hpp"

namespace std {

udpsocket::udpsocket() :
		socketwasopenflag(false), runningflag(false) {
	// TODO Auto-generated constructor stub
	sockfd = 0;
	bzero(&servaddr, sizeof(servaddr));
}

void udpsocket::assignipaddr(std::string ipaddr) {
	servaddr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
}

void udpsocket::assignport(int port) {
	servaddr.sin_port = htons(port);
}

void udpsocket::createsocket() {

	servaddr.sin_family = AF_INET;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
}

void udpsocket::closesocket() {

	runningflag = false;

	if (socketwasopenflag == true) {
		close(sockfd);
	}
	socketwasopenflag = false;
}

bool udpsocket::opensocket() {

	bool returnFlag = false;
	if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) == 0) {
		//Success opening socket
		printf("UDP socket opened\n");

		returnFlag = true;
	}
	return returnFlag;

}

int udpsocket::receive(float* passedinbuffer) {
	socklen_t fromlen = sizeof(servaddr);

	int length = recvfrom(sockfd, (char*) &receivebuffer, 1500 * sizeof(float), 0, (struct sockaddr *) &servaddr,
			&fromlen);

	printf("length = %d\n", length);

	return length;
}

void udpsocket::Setrunningflag(bool input){
	runningflag = input;
}
bool udpsocket::Getrunningflag(){
	return runningflag;
}


udpsocket::~udpsocket() {
// TODO Auto-generated destructor stub

}

} /* namespace std */
