#include "sdr.h"
#include <stdbool.h>

bool opensdr(struct rtlsdrstruct* sdr) {

	sdr->device_index = 0;

	int status;
	status = rtlsdr_open(&sdr->device, sdr->device_index);
	if (status < 0) {
		printf("Failed to open rtlsdr device %d.\n", sdr->device_index);
		exit(1);
	}

	sdr->sample_rate = 2000000;

	rtlsdr_set_sample_rate(sdr->device, sdr->sample_rate);

	return true;

}
void tunesdtr(struct rtlsdrstruct* sdr) {
	//rtlsdr_set_center_freq

}

void sdr_work(struct rtlsdrstruct* sdr) {
	rtlsdr_read_sync(sdr->device, sdr->buffer, 10000, &sdr->buffer_len);
}

void closesdr(struct rtlsdrstruct* sdr) {
	rtlsdr_close(sdr->device);
}

