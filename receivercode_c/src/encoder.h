#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include "demod.h"

#include <lame/lame.h>

//staconst int MP3_buffer_SIZE = 8192;

struct encoder {
	lame_t lame;
	unsigned char mp3_buffer[50];
	unsigned int mp3buffsize;
	FILE * outfile; //This file is only for testing purposes to write output to a file

};

void initialize_encoder(struct encoder* lame_encoder);

void encoder_work(struct liquidobjects* dsp, struct encoder* lame_encoder);

#endif

