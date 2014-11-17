#ifndef STRUCT_H
#define STRUCT_H

#include <liquid/liquid.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <lame/lame.h>
#include <curl/curl.h>
#include <alsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtl-sdr.h>


#define mono_FM 0
#define stereo_FM 1
#define cb_AM 2

#define CB_CHANNEL_1 	26965000 //Hz
#define CB_CHANNEL_2 	26975000 //Hz
#define CB_CHANNEL_3 	26985000 //Hz
#define CB_CHANNEL_4 	27005000 //Hz
#define CB_CHANNEL_5 	27015000 //Hz
#define CB_CHANNEL_6 	27025000 //Hz
#define CB_CHANNEL_7 	27035000 //Hz
#define CB_CHANNEL_8 	27055000 //Hz
#define CB_CHANNEL_9 	27065000 //Hz
#define CB_CHANNEL_10 	27075000 //Hz
#define CB_CHANNEL_11 	27085000 //Hz
#define CB_CHANNEL_12 	27105000 //Hz
#define CB_CHANNEL_13 	27115000 //Hz
#define CB_CHANNEL_14 	27125000 //Hz
#define CB_CHANNEL_15 	27135000 //Hz
#define CB_CHANNEL_16 	27155000 //Hz
#define CB_CHANNEL_17 	27165000 //Hz
#define CB_CHANNEL_18 	27175000 //Hz
#define CB_CHANNEL_19 	27185000 //Hz
#define CB_CHANNEL_20 	27205000 //Hz
#define CB_CHANNEL_21 	27215000 //Hz
#define CB_CHANNEL_22 	27225000 //Hz
#define CB_CHANNEL_23 	27255000 //Hz
#define CB_CHANNEL_24 	27235000 //Hz
#define CB_CHANNEL_25 	27245000 //Hz
#define CB_CHANNEL_26 	27265000 //Hz
#define CB_CHANNEL_27 	27275000 //Hz
#define CB_CHANNEL_28 	27285000 //Hz
#define CB_CHANNEL_29 	27295000 //Hz
#define CB_CHANNEL_30 	27305000 //Hz
#define CB_CHANNEL_31 	27315000 //Hz
#define CB_CHANNEL_32 	27325000 //Hz
#define CB_CHANNEL_33 	27335000 //Hz
#define CB_CHANNEL_34 	27345000 //Hz
#define CB_CHANNEL_35 	27355000 //Hz
#define CB_CHANNEL_36 	27365000 //Hz
#define CB_CHANNEL_37 	27375000 //Hz
#define CB_CHANNEL_38 	27385000 //Hz
#define CB_CHANNEL_39 	27395000 //Hz
#define CB_CHANNEL_40 	27405000 //Hz

int cbradiofreqs[40];

struct encoder {
	lame_t lame;
	unsigned char mp3_buffer[8192 * 21];
	unsigned int mp3buffsize;
	FILE * outfile; //This file is only for testing purposes to write output to a file

	//Curl variables
	CURL *curl;
	CURLcode res;

};

struct liquidobjects {
	iirfilt_crcf fm_filter;
	iirfilt_crcf am_filter;
//	msresamp_crcf resampler;
	msresamp_rrrf resampler;
	freqdem fdem;
	ampmodem ampdemod;
	float buf_resamp[8192 * 20];    // resampler output buffer
//	float complex complexbuffer[5120];
	float buf_demod[1000];     // demodulator output buffer
	unsigned int nw_resamp;
	unsigned int buffercounter;
	float sample_rate_rf; // input sample rate from RTL SDR
	float sample_rate_audio;   // audio sample rate
	float FM_cutoff_freq_rf;   // RF cut-off frequency
	float AM_cutoff_freq_rf;
	FILE * fid_demod; //This file is only for testing purposes to write output to a file
	int demodtype;
	int copy_buffcounter;
};

struct command {
	unsigned char cmd;
	unsigned int param;
}__attribute__((packed));

struct tcp_socket {
	struct sockaddr_in servaddr;
	struct sockaddr_in cli_addr;
	int sockfd;
	bool receiverexitflag;
	int receivesize;
    socklen_t clilen;
    int newsockfd;
    uint32_t receivebuffer[100];
};

struct control {
	struct rtlsdrstruct* sdrstruct;
	struct liquidobjects* demodstruct;
	struct tcp_socket* controlsocket;
};

struct udp_socket {
	struct sockaddr_in servaddr;
	int sockfd;
};

struct audiostruct {
	snd_pcm_t *playback_handle;
	snd_pcm_hw_params_t *hw_params;
	int audiobuffer_size;
	int minaudiobuffersize;
	float audiobuffer[500];
};


struct rtlsdrstruct
{
// the librtlsdr device object and the index used to look it up
rtlsdr_dev_t * device;
int device_index;
// called whenever samples are received from the RTL
//rtl_execute_callback execute_callback;
//void * execute_ctx;
// buffer for samples received from the RTL
uint8_t buffer[12*1024];
int receivesize;
uint32_t sample_rate;
bool receiverexitflag;
FILE * filewrite; //This file is only for testing purposes to write output to a file

};

#endif
