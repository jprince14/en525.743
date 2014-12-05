//#include <strings.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>

#include "sdr.h"
#include "audio.h"
#include "tcpsocket.h"
#include "udpsocket.h"
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

void* c2_socketcontrol(void* ptr) {
	struct control* sdr_control = (struct control*) ptr;

	// do I need to open before listen?
	if (tcp_opensocket(sdr_control->controlsocket) == 0) {
		printf("tcp socket opened\n");
//		while (sdr_control->sdrstruct->receiverexitflag == false) {
//		printf("receive loop\n");
		tcp_listen(sdr_control->controlsocket, sdr_control->sdrstruct, sdr_control->demodstruct);
//		}

//		tcp_closesocket(sdr_control->controlsocket);
	} else {
		printf("ERROR: Unable to open command control socket\n");
	}
//	return NULL;
	pthread_exit(NULL);

}

void* menufunction(void* ptr) {

	struct control* sdr_control = (struct control*) ptr;

	printf("Welcome to Jeremy's EN525.743 Embedded Development Project\n");
	printf("\tEnter 1 to adjust the frequency of the SDR\n");
	printf("\tEnter 2 to adjust the change between sending IQ data and audio\n");
	printf("\tEnter 3 to adjust the demodulator\n");
	printf("\tEnter 4 to adjust the CB Channel\n");
	printf("\tEnter 9 to exit\n");

	int x;
	while (scanf("%d", &x) != EOF) {
		//Adjust frequency
		if (x == 1) {
//TODO print out the frequency range of the tuner
			printf("Enter the desired tuning frequency (in Hz)\n");
			uint32_t freq;
			scanf("%d", &freq);
			tune_sdr(sdr_control->sdrstruct, freq, sdr_control->demodstruct);
		}

		// adjust sampling rate
		if (x == 2) {

			printf("Enter 1 to send IQ Data and 2 to sent Audio\n");
			int dataoption;

			scanf("%d", &dataoption);

			if (dataoption == 1) {
				pthread_mutex_lock(&sdr_control->sdrstruct->sdrlock);
				//send the raw IQ data
				sdr_control->sdrstruct->sendaudio = false;
				pthread_mutex_lock(&sdr_control->sdrstruct->sdrlock);

			} else if (dataoption == 2) {

				pthread_mutex_lock(&sdr_control->sdrstruct->sdrlock);
				//send the raw IQ data
				sdr_control->sdrstruct->sendaudio = true;
				pthread_mutex_lock(&sdr_control->sdrstruct->sdrlock);

			}
		}
		if (x == 3) {
			int fmoption;
			printf("Demodulation options:\n1:FM-Mono(default)\n3:AM-(CB Radio)\n");
			scanf("%d", &fmoption);

			if (fmoption == 1) {
				if (sdr_control->demodstruct->demodtype == mono_FM) {
					printf("Demod type is already set to FM-mono\n");
				} else {
					printf("Enter the desired tuning frequency (in Hz)\n");
					uint32_t freq;
					scanf("%d", &freq);
					tune_sdr(sdr_control->sdrstruct, freq, sdr_control->demodstruct);
					sdr_control->demodstruct->demodtype = mono_FM;
					sdr_control->demodstruct->buffercounter = 0;
				}
//			} else if (fmoption == 2) {
//				if (sdr_control->demodstruct->demodtype == stereo_FM) {
//					printf("Demod type is already set to FM-stereo\n");
//				} else {
//					printf("Enter the desired tuning frequency (in Hz)\n");
//					uint32_t freq;
//					scanf("%d", &freq);
//					tune_sdr(sdr_control->sdrstruct, freq, sdr_control->demodstruct);
//					sdr_control->demodstruct->demodtype = stereo_FM;
//					sdr_control->demodstruct->buffercounter = 0;
//				}
			} else if (fmoption == 3) {
				if (sdr_control->demodstruct->demodtype == cb_AM) {
					printf("Demod type is already set to AM (CB)\n");
				} else {
					int cbchannel;
					printf("Select CB Radio Channel - select 1 - 40\n");
					scanf("%d", &cbchannel);
					set_cb_freq_sdr(sdr_control->sdrstruct, cbchannel, sdr_control->demodstruct);

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
			set_cb_freq_sdr(sdr_control->sdrstruct, cbchannel, sdr_control->demodstruct);
		}

		//Exit
		if (x == 9) {

			printf("Exit signal received\n");
			sdr_control->sdrstruct->receiverexitflag = true;
			break;
		} else {
			printf("Invalid command received\n");
		}

		printf("\n\tEnter 1 to adjust the frequency of the SDR\n");
		printf("\tEnter 2 to adjust the sampling rate of the SDR\n");
		printf("\tEnter 3 to adjust the demodulator\n");
		printf("\tEnter 4 to adjust the CB Channel\n");
		printf("\tEnter 9 to exit\n");

	}

//	return NULL;
	pthread_exit(NULL);

}

int main(int argc, char**argv) {

	if (argc != 4) {
		printf("Error 3 arguments required\nProper Usage: ./server clientip commandcontrolport dataport\n");
		exit(0);
	}

#if WRITEFILES == 1
	int x;
	for (x = 1; x < 4; x++) {
		printf("arg %d = %s\n", x, argv[x]);
	}
#endif

	pthread_t menuthread;

	pthread_t commandtcpsocket;

	struct rtlsdrstruct* rtlsdr;
	rtlsdr = malloc(sizeof(struct rtlsdrstruct));

	struct liquidobjects* processingstruct;
	processingstruct = malloc(sizeof(struct liquidobjects));

	struct udp_socket* transmitter_socket;
	transmitter_socket = malloc(sizeof(struct udp_socket));

#if MP3 == 0
	struct encoder* mp3encoder;
	mp3encoder = malloc(sizeof(struct encoder));
#endif

#if AUDIO == 0
	struct audiostruct* audioobject;
	audioobject = malloc(sizeof(struct audiostruct));
#endif

#if TESTSOCKET == 0
	struct udp_socket* testsocket;
	testsocket = malloc(sizeof(struct udp_socket));
#endif

	struct tcp_socket* c2socket;
	c2socket = malloc(sizeof(struct tcp_socket));

//Initialize the control structure
	struct control* controlstruct;
	controlstruct = malloc(sizeof(struct control));
	controlstruct->demodstruct = processingstruct;
	controlstruct->sdrstruct = rtlsdr;
	controlstruct->controlsocket = c2socket;

	tcp_setaddress(c2socket, argv[1]);
	tcp_setport(c2socket, atoi(argv[2]));
	tcp_createsocket(c2socket);

	udp_setaddress(transmitter_socket, argv[1]);
	udp_setport(transmitter_socket, atoi(argv[3]));
	udp_createsocket(transmitter_socket);

	if (pthread_mutex_init(&rtlsdr->sdrlock, NULL) != 0) {
		printf("ERROR: Unable to open sdrlock\n");
	}

	rtlsdr->receiverexitflag = false;
	rtlsdr->sendaudio = true;
	initialize_dspobjects(processingstruct);

#if AUDIO == 0
	initializeaudio(audioobject);
#endif

#if WRITEFILES == 1
	processingstruct->fid_demod = fopen("fmdemod_demod.bin", "wb");
	processingstruct->filtered = fopen("filtered.bin", "wb");
#endif

#if MP3 == 0 && WRITEFILES == 1
	mp3encoder->outfile = fopen("mp3output.mp3", "wb");
#endif

#if MP3 == 0
	initialize_encoder(processingstruct, mp3encoder);
#endif

#if SDR_WRITE == 0
	rtlsdr->filewrite = fopen("sdroutput.bin", "wb");
#endif

#if TESTSOCKET == 0
	udp_setaddress(testsocket, "127.0.0.1");
	udp_setport(testsocket, 9999);
	udp_createsocket(testsocket);

#endif

	if (opensdr(rtlsdr, processingstruct) == true) {
		if (pthread_create(&menuthread, NULL, menufunction, controlstruct) == 0) {
			if (pthread_create(&commandtcpsocket, NULL, c2_socketcontrol, controlstruct) == 0) {

				while (rtlsdr->receiverexitflag == false) {

					sdr_work(rtlsdr);

#if TESTSOCKET == 0
					udp_senddata_test(testsocket, rtlsdr);
#endif

					pthread_mutex_lock(&rtlsdr->sdrlock);

					if (rtlsdr->sendaudio == true) {
						demod_work(rtlsdr, processingstruct);
						udp_senddata_float(transmitter_socket, processingstruct);
					} else {
						//send the raw IQ data
						udp_senddata_IQ(transmitter_socket, rtlsdr);
					}
					pthread_mutex_unlock(&rtlsdr->sdrlock);

#if AUDIO == 0
					playaudio(processingstruct, audioobject);
#endif

#if MP3 == 0
					encoder_work(processingstruct, mp3encoder);
#endif

				}
#if MP3 == 0
				encoder_flush(processingstruct, mp3encoder);
#endif
				pthread_join(menuthread, NULL);
				pthread_join(commandtcpsocket, NULL);

//TODO Update so that the user can enter the IP and Port through the GUI
			} else {
				printf("error unable to open tcpsocket thread\n");

			}

		} else {
			printf("error unable to open menu thread\n");
		}
//		} else {
//			printf("Unable to open UDP socket for transmitting the demodulated and encoded audio from the SDR\n");
//		}
	} else {
		printf("Unable to connect to the TCP socket for receiving data from the SDR, program exiting\n");
		exit(0);
	}

	//clean up
	closesdr(rtlsdr);
	demod_close(processingstruct);

#if SDR_WRITE == 0
	fclose(rtlsdr->filewrite);
#endif

#if WRITEFILES == 1
	fclose(processingstruct->fid_demod);
	fclose(processingstruct->filtered);
#endif

#if MP3 == 0 && WRITEFILES == 1
	fclose(mp3encoder->outfile);
#endif

#if MP3 == 0
	close_encoderojects(mp3encoder);
#endif

	closeudpsocket(transmitter_socket);

#if AUDIO == 0
	closeaudio(audioobject);
	free(audioobject);
#endif

	pthread_mutex_destroy(&rtlsdr->sdrlock);

	free(controlstruct);
	free(rtlsdr);
	free(processingstruct);

#if TESTSOCKET == 0
	closeudpsocket(testsocket);
	free(testsocket);
#endif

#if MP3 == 0
	free(mp3encoder);
#endif
	free(transmitter_socket);

	return 0;
}

