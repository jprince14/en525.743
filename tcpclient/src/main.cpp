//#include <strings.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>
#ifndef debug
#define debug 1 //1  = debug mode, 0 = normal mode
#endif

#include "tcpsocket.hpp"
#include <thread> // C++11 threading library - requires linking to pthread library
#include <fstream>

#include <rtl-sdr.h>
#include <math.h>
#include <complex.h>
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

void receivethread(tcpsocket* tcpsocket) {
	while (exitflag == false) {
//		printf("the thread is running\n");

		tcpsocket->receive(receivebuffer, sizeof(receivebuffer));
	}

}
/*
 struct demod_common {
 int demod_type; //0 for Fm, 1 for AM
 uint32_t center_freq;
 int inputrate;
 int outputrate;
 };

 struct amdemod {
 ampmodem demod;
 msresamp_crcf resamp1;
 float r1;
 float mi;

 };

 struct fmdemod {
 freqdem demod;
 float kf;
 msresamp_crcf resamp1;
 resamp_rrrf resamp2;
 float r1;
 float r2;

 };

 struct demod {
 struct fmdemod fm;
 struct amdemod am;

 struct demod_common common;

 int8_t inputbuffer[5000];
 int inputlength;

 int16_t outputbuffer[5000];
 int outputlength;

 };

 void demodam_initialize(demod demod) {
 demod.am.r1 = (float) demod.common.inputrate
 / (float) demod.common.outputrate;
 demod.am.mi = 0.9f;

 float fc = 0.0f;
 int supressed = 0;
 liquid_ampmodem_type t = LIQUID_AMPMODEM_DSB;

 demod.am.demod = ampmodem_create(demod.am.mi, fc, t, supressed);

 }*/
//void demodam_teardown(demod demod) {
//	ampmodem_destroy(demod.am.demod);
//	msresamp_crcf_destroy(demod.am.resamp1);
//}
//
//void demodam(demod demod) {
//	unsigned int nx = (demod.inputlength / 2);
//	unsigned int ny = ceil(demod.am.r1 * (float) nx);
//
//	float complex x[nx];
//	float complex y[ny];
//
//
//
//}
int main(int argc, char**argv) {
	thread *receivingthread;

	tcpsocket* rtlsocket = new tcpsocket;
	rtlsocket->assignipaddr("127.0.0.1");
	rtlsocket->assignport(1234);
	rtlsocket->createsocket();

#if debug
	printf("test\n");
#endif

	if (rtlsocket->opensocket() == true) {
		receivingthread = new thread(receivethread, rtlsocket);

//		int x = 0;
//
//		for (x = 0; x < 10000; x++) {
//			rtlsocket->receive(receivebuffer, sizeof(receivebuffer));
//
//		}

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
	delete (receivebuffer);

	return 0;
}
