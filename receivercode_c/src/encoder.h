#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include "demod.h"
#include <stdio.h>
#include <stdlib.h>
#include <lame/lame.h>
#include "structures.h"



void initialize_encoder(struct liquidobjects* dsp, struct encoder* lame_encoder);

void encoder_work(struct liquidobjects* dsp, struct encoder* lame_encoder);

void encoder_flush(struct liquidobjects* dsp, struct encoder* lame_encoder);

//void encoder_work_2(struct liquidobjects* dsp, struct encoder* lame_encoder) ;

#endif

