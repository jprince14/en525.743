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
	std::thread *receivingthread;

	tcpsocket* rtlsocket = new tcpsocket;
	rtlsocket->assignipaddr("127.0.0.1");
	rtlsocket->assignport(1234);
	rtlsocket->createsocket();

	if (rtlsocket->opensocket() == true) {
		receivingthread = new std::thread(receivethread, rtlsocket);
		//TODO Update so that the user can enter the IP and Port through the GUI
//		receivingthread.detach();
	}

	else {
		std::cout << "Unable to connect to socket, program exiting\n";
		exit(0);
	}

	std::cout << "Welcome to Jeremy's EN525.743 Embedded Development Project\n";
	std::cout << "\tEnter 1 to adjust the frequency of the SDR\n";
	std::cout << "\tEnter 2 to adjust the sampling rate of the SDR\n";
	std::cout << "\tEnter 3 to adjust the demodulator\n";
	std::cout << "\tEnter 9 to exit\n";

	int x;
	while (cin >> x) {

		//Adjust frequency
		if (x == 1) {
//TODO print out the frequency range of the tuner
			std::cout << "Enter the desired tuning frequency (in Hz)\n";
			uint32_t freq;
			std::cin >> freq;
			rtlsocket->set_freq(freq);
		}

		// adjust sampling rate
		if (x == 2) {
//TODO print out the potential sampling rates of the tuner
			std::cout << "Enter the desired sampling rate (in Hz)\n";
			uint32_t samplingrate;
			std::cin >> samplingrate;
			rtlsocket->set_sample_rate(samplingrate);
		}

		//adjust modulation type
		if (x == 3) {
			//TODO: Come back here - set the modulation type
		}

		//Exit
		if (x == 9) {

			std::cout << "Exit signal received\n";
			exitflag = true;
			rtlsocket->closesocket();
			break;
		}

	}

//Need this or it will seg-fault at termination
	receivingthread->join();

	delete (receivingthread);
	delete (rtlsocket);

	return 0;
}
