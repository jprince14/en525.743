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
#include "structures.h"

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

	struct control* sdr_control = (struct control*) ptr;

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
			set_freq(sdr_control->socketstruct, freq);
		}

		// adjust sampling rate
		if (x == 2) {
//TODO print out the potential sampling rates of the tuner
			printf("Enter the desired sampling rate (in Hz)\n");
			uint32_t samplingrate;
			scanf("%d", &samplingrate);
			set_sample_rate(sdr_control->socketstruct, samplingrate);
		}
		if (x == 3) {
			int fmoption;
			printf("Demodulation options:\n1:FM-Mono(default)\n2:FM-Stereo\n3:AM-(CB Radio)\n");
			scanf("%d", &fmoption);

			if (fmoption == 1) {
				if (sdr_control->demodstruct->demodtype == mono_FM) {
					printf("Demod type is already set to FM-mono\n");
				} else {
					printf("Enter the desired tuning frequency (in Hz)\n");
					uint32_t freq;
					scanf("%d", &freq);
					set_freq(sdr_control->socketstruct, freq);
					sdr_control->demodstruct->demodtype = mono_FM;
					sdr_control->demodstruct->buffercounter = 0;
				}
			} else if (fmoption == 2) {
				if (sdr_control->demodstruct->demodtype == stereo_FM) {
					printf("Demod type is already set to FM-stereo\n");
				} else {
					printf("Enter the desired tuning frequency (in Hz)\n");
					uint32_t freq;
					scanf("%d", &freq);
					set_freq(sdr_control->socketstruct, freq);
					sdr_control->demodstruct->demodtype = stereo_FM;
					sdr_control->demodstruct->buffercounter = 0;
				}
			} else if (fmoption == 3) {
				if (sdr_control->demodstruct->demodtype == cb_AM) {
					printf("Demod type is already set to AM (CB)\n");
				} else {
					int cbchannel;
					printf("Select CB Radio Channel - select 1 - 40\n");
					scanf("%d", &cbchannel);
					set_cb_freq(sdr_control->socketstruct, cbchannel);

					sdr_control->demodstruct->demodtype = cb_AM;
					sdr_control->demodstruct->buffercounter = 0;
				}
			}
		}

		//CB Channel Menu
		if (x == 4) {
			int cbchannel;
			printf("Select CB Radio Channel - select 1 - 40\n");
			scanf("%d", &cbchannel);
			set_cb_freq(sdr_control->socketstruct, cbchannel);
		}

		//Exit
		if (x == 9) {

			printf("Exit signal received\n");
			sdr_control->socketstruct->receiverexitflag = true;
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

//Initialize the control structure
	struct control* controlstruct;
	controlstruct = malloc(sizeof(struct control));
	controlstruct->demodstruct = processingstruct;
	controlstruct->socketstruct = rtlsdr;

	tcp_setaddress(rtlsdr, "127.0.0.1");
	tcp_setport(rtlsdr, 1234);
	rtlsdr->receiverexitflag = false;
	tcp_createsocket(rtlsdr);
	initialize_dspobjects(processingstruct);
	initialize_encoder(processingstruct, mp3encoder);
	initializecurl(mp3encoder);

	processingstruct->fid_demod = fopen("fmdemod_demod.bin", "wb");
	mp3encoder->outfile = fopen("mp3output.mp3", "wb");

	if (tcp_opensocket(rtlsdr) == 0) {

		if (pthread_create(&menuthread, NULL, menufunction, controlstruct) == 0) {

			while (rtlsdr->receiverexitflag == false) {
				tcp_receive(rtlsdr);
				demod_work(rtlsdr, processingstruct);
				encoder_work(processingstruct, mp3encoder);
			}
			encoder_flush(rtlsdr, processingstruct);

			pthread_join(menuthread, NULL);

//TODO Update so that the user can enter the IP and Port through the GUI
		} else {
			printf("error unable to open thread\n");
		}
	} else {
		printf("Unable to connect to socket, program exiting\n");
		exit(0);
	}

	//clean up
	tcp_closesocket(rtlsdr);
	demod_close(processingstruct);
	close_encoderojects(mp3encoder);
	fclose(processingstruct->fid_demod);
	fclose(mp3encoder->outfile);
	free(controlstruct);
	free(rtlsdr);
	free(processingstruct);
	free(mp3encoder);

	return 0;
}

