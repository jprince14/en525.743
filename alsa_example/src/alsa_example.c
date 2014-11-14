//#include <fcntl.h>
//#include <sys/stat.h>

// aplay -c 1 -r 48000 -f FLOAT_LE file.pcm


#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>


int main() {
	int err;
	snd_pcm_t *playback_handle;
	snd_pcm_hw_params_t *hw_params;

	if ((err = snd_pcm_open(&playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
		fprintf(stderr, "cannot open audio device %s (%s)\n", "default", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
		fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_any(playback_handle, hw_params)) < 0) {
		fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_set_access(playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf(stderr, "cannot set access type (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_set_format(playback_handle, hw_params, SND_PCM_FORMAT_FLOAT_LE)) < 0) {
		fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
		exit(1);
	}

	unsigned int samplingrate = 48000;
	if ((err = snd_pcm_hw_params_set_rate_near(playback_handle, hw_params, &samplingrate, 0)) < 0) {
		fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params_set_channels(playback_handle, hw_params, 1)) < 0) {
		fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
		exit(1);
	}

	if ((err = snd_pcm_hw_params(playback_handle, hw_params)) < 0) {
		fprintf(stderr, "cannot set parameters (%s)\n", snd_strerror(err));
		exit(1);
	}

	snd_pcm_hw_params_free(hw_params);

	if ((err = snd_pcm_prepare(playback_handle)) < 0) {
		fprintf(stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror(err));
		exit(1);
	}


	FILE *pcm = fopen("file.pcm", "rb");

	int pcmbuffersize;
	const int PCM_MAXSIZE = 500;

	float pcm_buffer[PCM_MAXSIZE * 2];

	do {
		pcmbuffersize = fread(pcm_buffer, sizeof(float), PCM_MAXSIZE, pcm);

		if ((err = snd_pcm_writei(playback_handle, pcm_buffer, pcmbuffersize)) != pcmbuffersize) {
			fprintf(stderr, "write to audio interface failed (%s)\n", snd_strerror(err));
			exit(1);
		}

	} while (pcmbuffersize != 0);

	snd_pcm_close(playback_handle);
	fclose(pcm);
	return 0;
}
