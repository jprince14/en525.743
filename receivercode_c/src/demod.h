#ifndef DEMOD_H
#define DEMOD_H

#include "tcpsocket.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <liquid/liquid.h>
#include <complex.h>
#include "structures.h"

void demod_work(struct rtlsdrstruct* rtl, struct liquidobjects* dsp);
void initialize_dspobjects(struct liquidobjects* dsp);
void demod_close(struct liquidobjects* dsp);

#endif
