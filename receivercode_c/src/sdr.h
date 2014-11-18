#ifndef SDR_H
#define SDR_H

#include "structures.h"
#include <rtl-sdr.h>

bool opensdr(struct rtlsdrstruct* sdr, struct liquidobjects* dsp);
void closesdr(struct rtlsdrstruct* sdr);
void tune_sdr(struct rtlsdrstruct* sdr, uint32_t freq, struct liquidobjects* dsp);
void setsamplingrate_sdr(struct rtlsdrstruct* sdr, uint32_t freq, struct liquidobjects* dsp);
void set_cb_freq_sdr(struct rtlsdrstruct* sdr, int cbchannel, struct liquidobjects* dsp);
void sdr_work(struct rtlsdrstruct* sdr);

#endif
