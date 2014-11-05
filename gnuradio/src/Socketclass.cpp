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

	_complexbufferfile.open("complexbuffer.bin", ios::out | ios::app | ios::binary);
	_filteredfile.open("filtered.bin", ios::out | ios::app | ios::binary);
	_demodulatedfile.open("demodulated.bin", ios::out | ios::app | ios::binary);
	_filteredanddemodulatedfile.open("filteredanddemodulated.bin", ios::out | ios::app | ios::binary);

	kf = 0.1f;        // modulation factor

	// create modulator/demodulator objects
	fdem = freqdem_create(kf);

	filter_fc = 0.375f;          // filter cutoff frequency = fc / 2*fs
	filter_ft = 0.125f;			//filter transition = ft / 2*fs
	filter_As = 60.0f;         // stop-band attenuation [dB]
	filter_mu = 0.0f;          // fractional timing offset

	h_len = estimate_req_filter_len(filter_ft, filter_As);
//	liquid_firdes_kaiser(h_len, filter_fc, filter_As, filter_mu, filterpulse);
	printf("h_len = %d\n", h_len);
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

		if (buffercounter == h_len) {

			//This is working as writing the input in complex form to a file
			_complexbufferfile.write((char*) &complexinputbuffer, sizeof(float complex) * buffercounter);

			//multiply input buffer by filter
			for (unsigned int length = 0; length < h_len; length++) {
//				filteroutput[length] = filterpulse[length] * complexinputbuffer[length];
			}
			_filteredfile.write((char*) &filteroutput, sizeof(float complex) * buffercounter);

//			freqdem_demodulate_block(fdem, reinterpret_cast<liquid_float_complex*>(&filteroutput), buffercounter,
//					filtereddemodoutput);
//
//			_filteredanddemodulatedfile.write((char*) &filtereddemodoutput, sizeof(float complex) * buffercounter);

//			freqdem_demodulate(fdem, complexinputbuffer, demodoutput);
//			_demodulatedfile.write((char*) &demodoutput, sizeof(float complex) * buffercounter);

//			}

//			myfile.write((char*) &demodoutput, sizeof(float) * buffercounter);

			buffercounter = 0;
		}

		_I = passedinbuffer[2 * x];
		_Q = passedinbuffer[((2 * x) + 1)];
//		complexbuffer.real(scale * (_I - 127));
//		complexbuffer.imag(scale * (_Q - 127));
//		memcpy(&fc,&complexbuffer, sizeof(complexbuffer));d
//		myfile.write((char*) &complexbuffer, sizeof(complexbuffer));

//		complexinputbuffer = (scale * (_I - 127)) + (I * scale * (_Q - 127));

		freqdem_demodulate(fdem, static_cast<liquid_float_complex>(complexinputbuffer), &demodoutput);
		_demodulatedfile.write((char*) &demodoutput, sizeof(float complex) * buffercounter);

//		myfile.write((char*) &complexinputbuffer[buffercounter], sizeof(float complex));

//		printf("%d items in buffer", buffercounter);

//		buffercounter++;

	}

	//		myfile.write((char*) &_I, sizeof(_I));
//		myfile.write((char*) &_Q, sizeof(_Q));

//	    freqdem_demodulate_block(fdem, complexinputbuffer, 1, output);

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
	freqdem_destroy(fdem);
	_complexbufferfile.close();
	_filteredfile.close();
	_demodulatedfile.close();
	_filteredanddemodulatedfile.close();
}

} /* namespace std */
