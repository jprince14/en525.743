#include "sdr.h"
#include <stdbool.h>

bool opensdr(struct rtlsdrstruct* sdr, struct liquidobjects* dsp) {

	sdr->device_index = 0;

	int status;
	status = rtlsdr_open(&sdr->device, sdr->device_index);
	if (status < 0) {
		printf("Failed to open rtlsdr device %d.\n", sdr->device_index);
		exit(1);
	}

	tune_sdr(sdr, 2000000, dsp);
	tune_sdr(sdr, 97900000, dsp);

	rtlsdr_set_tuner_gain_mode(sdr->device, 0);
//	printf("Gain mode set= %d\n",retval);
//	rtlsdr_set_tuner_gain(sdr->device, 390);
//	printf("Set gain= %d\n",retval);
	rtlsdr_reset_buffer(sdr->device);

	return true;

}
void tune_sdr(struct rtlsdrstruct* sdr, uint32_t freq, struct liquidobjects* dsp) {
	rtlsdr_set_center_freq(sdr->device, freq);

}

void setsamplingrate_sdr(struct rtlsdrstruct* sdr, uint32_t freq, struct liquidobjects* dsp) {
	dsp->sample_rate_rf = freq;
	rtlsdr_set_sample_rate(sdr->device, freq);

}

void sdr_work(struct rtlsdrstruct* sdr) {
	int x = rtlsdr_read_sync(sdr->device, sdr->buffer, 10 * 1024, &sdr->receivesize);
	if (x < 0) {
		printf("Samples read: %d\n", sdr->receivesize);
		printf("Error reading from SDR\n");
//		exit(0);
	}
//	rtlsdr_read_async(sdr->device, rtlsdr_callback, s, 0, s->buf_len);
	printf("Samples read: %d\n", sdr->receivesize);

//	printf("sdr->receivesize = %d\n", sdr->receivesize);
	fwrite(sdr->buffer, sizeof(uint8_t), sdr->receivesize, sdr->filewrite);

}

void closesdr(struct rtlsdrstruct* sdr) {
	rtlsdr_close(sdr->device);
}

void set_cb_freq_sdr(struct rtlsdrstruct* sdr, int cbchannel, struct liquidobjects* dsp) {

	printf("channel passed in = %d", cbchannel);
	switch (cbchannel) {

	case 1:
		tune_sdr(sdr, CB_CHANNEL_1, dsp);
		break;
	case 2:
		tune_sdr(sdr, CB_CHANNEL_2, dsp);
		break;
	case 3:
		tune_sdr(sdr, CB_CHANNEL_3, dsp);
		break;
	case 4:
		tune_sdr(sdr, CB_CHANNEL_4, dsp);
		break;
	case 5:
		tune_sdr(sdr, CB_CHANNEL_5, dsp);
		break;
	case 6:
		tune_sdr(sdr, CB_CHANNEL_6, dsp);
		break;
	case 7:
		tune_sdr(sdr, CB_CHANNEL_7, dsp);
		break;
	case 8:
		tune_sdr(sdr, CB_CHANNEL_8, dsp);
		break;
	case 9:
		tune_sdr(sdr, CB_CHANNEL_9, dsp);
		break;
	case 10:
		tune_sdr(sdr, CB_CHANNEL_10, dsp);
		break;
	case 11:
		tune_sdr(sdr, CB_CHANNEL_11, dsp);
		break;
	case 12:
		tune_sdr(sdr, CB_CHANNEL_12, dsp);
		break;
	case 13:
		tune_sdr(sdr, CB_CHANNEL_13, dsp);
		break;
	case 14:
		tune_sdr(sdr, CB_CHANNEL_14, dsp);
		break;
	case 15:
		tune_sdr(sdr, CB_CHANNEL_15, dsp);
		break;
	case 16:
		tune_sdr(sdr, CB_CHANNEL_16, dsp);
		break;
	case 17:
		tune_sdr(sdr, CB_CHANNEL_17, dsp);
		break;
	case 18:
		tune_sdr(sdr, CB_CHANNEL_18, dsp);
		break;
	case 19:
		tune_sdr(sdr, CB_CHANNEL_19, dsp);
		break;
	case 20:
		tune_sdr(sdr, CB_CHANNEL_20, dsp);
		break;
	case 21:
		tune_sdr(sdr, CB_CHANNEL_21, dsp);
		break;
	case 22:
		tune_sdr(sdr, CB_CHANNEL_22, dsp);
		break;
	case 23:
		tune_sdr(sdr, CB_CHANNEL_23, dsp);
		break;
	case 24:
		tune_sdr(sdr, CB_CHANNEL_24, dsp);
		break;
	case 25:
		tune_sdr(sdr, CB_CHANNEL_25, dsp);
		break;
	case 26:
		tune_sdr(sdr, CB_CHANNEL_26, dsp);
		break;
	case 27:
		tune_sdr(sdr, CB_CHANNEL_27, dsp);
		break;
	case 28:
		tune_sdr(sdr, CB_CHANNEL_28, dsp);
		break;
	case 29:
		tune_sdr(sdr, CB_CHANNEL_29, dsp);
		break;
	case 30:
		tune_sdr(sdr, CB_CHANNEL_30, dsp);
		break;
	case 31:
		tune_sdr(sdr, CB_CHANNEL_31, dsp);
		break;
	case 32:
		tune_sdr(sdr, CB_CHANNEL_32, dsp);
		break;
	case 33:
		tune_sdr(sdr, CB_CHANNEL_33, dsp);
		break;
	case 34:
		tune_sdr(sdr, CB_CHANNEL_34, dsp);
		break;
	case 35:
		tune_sdr(sdr, CB_CHANNEL_35, dsp);
		break;
	case 36:
		tune_sdr(sdr, CB_CHANNEL_36, dsp);
		break;
	case 37:
		tune_sdr(sdr, CB_CHANNEL_37, dsp);
		break;
	case 38:
		tune_sdr(sdr, CB_CHANNEL_38, dsp);
		break;
	case 39:
		tune_sdr(sdr, CB_CHANNEL_39, dsp);
		break;
	case 40:
		tune_sdr(sdr, CB_CHANNEL_40, dsp);
		break;
	}

}
