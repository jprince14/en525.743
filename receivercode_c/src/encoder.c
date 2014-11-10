#include "encoder.h"

void initialize_encoder(struct encoder* lame_encoder) {
	lame_encoder->lame = lame_init();
	lame_set_in_samplerate(lame_encoder->lame, (16000));
	lame_set_VBR(lame_encoder->lame, vbr_off); //sets cbr
	lame_set_VBR_q(lame_encoder->lame, 5); // 0 = best vbr q 5=~128k
//	lame_set_num_channels(lame_encoder->lame, 1);
//	lame_set_out_samplerate(lame_encoder->lame, 16000);
	lame_init_params(lame_encoder->lame);
}

void encoder_work(struct liquidobjects* dsp, struct encoder* lame_encoder) {

	if (dsp->buffercounter > (10000)) {
		printf("dsp->buffercounter = %d\n", dsp->buffercounter);

		lame_encoder->mp3buffsize = lame_encode_buffer_interleaved_ieee_float(lame_encoder->lame, dsp->buf_resamp,
				dsp->buffercounter, lame_encoder->mp3_buffer, 21 * 8192);

		printf("lame_encoder->mp3buffsize = %d\n", lame_encoder->mp3buffsize);
//	printf("dsp->nw_resamp = %d\n", dsp->nw_resamp);

		fwrite(lame_encoder->mp3_buffer, 1, lame_encoder->mp3buffsize, lame_encoder->outfile);
//		fwrite(dsp->buf_resamp, sizeof(float), dsp->buffercounter, lame_encoder->outfile);
		dsp->buffercounter = 0;

	}
}

void encoder_flush(struct liquidobjects* dsp, struct encoder* lame_encoder) {
	lame_encode_flush(lame_encoder->lame, lame_encoder->mp3_buffer, 21 * 8192);

}

//void encoder_work_2(struct liquidobjects* dsp, struct encoder* lame_encoder) {
//
//		printf("dsp->buffercounter = %d\n", dsp->buffercounter);
//
//		lame_encoder->mp3buffsize = lame_encode_buffer_interleaved_ieee_float(lame_encoder->lame, dsp->buf_resamp,
//				dsp->nw_resamp, lame_encoder->mp3_buffer, 21 * 8192);
//
//		printf("lame_encoder->mp3buffsize = %d\n", lame_encoder->mp3buffsize);
////	printf("dsp->nw_resamp = %d\n", dsp->nw_resamp);
//
//		fwrite(lame_encoder->mp3_buffer, 1, lame_encoder->mp3buffsize, lame_encoder->outfile);
////		fwrite(dsp->buf_resamp, sizeof(float), dsp->buffercounter, lame_encoder->outfile);
//
//
//}
