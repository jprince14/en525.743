#ifndef SDR_H
#define SDR_H

#include "structures.h"
#include <rtl-sdr.h>



bool opensdr(struct rtlsdrstruct* sdr);
void tunesdtr(struct rtlsdrstruct* sdr);
void closesdr(struct rtlsdrstruct* sdr);


#endif
