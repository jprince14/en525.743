//#include <strings.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>
#ifndef debug
#define debug 1 //1  = debug mode, 0 = normal mode
#endif

#include "tcpsocket.h"
#include <pthread.h>

#include <rtl-sdr.h>
#include <math.h>
#include <complex.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <liquid/liquid.h> // Liquid DSP Library http://liquidsdr.org/
#define Ampliture_Modulation 1;
#define Frequency_Modulation 0;

void* menufunction(void* ptr) {

	struct tcp_socket* sdrsocket = (struct tcp_socket*) ptr;

#warning - make this the secondary t
	printf("Welcome to Jeremy's EN525.743 Embedded Development Project\n");
	printf("\tEnter 1 to adjust the frequency of the SDR\n");
	printf("\tEnter 2 to adjust the sampling rate of the SDR\n");
	printf("\tEnter 3 to adjust the demodulator\n");
	printf("\tEnter 9 to exit\n");

	int *x;
	while (fgets(x, sizeof(int), stdin) != NULL) {
		//Adjust frequency
		if (x == 1) {
//TODO print out the frequency range of the tuner
			printf("Enter the desired tuning frequency (in Hz)\n");
			uint32_t freq;
			std
			::cin >> freq;
			socketptr->set_freq(sdrsocket, freq);
		}

		// adjust sampling rate
		if (x == 2) {
//TODO print out the potential sampling rates of the tuner
			printf("Enter the desired sampling rate (in Hz)\n");
			uint32_t samplingrate;
			std
			::cin >> samplingrate;
			socketptr->set_sample_rate(samplingrate);
		}

		//adjust modulation type
		if (x == 3) {
			//TODO: Come back here - set the modulation type
		}

		//Exit
		if (x == 9) {

			printf("Exit signal received\n");
			sdrsocket.receiverexitflag = true;
			socketptr->closesocket();
			break;
		}
	}

	return NULL;
}

int main(int argc, char**argv) {

	pthread_t menuthread;

	struct tcp_socket rtlsdr;
	tcp_setaddress(rtlsdr, "127.0.0.1");
	tcp_setport(rtlsdr, 1234);
	tcp_createsocket(rtlsdr);
	rtlsdr.receiverexitflag = false;

#if debug
	printf("test\n");
#endif

	if (tcpopensocket(rtlsdr) == true) {

		if (pthread_create(&menuthread, NULL, menufunction, (void *) &rtlsdr) == 0) {

			while (rtlsdr.receiverexitflag == false) {
//				rtlsocket->receive(receivebuffer, sizeof(receivebuffer));
			}

			pthread_join(menuthread, NULL);

//TODO Update so that the user can enter the IP and Port through the GUI
		} else {
			printf("error unable to open thread\n");
		}
	} else {
		printf("Unable to connect to socket, program exiting\n");
		exit(0);
	}

	return 0;
}

