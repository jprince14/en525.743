#ifndef DSP_H
#define DSP_H

// First run g++ -c -o dsp.cc.o dsp.cc


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <liquid/liquid.h>
#include <complex>
#include "structures.h"

#ifndef dspconstants
#define mono_FM 0
#define stereo_FM 1
#define cb_AM 2
#endif

struct dspobjects {
	iirfilt_crcf fm_filter;
	iirfilt_crcf am_filter;
	msresamp_rrrf resampler;
	freqdem fdem;
	ampmodem ampdemod;
	float buf_resamp[8192 * 20];    // resampler output buffer
	float buf_demod[10000];     // demodulator output buffer
	unsigned int nw_resamp;
	unsigned int buffercounter;
	uint32_t centerfreq;
	float sample_rate_rf; // input sample rate from RTL SDR
	float sample_rate_audio;   // audio sample rate
	float FM_cutoff_freq_rf;   // RF cut-off frequency
	float AM_cutoff_freq_rf;
//	FILE * fid_demod; //This file is only for testing purposes to write output to a file
//	FILE * filtered;
	int demodtype;
//	int copy_buffcounter;
};

struct demodulateddata demod_work(struct dspobjects* dsp, struct receivestruct inputstruct);

void initialize_dspobjects(struct dspobjects* dsp);

void demod_close(struct dspobjects* dsp);

#endif
