#ifndef DEMOD_H
#define DEMOD_H

#include "tcpsocket.h"
#include "demod.h"
#include <math.h>
#include <liquid/liquid.h>
#include <complex.h>


struct liquidobjects {
	iirfilt_crcf filter;
	msresamp_crcf resampler;
	freqdem fdem;
	float buf_resamp[50];    // resampler output buffer
	float buf_demod[10];     // demodulator output buffer
	unsigned int nw_resamp;
	unsigned int buffercounter;
	FILE * fid_demod; //This file is only for testing purposes to write output to a file
};

void demod_work(struct tcp_socket* rtl, struct liquidobjects* dsp);
void initialize_dspobjects(struct liquidobjects* dsp);

#endif
