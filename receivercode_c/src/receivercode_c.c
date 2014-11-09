//#include <strings.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>
#ifndef debug
#define debug 1 //1  = debug mode, 0 = normal mode
#endif

#include "tcpsocket.h"
#include "demod.h"
#include "encoder.h"
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
#include <lame/lame.h>


#define Ampliture_Modulation 1;
#define Frequency_Modulation 0;

void* menufunction(void* ptr) {

	struct tcp_socket* sdr_socket = (struct tcp_socket*) ptr;

	printf("Welcome to Jeremy's EN525.743 Embedded Development Project\n");
	printf("\tEnter 1 to adjust the frequency of the SDR\n");
	printf("\tEnter 2 to adjust the sampling rate of the SDR\n");
	printf("\tEnter 3 to adjust the demodulator\n");
	printf("\tEnter 9 to exit\n");

	int x;
	while (scanf("%d", &x) != EOF) {
		//Adjust frequency
		if (x == 1) {
//TODO print out the frequency range of the tuner
			printf("Enter the desired tuning frequency (in Hz)\n");
			uint32_t freq;
			scanf("%d", &freq);
			set_freq(sdr_socket, freq);
		}

		// adjust sampling rate
		if (x == 2) {
//TODO print out the potential sampling rates of the tuner
			printf("Enter the desired sampling rate (in Hz)\n");
			uint32_t samplingrate;
			scanf("%d", &samplingrate);
			set_sample_rate(sdr_socket, samplingrate);
		}
		//Exit
		if (x == 9) {

			printf("Exit signal received\n");
			sdr_socket->receiverexitflag = true;
			break;
		}
	}

	return NULL;
}

int main(int argc, char**argv) {

	pthread_t menuthread;

	struct tcp_socket* rtlsdr;
	rtlsdr = malloc(sizeof(struct tcp_socket));
	struct liquidobjects* processingstruct;
	processingstruct = malloc(sizeof(struct liquidobjects));
	struct encoder* mp3encoder;
	mp3encoder = malloc(sizeof(struct encoder));


	tcp_setaddress(rtlsdr, "127.0.0.1");
	tcp_setport(rtlsdr, 1234);
	rtlsdr->receiverexitflag = false;
	tcp_createsocket(rtlsdr);
	initialize_dspobjects(processingstruct);
	initialize_encoder(mp3encoder);

	processingstruct->fid_demod = fopen("fmdemod_demod.bin", "wb");
	mp3encoder->outfile = fopen("mp3output.mp3", "wb");


	if (tcp_opensocket(rtlsdr) == 0) {

		if (pthread_create(&menuthread, NULL, menufunction, rtlsdr) == 0) {

			while (rtlsdr->receiverexitflag == false) {
				tcp_receive(rtlsdr);
				demod_work(rtlsdr, processingstruct);
				encoder_work(processingstruct, mp3encoder);
				//encode audio - format is 32bit little endian float
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
	closesocket(rtlsdr);

	free(rtlsdr);
	free(processingstruct);
	free(mp3encoder);

	return 0;
}

