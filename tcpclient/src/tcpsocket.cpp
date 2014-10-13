/*
 * tcpsocket.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: jeremy
 */

#include "tcpsocket.hpp"

namespace std {

tcpsocket::tcpsocket() {
	// TODO Auto-generated constructor stub
//	std::string serveraddr = "127.0.0.1";
	sockfd = 0;
	bzero(&servaddr, sizeof(servaddr));
//	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//	servaddr.sin_port = htons(1234);

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
}

void tcpsocket::opensocket() {

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
}

void tcpsocket::senduint32(uint32_t command) {
	//sends little endian
	send(sockfd, (char*) &command, sizeof(command), 0);
}

tcpsocket::~tcpsocket() {
// TODO Auto-generated destructor stub
}

} /* namespace std */
