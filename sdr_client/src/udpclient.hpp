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

namespace std {

class udpsocket {
public:
	udpsocket();

	struct sockaddr_in servaddr;
	int sockfd;
	float receivebuffer[1500];
	bool socketwasopenflag;
	void Setrunningflag(bool);
	bool Getrunningflag();



	void assignipaddr(std::string);
	void assignport(int port);
	void createsocket();
	bool opensocket();

	int receive(float*);
	void closesocket();

	virtual ~udpsocket();
private:
	bool runningflag;

};

} /* namespace std */

#endif /* SRC_udpSOCKET_HPP_ */
