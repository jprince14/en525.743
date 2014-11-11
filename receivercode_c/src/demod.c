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

		if (dsp->demodtype == mono_FM) {
			// filter result
			float complex y = 0;
			iirfilt_crcf_execute(dsp->fm_filter, x, &y);

			// run frequency demodulation
			freqdem_demodulate_block(dsp->fdem, &y, 1, dsp->buf_demod);
//		fwrite(&dsp->buf_demod, sizeof(float), 1, dsp->fid_demod);

// resample to 48 kHz (one input should produce either 0 or 1 output)
			dsp->nw_resamp = 0;
//this line below gives a warning but it works fine
			msresamp_rrrf_execute(dsp->resampler, dsp->buf_demod, 1, dsp->buf_resamp + dsp->buffercounter,
					&dsp->nw_resamp);

//		msresamp_crcf_execute(dsp->resampler, dsp->buf_demod, 1, dsp->buf_resamp + dsp->buffercounter, &dsp->nw_resamp);
//		printf("dsp->nw_resamp = %d\n", dsp->nw_resamp);
//		fwrite(dsp->buf_resamp + dsp->buffercounter, sizeof(float), dsp->nw_resamp, dsp->fid_demod);
			dsp->buffercounter += (dsp->nw_resamp);
		}

		if (dsp->demodtype == stereo_FM) {
#warning - come back here
		}
		if (dsp->demodtype == cb_AM) {
			float complex y_AM = 0;

			iirfilt_crcf_execute(dsp->am_filter, x, &y_AM);

			ampmodem_demodulate(dsp->ampdemod, y_AM, dsp->buf_demod);

			dsp->nw_resamp = 0;

			msresamp_rrrf_execute(dsp->resampler, dsp->buf_demod, 1, dsp->buf_resamp + dsp->buffercounter,
					&dsp->nw_resamp);
			dsp->buffercounter += (dsp->nw_resamp);

		}

	}
}

void initialize_dspobjects(struct liquidobjects* dsp) {
	dsp->sample_rate_rf = 2000e3; // input sample rate from RTL SDR
	dsp->sample_rate_audio = 48e3;   // audio sample rate

	dsp->FM_cutoff_freq_rf = 75e3;   // RF cut-off frequency

	dsp->AM_cutoff_freq_rf = 10e3;   // RF cut-off frequency

	dsp->demodtype = mono_FM; //setting the default demod type

	dsp->buffercounter = 0;
//create filter
	dsp->fm_filter = iirfilt_crcf_create_prototype(LIQUID_IIRDES_BUTTER,           // Butterworth filter
			LIQUID_IIRDES_LOWPASS,          // Low-pass design
			LIQUID_IIRDES_SOS,              // second-order sections format
			7,                              // 7th order
			dsp->FM_cutoff_freq_rf / dsp->sample_rate_rf,  // appropriate cut-off
			0,                              // centered at baseband
			1, 60);                         // ignored for Butterworth

	dsp->am_filter = iirfilt_crcf_create_prototype(LIQUID_IIRDES_BUTTER,           // Butterworth filter
			LIQUID_IIRDES_LOWPASS,          // Low-pass design
			LIQUID_IIRDES_SOS,              // second-order sections format
			7,                              // 7th order
			dsp->AM_cutoff_freq_rf / dsp->sample_rate_rf,  // appropriate cut-off
			0,                              // centered at baseband
			1, 60);

// create resampler
	float resampler_rate = dsp->sample_rate_audio / dsp->sample_rate_rf;
	float resampler_As = 60.0f;
//	dsp->resampler = msresamp_crcf_create(resampler_rate, resampler_As);
	dsp->resampler = msresamp_rrrf_create(resampler_rate, resampler_As);

//create demodulator
	float kf = 0.1f;        // modulation factor
	dsp->fdem = freqdem_create(kf);

	float mod_index = 0.1f;         // modulation index (bandwidth)
	float fc = 0.0f;                // AM carrier
	liquid_ampmodem_type type = LIQUID_AMPMODEM_USB;
	int suppressed_carrier = 0;     // suppress the carrier?
	dsp->ampdemod = ampmodem_create(mod_index, fc, type, LIQUID_AMPMODEM_DSB);

}

