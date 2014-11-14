#include "structures.h"
#include <alsa/asoundlib.h>

void initializeaudio(struct audiostruct* alsa);
void closeaudio(struct audiostruct* alsa);
void playaudio(struct liquidobjects* dsp, struct audiostruct* alsa);
