#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include "demod.h"
#include <stdio.h>
#include <stdlib.h>
#include <lame/lame.h>

struct encoder {
	lame_t lame;
	unsigned char mp3_buffer[8192 * 21];
	unsigned int mp3buffsize;
	FILE * outfile; //This file is only for testing purposes to write output to a file

};

void initialize_encoder(struct encoder* lame_encoder);

void encoder_work(struct liquidobjects* dsp, struct encoder* lame_encoder);

void encoder_flush(struct liquidobjects* dsp, struct encoder* lame_encoder);

//void encoder_work_2(struct liquidobjects* dsp, struct encoder* lame_encoder) ;

#endif

