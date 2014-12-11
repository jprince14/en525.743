#include "udpclient.hpp"

namespace std {

udpsocket::udpsocket() :
		runningflag(false) {
	sockfd = 0;
	bzero(&servaddr, sizeof(servaddr));
	rcv_que = new std::queue<receivestruct>;

#if IGNOREMUTEX == 1
	if (pthread_mutex_init(&queuelock, NULL) != 0) {
		printf("ERROR: Unable to open queuelock\n");
	}

	if (pthread_mutex_init(&udprunninglock, NULL) != 0) {
		printf("ERROR: Unable to open TCP running lock\n");
	}
#endif
}

void udpsocket::assignipaddr(std::string ipaddr) {
	servaddr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
}

void udpsocket::assignport(int port) {
	servaddr.sin_port = htons(port);
}

void udpsocket::createsocket() {

	servaddr.sin_family = AF_INET;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct timeval tv;
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*) &tv, sizeof(struct timeval));

}

void udpsocket::closesocket() {

	runningflag = false;
	close(sockfd);
}

bool udpsocket::opensocket() {

	bool returnFlag = false;
	if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) == 0) {
		//Success opening socket
		printf("UDP socket opened\n");

		returnFlag = true;
	} else {
		printf("Unable to open UDP socket\n");
	}
	return returnFlag;

}

void udpsocket::receive() {
	socklen_t fromlen = sizeof(servaddr);

	rcv_struct.revlength = recvfrom(sockfd, (char*) &rcv_struct.rcvbuffer, 2500 * sizeof(float), 0,
			(struct sockaddr *) &servaddr, &fromlen);

//	printf("rcv_struct.revlength = %d\n", rcv_struct.revlength);

	if (rcv_struct.revlength > 0) {
#if IGNOREMUTEX == 1
		pthread_mutex_lock(&queuelock);
#endif
		rcv_que->push(rcv_struct);

#if IGNOREMUTEX == 1
		pthread_mutex_unlock(&queuelock);
#endif

		if ((int) rcv_que->size() % 500 == 0) {
			printf("rcv_que length = %d\n", int(rcv_que->size()));

		}
	} else {
		printf("No data received on UDP Socket\n");
	}

}

void udpsocket::Setrunningflag(bool input) {

#if IGNOREMUTEX == 1
	pthread_mutex_lock(&udprunninglock);
#endif

	runningflag = input;

#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&udprunninglock);
#endif

}

bool udpsocket::Getrunningflag() {

#if IGNOREMUTEX == 1
	pthread_mutex_lock(&udprunninglock);
#endif

	bool flag = runningflag;

#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&udprunninglock);
#endif

	return flag;

}

udpsocket::~udpsocket() {
// TODO Auto-generated destructor stub

//empty the queue
#if IGNOREMUTEX == 1
	pthread_mutex_lock(&queuelock);
#endif
	//empty the receive queue
	while (!rcv_que->empty()) {
		rcv_que->pop();
	}

#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&queuelock);
#endif

#if IGNOREMUTEX == 1
	pthread_mutex_destroy(&queuelock);
	pthread_mutex_destroy(&udprunninglock);
#endif

	delete rcv_que;
}

} /* namespace std */
