#include "audio.h"

void initializeaudio(struct audiostruct* audio) {

	audio->pulsespec.format = PA_SAMPLE_FLOAT32LE;
	audio->pulsespec.channels = 1;
	audio->pulsespec.rate = 48000;

	audio->pulsestruct = pa_simple_new(NULL, // Use the default server.
			"rtlsdr_demod_client", // Our application's name.
			PA_STREAM_PLAYBACK,
			NULL, // Use the default device.
			"Music", // Description of our stream.
			&audio->pulsespec, // Our sample format.
			NULL, // Use default channel map
			NULL, // Use default buffering attributes.
			NULL // Ignore error code.
			);

	/*int err;

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

//	snd_pcm_uframes_t buffer_size = 1024;
//	snd_pcm_uframes_t period_size = 64;
//
//	snd_pcm_hw_params_set_buffer_size_near (alsa->playback_handle, alsa->hw_params, &buffer_size);
//	snd_pcm_hw_params_set_period_size_near (alsa->playback_handle, alsa->hw_params, &period_size, NULL);


	if ((err = snd_pcm_hw_params(alsa->playback_handle, alsa->hw_params)) < 0) {
		fprintf(stderr, "cannot set parameters (%s)\n", snd_strerror(err));
		exit(1);
	}

	snd_pcm_hw_params_free(alsa->hw_params);

	if ((err = snd_pcm_prepare(alsa->playback_handle)) < 0) {
		fprintf(stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror(err));
		exit(1);
	}

	alsa->audiobuffer_size = 0;
	alsa->minaudiobuffersize = 50;*/
}

void playaudio(struct liquidobjects* dsp, struct audiostruct* audio) {
	int err;

	if (pa_simple_write(audio->pulsestruct, dsp->buf_resamp,
						(size_t) dsp->copy_buffcounter, &err) < 0) {
					fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(err));
				}



//	printf("dsp->copy_buffcounter = %d\n", dsp->copy_buffcounter);
//	printf("alsa->audiobuffer_size = %d\n", alsa->audiobuffer_size);

//	if (alsa->audiobuffer_size > alsa->minaudiobuffersize) {

	/*	if ((err = snd_pcm_writei(alsa->playback_handle, dsp->buf_resamp, dsp->copy_buffcounter))
				!= dsp->copy_buffcounter) {
			fprintf(stderr, "error %d - write to audio interface failed (%s)\n", err, snd_strerror(err));
			exit(1);
		}
		snd_pcm_drain(alsa->playback_handle);
		alsa->audiobuffer_size = 0;*/

//	} else {
//
//		memcpy(alsa->audiobuffer + alsa->audiobuffer_size, dsp->buf_resamp, dsp->copy_buffcounter* sizeof(float) );
//		alsa->audiobuffer_size += dsp->copy_buffcounter;
//	}
}

void closeaudio(struct audiostruct* audio) {
//	snd_pcm_close(alsa->playback_handle);

	int error;
	if (pa_simple_drain(audio->pulsestruct, &error) < 0) {
		fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));

	}
	pa_simple_free(audio->pulsestruct);

}
