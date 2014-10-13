/*
 * tcpsocket.hpp
 *
 *  Created on: Oct 12, 2014
 *      Author: jeremy
 */

#ifndef SRC_TCPSOCKET_HPP_
#define SRC_TCPSOCKET_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <time.h>
#include <string>
#include <unistd.h>

namespace std {

class tcpsocket {
public:
	tcpsocket();

	struct sockaddr_in servaddr;
	int sockfd;

	void assignipaddr(std::string);
	void assignport(int port);
	void createsocket();
	void opensocket();
	void senduint32(uint32_t );


	virtual ~tcpsocket();
};

} /* namespace std */

#endif /* SRC_TCPSOCKET_HPP_ */
