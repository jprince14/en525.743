#include "encoder.h"

void initialize_encoder(struct liquidobjects* dsp, struct encoder* lame_encoder) {
	lame_encoder->lame = lame_init();
	lame_set_in_samplerate(lame_encoder->lame, (dsp->sample_rate_audio));
	lame_set_VBR(lame_encoder->lame, vbr_off); //sets cbr
	lame_set_VBR_q(lame_encoder->lame, 5); // 0 = best vbr q 5=~128k
//	lame_set_out_samplerate(lame_encoder->lame, (dsp->sample_rate_audio));
//	lame_set_num_channels(lame_encoder->lame, 1);
//	lame_set_out_samplerate(lame_encoder->lame, 16000);
	lame_init_params(lame_encoder->lame);
}

void encoder_work(struct liquidobjects* dsp, struct encoder* lame_encoder) {

	if (dsp->buffercounter > (10000)) {
//		printf("dsp->buffercounter = %d\n", dsp->buffercounter);

		lame_encoder->mp3buffsize = lame_encode_buffer_ieee_float(lame_encoder->lame, dsp->buf_resamp, dsp->buf_resamp,
				dsp->buffercounter, lame_encoder->mp3_buffer, 21 * 8192);

		curl_easy_setopt(lame_encoder->curl, CURLOPT_READDATA, lame_encoder->mp3_buffer);

		/* provide the size of the upload, we specicially typecast the value
		 to curl_off_t since we must be sure to use the correct data size */
		curl_easy_setopt(lame_encoder->curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t )lame_encoder->mp3buffsize);

		/* Now run off and do what you've been told! */
		lame_encoder->res = curl_easy_perform(lame_encoder->curl);

//		printf("lame_encoder->mp3buffsize = %d\n", lame_encoder->mp3buffsize);
//	printf("dsp->nw_resamp = %d\n", dsp->nw_resamp);

		fwrite(lame_encoder->mp3_buffer, 1, lame_encoder->mp3buffsize, lame_encoder->outfile);

//		fwrite(dsp->buf_resamp, sizeof(float), dsp->buffercounter, lame_encoder->outfile);
		dsp->buffercounter = 0;

	}
}

void close_encoderojects(struct encoder* lame_encoder) {
	curl_easy_cleanup(lame_encoder->curl);
	curl_global_cleanup();

}

void encoder_flush(struct liquidobjects* dsp, struct encoder* lame_encoder) {
	lame_encode_flush(lame_encoder->lame, lame_encoder->mp3_buffer, 21 * 8192);

}

static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
	size_t retcode;
	curl_off_t nread;

	/* in real-world cases, this would probably get this data differently
	 as this fread() stuff is exactly what the library already would do
	 by default internally */
	retcode = fread(ptr, size, nmemb, stream);

	nread = (curl_off_t) retcode;

	fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
	" bytes from file\n", nread);

	return retcode;
}

void initializecurl(struct encoder* encoder) {
	encoder->curl = curl_easy_init();

	//Initialize Curl
	if (encoder->curl) {
		/* we want to use our own read function */
		curl_easy_setopt(encoder->curl, CURLOPT_READFUNCTION, read_callback);

		/* enable uploading */
		curl_easy_setopt(encoder->curl, CURLOPT_UPLOAD, 1L);

		/* HTTP PUT please */
		curl_easy_setopt(encoder->curl, CURLOPT_PUT, 1L);

		/* specify target URL, and note that this URL should include a file
		 name, not only a directory */
		curl_easy_setopt(encoder->curl, CURLOPT_URL, "http://localhost:8001/sdr_stream");
//		curl_easy_setopt(encoder->curl, CURLOPT_URL, "http://user:password@localhost:8001/sdr_stream");
	}
}

