#include "udpclient.hpp"

namespace std {

udpsocket::udpsocket() :
		socketwasopenflag(false) {
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
	printf("udpclosesocket was run\n");
	if (socketwasopenflag == true) {
		close(sockfd);
	}
}

bool udpsocket::opensocket() {

	bool returnFlag = false;
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) == 0) {
		//Success opening socket
		returnFlag = true;
	}
	return returnFlag;

}

int udpsocket::receive(char* passedinbuffer) {
	socklen_t fromlen = sizeof(servaddr);

	int length = recvfrom(sockfd, (char*) &receivebuffer, 1500 * sizeof(float), 0, (struct sockaddr *) &servaddr,
			&fromlen);

	return 0;
}

udpsocket::~udpsocket() {
// TODO Auto-generated destructor stub

}

} /* namespace std */
