#ifndef STRUCT_H
#define STRUCT_H

#include <liquid/liquid.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <lame/lame.h>

struct encoder {
	lame_t lame;
	unsigned char mp3_buffer[8192 * 21];
	unsigned int mp3buffsize;
	FILE * outfile; //This file is only for testing purposes to write output to a file

};

struct liquidobjects {
	iirfilt_crcf filter;
//	msresamp_crcf resampler;
	msresamp_rrrf resampler;
	freqdem fdem;
	float buf_resamp[8192 * 21];    // resampler output buffer
	float buf_demod[10];     // demodulator output buffer
	unsigned int nw_resamp;
	unsigned int buffercounter;
	float sample_rate_rf; // input sample rate from RTL SDR
	float sample_rate_audio;   // audio sample rate
	float cutoff_freq_rf;   // RF cut-off frequency
	FILE * fid_demod; //This file is only for testing purposes to write output to a file
};

struct command {
	unsigned char cmd;
	unsigned int param;
}__attribute__((packed));

struct tcp_socket {
	struct sockaddr_in servaddr;
	int sockfd;
	bool receiverexitflag;
	uint8_t buffer[1000];
	int receivesize;
};

#endif
