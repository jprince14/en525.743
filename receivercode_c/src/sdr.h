#ifndef SDR_H
#define SDR_H

#include "structures.h"
#include <rtl-sdr.h>

bool opensdr(struct rtlsdrstruct* sdr);
void closesdr(struct rtlsdrstruct* sdr);
void tune_sdr(struct rtlsdrstruct* sdr, uint32_t freq);
void setsamplingrate_sdr(struct rtlsdrstruct* sdr, uint32_t freq);
void set_cb_freq_sdr(struct rtlsdrstruct* sdr, int cbchannel);
void sdr_work(struct rtlsdrstruct* sdr) ;


#endif
