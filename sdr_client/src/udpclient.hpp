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
#include "structures.h"


#ifndef ignoremutex
#define IGNOREMUTEX 1 //1 = use mutex, 0 = ignore mutex
#endif

#ifndef ignorejoin
#define JOINFLAG 1 //1 = usejoin 0 = ignore join
#endif

namespace std {

class udpsocket {
public:
	udpsocket();


	pthread_mutex_t udprunninglock;

	struct sockaddr_in servaddr;
	int sockfd;
	float receivebuffer[10000];
//	bool socketwasopenflag;
	void Setrunningflag(bool);
	bool Getrunningflag();

#if IGNOREMUTEX == 1
	pthread_mutex_t queuelock;
#endif




	struct receivestruct rcv_struct;
	std::queue<receivestruct> *rcv_que;


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
