//#include <strings.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>
#ifndef debug
#define debug 1 //1  = debug mode, 0 = normal mode
#endif

#include "Socketclass.hpp"
#include <pthread.h>
#include <fstream>

#include <rtl-sdr.h>
#include <math.h>
#include <complex>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <liquid/liquid.h> // Liquid DSP Library http://liquidsdr.org/
#define Ampliture_Modulation 1;
#define Frequency_Modulation 0;
using namespace std;

//my demod is based heavily on this github repo
//https://github.com/alxlit/rtl-and-liquid

//GNU Radio code for interacting with the SDR
//http://git.osmocom.org/gr-osmosdr/tree/lib/rtl_tcp
//example command: rtl_tcp -a 127.0.0.1 -p 1234

uint8_t* receivebuffer = new uint8_t[200000];
bool exitflag = false;

//bool exitflag = false;
//
//void receivethread(tcpsocket* tcpsocket) {
//	while (exitflag == false) {
////		printf("the thread is running\n");
//
//		tcpsocket->receive(receivebuffer, sizeof(receivebuffer));
//	}
//
//}

void* menufunction(void* ptr) {

	tcpsocket* socketptr = (tcpsocket*) ptr;

#warning - make this the secondary t
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
			socketptr->set_freq(freq);
		}

		// adjust sampling rate
		if (x == 2) {
//TODO print out the potential sampling rates of the tuner
			std::cout << "Enter the desired sampling rate (in Hz)\n";
			uint32_t samplingrate;
			std::cin >> samplingrate;
			socketptr->set_sample_rate(samplingrate);
		}

		//adjust modulation type
		if (x == 3) {
			//TODO: Come back here - set the modulation type
		}

		//Exit
		if (x == 9) {

			std::cout << "Exit signal received\n";
			exitflag = true;
			socketptr->closesocket();
			break;
		}
	}

	return NULL;
}

int main(int argc, char**argv) {

	pthread_t menuthread;

	tcpsocket* rtlsocket = new tcpsocket;
	rtlsocket->assignipaddr("127.0.0.1");
	rtlsocket->assignport(1234);
	rtlsocket->createsocket();

#if debug
	printf("test\n");
#endif

	if (rtlsocket->opensocket() == true) {

		if (pthread_create(&menuthread, NULL, menufunction, rtlsocket) == 0) {

			while (exitflag == false) {
				rtlsocket->receive(receivebuffer, sizeof(receivebuffer));
			}

			pthread_join(menuthread, NULL);

//TODO Update so that the user can enter the IP and Port through the GUI
		} else {
			printf("error unable to open thread\n");
		}
	} else {
		std::cout << "Unable to connect to socket, program exiting\n";
		exit(0);
	}

	delete (rtlsocket);
	delete (receivebuffer);

	return 0;
}

