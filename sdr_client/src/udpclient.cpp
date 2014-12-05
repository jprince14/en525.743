#include "udpclient.hpp"

namespace std {

udpsocket::udpsocket() :
		socketwasopenflag(false), audiobufferset(false), runningflag(false) {
	// TODO Auto-generated constructor stub
	sockfd = 0;
	bzero(&servaddr, sizeof(servaddr));
	rcv_que = new std::queue<receivestruct>;

	if (pthread_mutex_init(&queuelock, NULL) != 0) {
		printf("ERROR: Unable to open queuelock\n");
	}

	if (pthread_mutex_init(&udprunninglock, NULL) != 0) {
		printf("ERROR: Unable to open TCP running lock\n");
	}

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
}

void udpsocket::closesocket() {

	runningflag = false;

	if (socketwasopenflag == true) {
		close(sockfd);
	}
	socketwasopenflag = false;
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
	pthread_mutex_lock(&queuelock);

	rcv_que->push(rcv_struct);

	pthread_mutex_unlock(&queuelock);
	if ((int) rcv_que->size() % 500 == 0) {
		printf("rcv_que length = %d\n", int(rcv_que->size()));

	}
//	printf("queue.size = %d with length %d and struct length %d\n", (int) rcv_que->size(), rcv_que->back().revlength,
//			rcv_struct.revlength);

//	return length;
}

void udpsocket::Setrunningflag(bool input) {
	pthread_mutex_lock(&udprunninglock);
	runningflag = input;
	pthread_mutex_unlock(&udprunninglock);
}
bool udpsocket::Getrunningflag() {
	pthread_mutex_lock(&udprunninglock);
	bool flag = runningflag;
	pthread_mutex_unlock(&udprunninglock);
	return flag;

}

udpsocket::~udpsocket() {
// TODO Auto-generated destructor stub

//empty the queue
	pthread_mutex_lock(&queuelock);

	//empty the receive queue
	while (!rcv_que->empty()) {
		rcv_que->pop();
	}
	pthread_mutex_unlock(&queuelock);

	pthread_mutex_destroy(&queuelock);
	pthread_mutex_destroy(&udprunninglock);

	delete rcv_que;
}

} /* namespace std */
