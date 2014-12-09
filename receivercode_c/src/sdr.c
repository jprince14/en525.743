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

//	rtlsdr_set_center_freq(sdr->device, 97900000);
//	rtlsdr_set_sample_rate(sdr->device, 2000000);
	tune_sdr(sdr, 97900000, dsp);
	setsamplingrate_sdr(sdr, 2000000, dsp);

	rtlsdr_set_tuner_gain_mode(sdr->device, 0);
//	printf("Gain mode set= %d\n",retval);
//	rtlsdr_set_tuner_gain(sdr->device, 390);
//	printf("Set gain= %d\n",retval);
	rtlsdr_reset_buffer(sdr->device);

	return true;

}
void tune_sdr(struct rtlsdrstruct* sdr, uint32_t freq, struct liquidobjects* dsp) {
	rtlsdr_set_center_freq(sdr->device, freq);
	dsp->centerfreq = freq;

}

void setsamplingrate_sdr(struct rtlsdrstruct* sdr, uint32_t freq, struct liquidobjects* dsp) {
	rtlsdr_set_sample_rate(sdr->device, freq);
	dsp->sample_rate_rf = freq;
	printf("Sampling rate set to %d\n", rtlsdr_get_sample_rate(sdr->device));
}

void sdr_work(struct rtlsdrstruct* sdr) {
	//if the size of the data read off the SDR is too large then the demod function
	//takes too long which makes the output audio low quality
	int x = rtlsdr_read_sync(sdr->device, sdr->buffer, 1 * 1024, &sdr->receivesize);
//	usleep(1000);
	if (x < 0) {
		printf("Samples read: %d\n", sdr->receivesize);
		printf("Error reading from SDR\n");
		exit(0);
	}
//	if (sdr->receivesize == 0) {
//		printf("ERROR reading data off SDR, # Samples read: %d\n", sdr->receivesize);
//	}

#if SDR_WRITE == 0
	printf("sdr->receivesize = %d\n", sdr->receivesize);
//	printf("Sampling rate set to %d\n", rtlsdr_get_sample_rate(sdr->device));
	fwrite(sdr->buffer, sizeof(uint8_t), sdr->receivesize, sdr->filewrite);
#endif

}

void closesdr(struct rtlsdrstruct* sdr) {
	rtlsdr_close(sdr->device);
}

void set_cb_freq_sdr(struct rtlsdrstruct* sdr, int cbchannel, struct liquidobjects* dsp) {

//	printf("channel passed in = %d", cbchannel);
	switch (cbchannel) {

	case 1:
		tune_sdr(sdr, CB_CHANNEL_1, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_1);
		break;
	case 2:
		tune_sdr(sdr, CB_CHANNEL_2, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_2);
		break;
	case 3:
		tune_sdr(sdr, CB_CHANNEL_3, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_3);
		break;
	case 4:
		tune_sdr(sdr, CB_CHANNEL_4, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_4);
		break;
	case 5:
		tune_sdr(sdr, CB_CHANNEL_5, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_5);
		break;
	case 6:
		tune_sdr(sdr, CB_CHANNEL_6, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_6);
		break;
	case 7:
		tune_sdr(sdr, CB_CHANNEL_7, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_7);
		break;
	case 8:
		tune_sdr(sdr, CB_CHANNEL_8, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_8);
		break;
	case 9:
		tune_sdr(sdr, CB_CHANNEL_9, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_9);
		break;
	case 10:
		tune_sdr(sdr, CB_CHANNEL_10, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_10);
		break;
	case 11:
		tune_sdr(sdr, CB_CHANNEL_11, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_11);
		break;
	case 12:
		tune_sdr(sdr, CB_CHANNEL_12, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_12);
		break;
	case 13:
		tune_sdr(sdr, CB_CHANNEL_13, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_13);
		break;
	case 14:
		tune_sdr(sdr, CB_CHANNEL_14, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_14);
		break;
	case 15:
		tune_sdr(sdr, CB_CHANNEL_15, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_15);
		break;
	case 16:
		tune_sdr(sdr, CB_CHANNEL_16, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_16);
		break;
	case 17:
		tune_sdr(sdr, CB_CHANNEL_17, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_17);
		break;
	case 18:
		tune_sdr(sdr, CB_CHANNEL_18, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_18);
		break;
	case 19:
		tune_sdr(sdr, CB_CHANNEL_19, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_19);
		break;
	case 20:
		tune_sdr(sdr, CB_CHANNEL_20, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_20);
		break;
	case 21:
		tune_sdr(sdr, CB_CHANNEL_21, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_21);
		break;
	case 22:
		tune_sdr(sdr, CB_CHANNEL_22, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_22);
		break;
	case 23:
		tune_sdr(sdr, CB_CHANNEL_23, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_23);
		break;
	case 24:
		tune_sdr(sdr, CB_CHANNEL_24, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_24);
		break;
	case 25:
		tune_sdr(sdr, CB_CHANNEL_25, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_25);
		break;
	case 26:
		tune_sdr(sdr, CB_CHANNEL_26, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_26);
		break;
	case 27:
		tune_sdr(sdr, CB_CHANNEL_27, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_27);
		break;
	case 28:
		tune_sdr(sdr, CB_CHANNEL_28, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_28);
		break;
	case 29:
		tune_sdr(sdr, CB_CHANNEL_29, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_29);
		break;
	case 30:
		tune_sdr(sdr, CB_CHANNEL_30, dsp);\
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_30);
		break;
	case 31:
		tune_sdr(sdr, CB_CHANNEL_31, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_31);
		break;
	case 32:
		tune_sdr(sdr, CB_CHANNEL_32, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_32);
		break;
	case 33:
		tune_sdr(sdr, CB_CHANNEL_33, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_33);
		break;
	case 34:
		tune_sdr(sdr, CB_CHANNEL_34, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_34);
		break;
	case 35:
		tune_sdr(sdr, CB_CHANNEL_35, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_35);
		break;
	case 36:
		tune_sdr(sdr, CB_CHANNEL_36, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_36);
		break;
	case 37:
		tune_sdr(sdr, CB_CHANNEL_37, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_37);
		break;
	case 38:
		tune_sdr(sdr, CB_CHANNEL_38, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_38);
		break;
	case 39:
		tune_sdr(sdr, CB_CHANNEL_39, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_39);
		break;
	case 40:
		tune_sdr(sdr, CB_CHANNEL_40, dsp);
		printf("New frequency set to CB Channel %d : %dHz\n", cbchannel, CB_CHANNEL_40);
		break;
	}

}
