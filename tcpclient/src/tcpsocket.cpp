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
	sockfd = 0;
	bzero(&servaddr, sizeof(servaddr));
	myfile.open("example.bin", ios::out | ios::app | ios::binary);
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

#warning - add in checking to see if socket is open

	send(sockfd, (const char*) &cmd, sizeof(cmd), 0);
}

int tcpsocket::receive(char* passedinbuffer, int size) {

//receives 8 bytes I, 8 bytes Q as unsigned int's need to subtrack 127
	int returnvalue;

	returnvalue = recv(sockfd, (char*) passedinbuffer, size, 0);
	std::cout << returnvalue << std::endl;



#warning - this part below is causing a seg fault
	//attempting to turn the unsigned I and Q bits recieved into signed

	/*int8_t I;
	int8_t Q;

	for (int8_t x = 0; x < (returnvalue / 4); x++) {
		memcpy(&I, passedinbuffer + x, 2);
		memcpy(&Q, passedinbuffer + (2 + x), 2);

		printf("I = %x\n", I);
		printf("Q = %x\n", Q);
		I -= 127;
		Q -= 127;

		printf("I = %x\n", I);
		printf("Q = %x\n", Q);


		myfile.write(reinterpret_cast<const char *>(&I), sizeof(int8_t));
		myfile.write(reinterpret_cast<const char *>(&Q), sizeof(int8_t));



	}*/
	myfile.write(passedinbuffer, returnvalue);

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
	myfile.close();
}

} /* namespace std */
