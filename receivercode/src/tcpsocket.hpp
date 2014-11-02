/*
 * tcpsocket.hpp
 *
 *  Created on: Oct 12, 2014
 *      Author: jeremy
 */

#ifndef SRC_TCPSOCKET_HPP_
#define SRC_TCPSOCKET_HPP_

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <liquid/liquid.h>
#include <fstream>

#include <math.h>
#include <complex.h>
//#include <stdbool.h>
//#include <cstring>
//#include <time.h>
//#include <stdlib.h>
//#include <stdio.h>

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
	bool opensocket();

	void sendcommand(command);
	int receive(uint8_t*, int);
	void closesocket();

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

	ofstream myfile;
	int _I;
	int _Q;
	const float scale;
	float complex fc;

    float kf;        // modulation factor
//    liquid_freqdem_type type;

    // create modulator/demodulator objects
    freqdem fdem;
    float output;
};

} /* namespace std */

#endif /* SRC_TCPSOCKET_HPP_ */
