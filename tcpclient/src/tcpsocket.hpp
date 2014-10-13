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

struct command {
	unsigned char cmd;
	unsigned int param;
}__attribute__((packed));

class tcpsocket {
public:
	tcpsocket();

	struct sockaddr_in servaddr;
	int sockfd;

	void assignipaddr(std::string);
	void assignport(int port);
	void createsocket();
	void opensocket();

	void sendcommand(command);

	void set_freq(int);
	void set_sample_rate(int);
	void set_gain_mode(int);
	void set_gain(int);
	void set_freq_corr(int);
	void set_if_gain(int, int);
	void set_agc_mode(int);
	void set_direct_sampling(int);
	void set_offset_tuning(int);

	virtual ~tcpsocket();
};

} /* namespace std */

#endif /* SRC_TCPSOCKET_HPP_ */
