#ifndef STRUCTURES_H
#define STRUCTURES_H



#ifndef _DSP
#define dspcode 1 //0 = ignore dsp code, 1 = run dsp code
#endif

struct receivestruct {
	unsigned int revlength;
	uint8_t rcvbuffer[5000];
};


#if dspcode == 1
struct demodulateddata{
	unsigned int length;
	float buffer[2500];

};
#endif



#endif
