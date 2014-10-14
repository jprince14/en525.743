//#include <strings.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>

#include "tcpsocket.hpp"
#include <thread>

#include <stdio.h>
#include <iostream>

using namespace std;

//GNU Radio code for interacting with the SDR
//http://git.osmocom.org/gr-osmosdr/tree/lib/rtl_tcp

char receivebuffer[200000];

bool exitflag = false;

void receivethread(tcpsocket* socket) {

	while (exitflag == false) {
//		printf("the thread is running\n");
		socket->receive(receivebuffer, sizeof(receivebuffer));
	}
}

int main(int argc, char**argv) {

	tcpsocket* rtlsocket = new tcpsocket;
	rtlsocket->assignipaddr("127.0.0.1");
	rtlsocket->assignport(1234);
	rtlsocket->createsocket();
	rtlsocket->opensocket();

	rtlsocket->set_freq(123458);

	std::thread receivingthread(receivethread, rtlsocket);


	std::cout << "enter 1 to stop the program\n";

	int x;
	while (cin >> x) {
		if (x == 1) {

//		printf("input = 1\n");
			exitflag = true;
			rtlsocket->closesocket();
			break;
		}

	}

	return 0;
}
