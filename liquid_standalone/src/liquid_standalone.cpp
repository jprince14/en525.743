#include <iostream>
#include <liquid/liquid.h>
#include <fstream>

#include <math.h>
#include <complex.h>

int _I;
int _Q;
const float scale;
float complex complexinputbuffer;
float filter_fc;          // filter cutoff frequency
float filter_As;         // stop-band attenuation [dB]
float filter_mu;          // fractional timing offset
float filter_ft; //filter transition
float kf;        // modulation factor
unsigned int h_len;
unsigned int buffercounter;

//    liquid_freqdem_type type;

// create modulator/demodulator objects
freqdem fdem;
float filterpulse[500];
float complex filteroutput[500];
float demodoutput;
float filtereddemodoutput[500];

void main()

{

	kf = 0.1f;        // modulation factor

	// create modulator/demodulator objects
	fdem = freqdem_create(kf);

	filter_fc = 0.375f;          // filter cutoff frequency = fc / 2*fs
	filter_ft = 0.125f;			//filter transition = ft / 2*fs
	filter_As = 60.0f;         // stop-band attenuation [dB]
	filter_mu = 0.0f;          // fractional timing offset

	h_len = estimate_req_filter_len(filter_ft, filter_As);
	liquid_firdes_kaiser(h_len, filter_fc, filter_As, filter_mu, filterpulse);

	//read in until end of file
	for (int x = 0; ________________; x++) {

		if (buffercounter == h_len) {

			//multiply input buffer by filter
			for (unsigned int length = 0; length < h_len; length++) {
				filteroutput[length] = filterpulse[length]
						* complexinputbuffer[length];
			}
			_filteredfile.write((char*) &filteroutput,
					sizeof(float complex) * buffercounter);

			//			freqdem_demodulate_block(fdem, reinterpret_cast<liquid_float_complex*>(&filteroutput), buffercounter,
			//					filtereddemodoutput);
			//
			//			_filteredanddemodulatedfile.write((char*) &filtereddemodoutput, sizeof(float complex) * buffercounter);

			freqdem_demodulate(fdem, complexinputbuffer, demodoutput);
			_demodulatedfile.write((char*) &demodoutput,
					sizeof(float complex) * buffercounter);

			//			}

			//			myfile.write((char*) &demodoutput, sizeof(float) * buffercounter);

			buffercounter = 0;
		}

		_I = passedinbuffer[2 * x];
		_Q = passedinbuffer[((2 * x) + 1)];
		//		complexbuffer.real(scale * (_I - 127));
		//		complexbuffer.imag(scale * (_Q - 127));
		//		memcpy(&fc,&complexbuffer, sizeof(complexbuffer));d
		//		myfile.write((char*) &complexbuffer, sizeof(complexbuffer));

		complexinputbuffer = (scale * (_I - 127)) + (I * scale * (_Q - 127));

		freqdem_demodulate(fdem,
				static_cast<liquid_float_complex>(complexinputbuffer),
				&demodoutput);
		_demodulatedfile.write((char*) &demodoutput,
				sizeof(float complex) * buffercounter);

		//		myfile.write((char*) &complexinputbuffer[buffercounter], sizeof(float complex));

		//		printf("%d items in buffer", buffercounter);

		//		buffercounter++;

	}

}
