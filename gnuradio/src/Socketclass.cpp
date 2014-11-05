/*
 * tcpsocket.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: jeremy
 */

#include "Socketclass.hpp"
namespace std {

tcpsocket::tcpsocket() :
		_I(0), _Q(0), scale(1.0 / 128.0), buffercounter(0) {
	// TODO Auto-generated constructor stub
	sockfd = 0;
	bzero(&servaddr, sizeof(servaddr));

	_complexbufferfile.open("complexbuffer.bin",
			ios::out | ios::app | ios::binary);
	_filteredfile.open("filtered.bin", ios::out | ios::app | ios::binary);
	_demodulatedfile.open("demodulated.bin", ios::out | ios::app | ios::binary);
	_filteredanddemodulatedfile.open("filteredanddemodulated.bin",
			ios::out | ios::app | ios::binary);

	filter = gr::filter::firdes::low_pass(1, 2e6, 75e3, 25e3,
			gr::filter::firdes::WIN_HAMMING, 6.76);

	filtersize = filter.size();

	std::cout << "filter size = " << filtersize << std::endl;

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

void tcpsocket::closesocket() {
	close(sockfd);
}

bool tcpsocket::opensocket() {
	bool returnFlag = false;
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == 0) {
		//Success opening socket
		returnFlag = true;
	}
	return returnFlag;

}

void tcpsocket::sendcommand(command cmd) {
	//sends little endian

	send(sockfd, (const char*) &cmd, sizeof(cmd), 0);
}

int tcpsocket::receive(uint8_t* passedinbuffer, int size) {

//receives 8 bytes I, 8 bytes Q as unsigned int's need to subtrack 127
	int returnvalue;

	returnvalue = recv(sockfd, (char*) passedinbuffer, size, 0);
//	std::cout << returnvalue << std::endl;

	for (int x = 0; x < (returnvalue / 2); x++) {
//
		if (buffercounter == filtersize) {
//
//			//This is working as writing the input in complex form to a file
			_complexbufferfile.write((char*) &complexinputbuffer,
					sizeof(std::complex<float>) * buffercounter);
//
			//multiply input buffer by filter
			for (unsigned int length = 0; length < filtersize; length++) {
				filteroutput[length] = filter.at(length)
						* complexinputbuffer[length];
			}
			_filteredfile.write((char*) &filteroutput,
					sizeof(float) * buffercounter);


			//resample


//			freqdem_demodulate_block(fdem, reinterpret_cast<liquid_float_complex*>(&filteroutput), buffercounter,
//					filtereddemodoutput);
//
//			_filteredanddemodulatedfile.write((char*) &filtereddemodoutput, sizeof(float complex) * buffercounter);

//			freqdem_demodulate(fdem, complexinputbuffer, demodoutput);
//			_demodulatedfile.write((char*) &demodoutput, sizeof(float complex) * buffercounter);

//			myfile.write((char*) &demodoutput, sizeof(float) * buffercounter);

			buffercounter = 0;
		}

		_I = passedinbuffer[2 * x];
		_Q = passedinbuffer[((2 * x) + 1)];
		input.real(scale * (_I - 127));
		input.imag(scale * (_Q - 127));
//		memcpy(&fc,&complexbuffer, sizeof(complexbuffer));d
//		myfile.write((char*) &complexbuffer, sizeof(complexbuffer));

		complexinputbuffer[buffercounter] = input;

//	_demodulatedfile.write((char*) &demodoutput, sizeof(float complex) * buffercounter);

//		myfile.write((char*) &complexinputbuffer[buffercounter], sizeof(float complex));

//		printf("%d items in buffer", buffercounter);

//		buffercounter++;

//}

//		myfile.write((char*) &_I, sizeof(_I));
//		myfile.write((char*) &_Q, sizeof(_Q));

//	    freqdem_demodulate_block(fdem, complexinputbuffer, 1, output);
	}
	return returnvalue;
}

void tcpsocket::set_freq(int freq) {
	struct command cmd = { 0x01, htonl(freq) };
	sendcommand(cmd);
}

void tcpsocket::set_sample_rate(int sample_rate) {
	struct command cmd = { 0x02, htonl(sample_rate) };
	sendcommand(cmd);
}

//Command not used
void tcpsocket::set_gain_mode(int manual) {
	struct command cmd = { 0x03, htonl(manual) };
	sendcommand(cmd);
}

//Command not used
void tcpsocket::set_gain(int gain) {
	struct command cmd = { 0x04, htonl(gain) };
	sendcommand(cmd);
}

//Command not used
void tcpsocket::set_freq_corr(int ppm) {
	struct command cmd = { 0x05, htonl(ppm) };
	sendcommand(cmd);
}

//Command not used
void tcpsocket::set_if_gain(int stage, int gain) {
	uint32_t params = stage << 16 | (gain & 0xffff);
	struct command cmd = { 0x06, htonl(params) };
	sendcommand(cmd);
}

//Command not used
void tcpsocket::set_agc_mode(int on) {
	struct command cmd = { 0x08, htonl(on) };
	sendcommand(cmd);
}

//Command not used
void tcpsocket::set_direct_sampling(int on) {
	struct command cmd = { 0x09, htonl(on) };
	sendcommand(cmd);
}

//Command not used
void tcpsocket::set_offset_tuning(int on) {
	struct command cmd = { 0x0a, htonl(on) };
	sendcommand(cmd);
}

tcpsocket::~tcpsocket() {
// TODO Auto-generated destructor stub
	_complexbufferfile.close();
	_filteredfile.close();
	_demodulatedfile.close();
	_filteredanddemodulatedfile.close();
}

} /* namespace std */
