#ifndef SRC_TCPSOCKET_HPP_
#define SRC_TCPSOCKET_HPP_

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

struct commandstructure {
	uint32_t cmd;
	uint32_t param;
};

namespace std {

class tcpsocket {
public:
	tcpsocket();

	struct sockaddr_in servaddr;
	int sockfd;
	fd_set fdset;
	struct timeval tv;
//	bool socketwasopenflag;

	void assignipaddr(std::string);
	void assignport(int port);
	void createsocket();
	bool opensocket();
	void Setrunningflag(bool);
	bool Getrunningflag();
	int receive(char*);
	void closesocket();
	void sendcommand(uint32_t command[2]);

	pthread_mutex_t tcprunninglock;
    fd_set  rset, wset;

	virtual ~tcpsocket();
private:
	bool runningflag;

};

} /* namespace std */

#endif /* SRC_TCPSOCKET_HPP_ */
