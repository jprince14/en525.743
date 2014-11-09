struct liquidobjects
{
	iirfilt_crcf filter;
	msresamp_crcf resampler;
	freqdem fdem;
	float complex buf_resamp[10];    // resampler output buffer
	float buf_demod[10];     // demodulator output buffer
};

demod_work(struct tcp_socket rtl, struct liquidobjects dsp);
