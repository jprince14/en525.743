#include "demod.h"

void demod_work(struct tcp_socket* rtl, struct liquidobjects* dsp) {
	int _I;
	int _Q;
	int x;
	for (x = 0; x < (rtl->receivesize / 2); x++) {

		_I = rtl->buffer[2 * x];

		_Q = rtl->buffer[((2 * x) + 1)];

		// convert to float complex type
		float complex x = (float) (_I - 127.0) / 128.0f + (float) (_Q - 127.0) / 128.0f * _Complex_I;

		// filter result
		float complex y = 0;
		iirfilt_crcf_execute(dsp->filter, x, &y);

		// run frequency demodulation
		freqdem_demodulate_block(dsp->fdem, &y, 1, dsp->buf_demod);
//		fwrite(&dsp->buf_demod, sizeof(float), 1, dsp->fid_demod);

// resample to 48 kHz (one input should produce either 0 or 1 output)
		dsp->nw_resamp = 0;
		//this line below gives a warning but it works fine
		msresamp_crcf_execute(dsp->resampler, dsp->buf_demod, 1, dsp->buf_resamp + dsp->buffercounter, &dsp->nw_resamp);
//		printf("dsp->nw_resamp = %d\n", dsp->nw_resamp);
		fwrite(dsp->buf_resamp + dsp->buffercounter, sizeof(float), dsp->nw_resamp, dsp->fid_demod);
		dsp->buffercounter += (dsp->nw_resamp);

	}
}

void initialize_dspobjects(struct liquidobjects* dsp) {
	float sample_rate_rf = 2000e3; // input sample rate from RTL SDR - this works when i put it through a resampler of decimation 10
	float sample_rate_audio = 16e3;   // audio sample rate
	float cutoff_freq_rf = 75e3;   // RF cut-off frequency
	dsp->buffercounter = 0;
	//create filter
	dsp->filter = iirfilt_crcf_create_prototype(LIQUID_IIRDES_BUTTER,           // Butterworth filter
			LIQUID_IIRDES_LOWPASS,          // Low-pass design
			LIQUID_IIRDES_SOS,              // second-order sections format
			7,                              // 7th order
			cutoff_freq_rf / sample_rate_rf,  // appropriate cut-off
			0,                              // centered at baseband
			1, 60);                         // ignored for Butterworth

	// create resampler
	float resampler_rate = sample_rate_audio / sample_rate_rf;
	float resampler_As = 60.0f;
	dsp->resampler = msresamp_crcf_create(resampler_rate, resampler_As);

	//create demodulator
	float kf = 0.1f;        // modulation factor
	dsp->fdem = freqdem_create(kf);
}

//void demod_work_testing(struct tcp_socket* rtl, struct liquidobjects* dsp) {
//	int _I;
//	int _Q;
//	int x;
//	for (x = 0; x < (rtl->receivesize / 2); x++) {
//
//		_I = rtl->buffer[2 * x];
//
//		_Q = rtl->buffer[((2 * x) + 1)];
//
//		// convert to float complex type
//		float complex x = (float) (_I - 127.0) / 128.0f + (float) (_Q - 127.0) / 128.0f * _Complex_I;
//
//		// filter result
//		float complex y = 0;
//		iirfilt_crcf_execute(dsp->filter, x, &y);
//
//		// run frequency demodulation
//		freqdem_demodulate_block(dsp->fdem, &y, 1, dsp->buf_demod);
////		fwrite(&dsp->buf_demod, sizeof(float), 1, dsp->fid_demod);
//
//// resample to 48 kHz (one input should produce either 0 or 1 output)
//		dsp->nw_resamp = 0;
//		//this line below gives a warning but it works fine
//		msresamp_crcf_execute(dsp->resampler, dsp->buf_demod, 1, dsp->buf_resamp, &dsp->nw_resamp);
////		printf("dsp->nw_resamp = %d\n", dsp->nw_resamp);
//
//		encoder_work_2(dsp,lame_obj);
//
//
////		fwrite(dsp->buf_resamp + dsp->buffercounter, sizeof(float), dsp->nw_resamp, dsp->fid_demod);
////		dsp->buffercounter += (dsp->nw_resamp);
//
//	}
//}
