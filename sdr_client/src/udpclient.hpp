#ifndef SRC_udpSOCKET_HPP_
#define SRC_udpSOCKET_HPP_

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <pthread.h>

namespace std {

class udpsocket {
public:
	udpsocket();

	struct sockaddr_in servaddr;
	int sockfd;
	float receivebuffer[10000];
	bool socketwasopenflag;
	void Setrunningflag(bool);
	bool Getrunningflag();

	pthread_mutex_t queuelock;

	struct receivestruct {
		unsigned int revlength;
		float rcvbuffer[2500];
	};

	struct receivestruct rcv_struct;
	std::queue<receivestruct> *rcv_que;

	bool audiobufferset;

	void assignipaddr(std::string);
	void assignport(int port);
	void createsocket();
	bool opensocket();

	void receive();
	void closesocket();

	virtual ~udpsocket();
private:
	bool runningflag;

};

} /* namespace std */

#endif /* SRC_udpSOCKET_HPP_ */
