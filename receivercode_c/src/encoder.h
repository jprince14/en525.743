#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>
#include "demod.h"
#include <stdio.h>
#include <stdlib.h>
#include <lame/lame.h>
#include "structures.h"

#include <curl/curl.h>
#include <fcntl.h>
#include <sys/stat.h>

void initialize_encoder(struct liquidobjects* dsp, struct encoder* lame_encoder);

void encoder_work(struct liquidobjects* dsp, struct encoder* lame_encoder, struct udp_socket* inputsocket);

void encoder_flush(struct liquidobjects* dsp, struct encoder* lame_encoder);

//static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream);

//void initializecurl(struct encoder* encoder);

void close_encoderojects(struct encoder* lame_encoder);

#endif

