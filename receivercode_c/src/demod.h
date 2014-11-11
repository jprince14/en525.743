#ifndef DEMOD_H
#define DEMOD_H

#include "tcpsocket.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <liquid/liquid.h>
#include <complex.h>
#include "structures.h"


void demod_work(struct tcp_socket* rtl, struct liquidobjects* dsp);
void initialize_dspobjects(struct liquidobjects* dsp);

//void demod_work_testing(struct tcp_socket* rtl, struct liquidobjects* dsp, struct encoder* lame_obj);

#endif
