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
#include <gnuradio/filter/firdes.h>
#include <gnuradio/analog/frequency_modulator_fc.h>
#include <fstream>

#include <math.h>
#include <complex>
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

	unsigned int filtersize;

	virtual ~tcpsocket();

	ofstream _complexbufferfile;
	ofstream _filteredfile;
	ofstream _demodulatedfile;
	ofstream _filteredanddemodulatedfile;

	int _I;
	int _Q;
	const float scale;
	std::complex<float> complexinputbuffer[1000];
	std::complex<float> input;
	unsigned int buffercounter;

	vector<float> filter;

	// create modulator/demodulator objects
	float filterpulse[500];
	float filteroutput[500];
	float demodoutput;
	float filtereddemodoutput[500];

};

} /* namespace std */

#endif /* SRC_TCPSOCKET_HPP_ */
