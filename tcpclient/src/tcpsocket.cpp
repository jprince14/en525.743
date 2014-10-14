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

void tcpsocket::opensocket() {

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
}

void tcpsocket::sendcommand(command cmd) {
	//sends little endian

#warning - add in checking to see if command is open

	send(sockfd, (const char*) &cmd, sizeof(cmd), 0);
}

int tcpsocket::receive(char* passedinbuffer, int size) {

	memset(passedinbuffer, 0x00, size);

	int returnvalue;

	returnvalue = recv(sockfd, (char*) passedinbuffer, size, 0);
	std::cout << passedinbuffer;
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

void tcpsocket::set_gain_mode(int manual) {
	struct command cmd = { 0x03, htonl(manual) };
	sendcommand(cmd);
}

void tcpsocket::set_gain(int gain) {
	struct command cmd = { 0x04, htonl(gain) };
	sendcommand(cmd);
}

void tcpsocket::set_freq_corr(int ppm) {
	struct command cmd = { 0x05, htonl(ppm) };
	sendcommand(cmd);
}

void tcpsocket::set_if_gain(int stage, int gain) {
	uint32_t params = stage << 16 | (gain & 0xffff);
	struct command cmd = { 0x06, htonl(params) };
	sendcommand(cmd);
}

void tcpsocket::set_agc_mode(int on) {
	struct command cmd = { 0x08, htonl(on) };
	sendcommand(cmd);
}

void tcpsocket::set_direct_sampling(int on) {
	struct command cmd = { 0x09, htonl(on) };
	sendcommand(cmd);
}

void tcpsocket::set_offset_tuning(int on) {
	struct command cmd = { 0x0a, htonl(on) };
	sendcommand(cmd);
}

tcpsocket::~tcpsocket() {
// TODO Auto-generated destructor stub
}

} /* namespace std */
