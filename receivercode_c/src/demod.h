#ifndef DEMOD_H
#define DEMOD_H

#include "tcpsocket.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <liquid/liquid.h>
#include <complex.h>

struct liquidobjects {
	iirfilt_crcf filter;
	msresamp_crcf resampler;
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

void demod_work(struct tcp_socket* rtl, struct liquidobjects* dsp);
void initialize_dspobjects(struct liquidobjects* dsp);

//void demod_work_testing(struct tcp_socket* rtl, struct liquidobjects* dsp, struct encoder* lame_obj);

#endif
