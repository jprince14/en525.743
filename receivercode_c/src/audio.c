#include "audio.h"

void initializeaudio(struct audiostruct* alsa) {
	int err;

	if ((err = snd_pcm_open(&alsa->playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
		fprintf(stderr, "cannot open audio device %s (%s)\n", "default", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_malloc(&alsa->hw_params)) < 0) {
		fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_any(alsa->playback_handle, alsa->hw_params)) < 0) {
		fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_set_access(alsa->playback_handle, alsa->hw_params, SND_PCM_ACCESS_RW_INTERLEAVED))
			< 0) {
		fprintf(stderr, "cannot set access type (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_set_format(alsa->playback_handle, alsa->hw_params, SND_PCM_FORMAT_FLOAT_LE)) < 0) {
		fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
		exit(1);
	}

	unsigned int samplingrate = 48000;
	if ((err = snd_pcm_hw_params_set_rate_near(alsa->playback_handle, alsa->hw_params, &samplingrate, 0)) < 0) {
		fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_set_channels(alsa->playback_handle, alsa->hw_params, 1)) < 0) {
		fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params(alsa->playback_handle, alsa->hw_params)) < 0) {
		fprintf(stderr, "cannot set parameters (%s)\n", snd_strerror(err));
		exit(1);
	}

	snd_pcm_hw_params_free(alsa->hw_params);

	if ((err = snd_pcm_prepare(alsa->playback_handle)) < 0) {
		fprintf(stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror(err));
		exit(1);
	}

}

void playaudio(struct liquidobjects* dsp, struct audiostruct* alsa) {
	int err;
	if (dsp->buffercounter > (dsp->buffermax)) {

		if ((err = snd_pcm_writei(alsa->playback_handle, dsp->buf_resamp, dsp->buffercounter)) != dsp->buffercounter) {
			fprintf(stderr, "write to audio interface failed (%s)\n", snd_strerror(err));
			exit(1);
		}
	}

}

void closeaudio(struct audiostruct* alsa) {
	snd_pcm_close(alsa->playback_handle);

}
