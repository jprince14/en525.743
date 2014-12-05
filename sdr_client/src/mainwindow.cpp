#include "mainwindow.hpp"

#include "ui_mainwindow.h"
#include "tcpclient.hpp"

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent), ui(new Ui::MainWindow) {
	recordmp3 = false;
	playaudio = false;

	ui->setupUi(this);

	enableall(false, true);

	controlsocket = new std::tcpsocket;
	datasocket = new std::udpsocket;

	dataport = ui->beaglebone_data_port->text().toInt();
	controlport = ui->beaglebone_port->text().toInt();
	beagleip = ui->beaglebone_ip->text().toStdString();
	clientip = ui->Client_IP->text().toStdString();
	mp3location = ui->mp3_location->text().toStdString();
	fmfreq = ui->fm_freq_BOX->text().toInt();

	std::cout << "dataport = " << dataport << std::endl;
	std::cout << "controlport = " << controlport << std::endl;
	std::cout << "beagleip = " << beagleip << std::endl;
	std::cout << "mp3location = " << mp3location << std::endl;
	std::cout << "fmfreq = " << fmfreq << std::endl;

	if (pthread_mutex_init(&audiolock, NULL) != 0) {
		printf("ERROR: Unable to open audiolock\n");
	}
	if (pthread_mutex_init(&mp3lock, NULL) != 0) {
		printf("ERROR: Unable to open mp3lock\n");
	}

}

MainWindow::~MainWindow() {

	if (ui->Enable_receiver->isChecked()) {

		//send the exit command
		uint32_t exitcommand[2];
		exitcommand[0] = 4;
		exitcommand[1] = 0;
		controlsocket->sendcommand(exitcommand);

		controlsocket->closesocket();
		datasocket->closesocket();

		//wait for the threads to close before continuing

		if (datasocket->Getrunningflag() == true) {
			pthread_join(receive_pthread, NULL);
			pthread_join(output_pthread, NULL);

		}
	}

	pthread_mutex_destroy(&audiolock);

	pthread_mutex_destroy(&mp3lock);

	delete datasocket;
	delete controlsocket;
	delete ui;
}

void MainWindow::enableall(bool flag, bool startup) {

//	printf("location 0-1\n");

	ui->beaglebone_ip->setEnabled(true);
	ui->beaglebone_port->setEnabled(true);
//	printf("location 0-2\n");
	ui->CB_channel_box->setEnabled(flag);
	ui->cb_channel_label->setEnabled(flag);
	ui->cb_channel_label->setEnabled(flag);
	ui->enable_recording->setEnabled(flag);
	ui->enable_speakers->setEnabled(flag);
	ui->fm_freq_BOX->setEnabled(flag);
//	printf("location 0-3\n");
	ui->fm_freq_label->setEnabled(flag);
	ui->ip_label->setEnabled(true);
	ui->modulationtype_label->setEnabled(flag);
	ui->modulation_combobox->setEnabled(flag);
//	printf("location 0-4\n");
	ui->mp3_location->setEnabled(true);
	ui->mp3_location_label->setEnabled(true);
	ui->port_label->setEnabled(true);
	ui->output_label->setEnabled(true);
	ui->data_port_label->setEnabled(true);
	ui->beaglebone_data_port->setEnabled(true);
	ui->Client_IP_label->setEnabled(true);
	ui->Client_IP->setEnabled(true);
	ui->Receive_data_type->setEnabled(flag);
	ui->receivetype_label->setEnabled(flag);
//	printf("location 0-5\n");

//printf("location 1\n");
	if (startup == false) {
		if (flag == true) {
//			printf("location 1-1\n");

			initialize_open_tcp_socket(controlsocket);
			initialize_open_udp_socket(datasocket);
//			printf("location 2\n");

		}

		else if (flag == false) {
//			printf("location 1-3\n");

//send the exit command
			uint32_t exitcommand[2];
			exitcommand[0] = 4;
			exitcommand[1] = 0;
			controlsocket->sendcommand(exitcommand);

			datasocket->closesocket();
			controlsocket->closesocket();

//			printf("location 3\n");

//wait for the threads to close before continuing
			if (datasocket->Getrunningflag() == true) {

				pthread_join(receive_pthread, NULL);
				pthread_join(output_pthread, NULL);
//			printf("location 4\n");
			}
		}
	}
}

void MainWindow::on_Enable_receiver_clicked() {
//	printf("on_Enable_receiver_clicked was run\n");
	enableall(ui->Enable_receiver->isChecked(), false);
//	printf("enableall completed\n");
}

void MainWindow::initialize_open_tcp_socket(std::tcpsocket* _socket) {
	_socket->assignipaddr(ui->beaglebone_ip->text().toStdString());
	_socket->assignport(ui->beaglebone_port->text().toInt());
	_socket->createsocket();
	socketconnectflag = _socket->opensocket();

	if (_socket->socketwasopenflag == true) {
		//this will tune the sdr to the gui's current settings
		changemodulation();
		changesenddatatype();
	}

}

void MainWindow::initialize_open_udp_socket(std::udpsocket* _socket) {
//	printf("initialize_open_udp_socket was run\n");

	_socket->assignipaddr(ui->Client_IP->text().toStdString());
	_socket->assignport(ui->beaglebone_data_port->text().toInt());
	_socket->createsocket();
	_socket->opensocket();

	//kickoff receive and process thread
	if (pthread_create(&receive_pthread, NULL, receivethread, this) != 0) {

		printf("Error creating UDP thread\n");
	}
	if (pthread_create(&output_pthread, NULL, audiomp3thread, this) != 0) {

		printf("Error creating audio and mp3 thread\n");
	}

}

void MainWindow::on_beaglebone_ip_editingFinished() {
	if (ui->Enable_receiver->isChecked() == true) {
		if (beagleip.compare(ui->beaglebone_ip->text().toStdString()) != 0) {
			restartoutput(2);
			std::cout << "The new IP address for the beaglebone is " << ui->beaglebone_ip->text().toStdString()
					<< std::endl;
			beagleip = ui->beaglebone_ip->text().toStdString();

			printf("\n\n\n\n\nwhi is this causing the udp socket to disconnect\n\n\n\n\n");
		}
	}
}
void MainWindow::on_Client_IP_editingFinished() {
	if (ui->Enable_receiver->isChecked() == true) {

		if (clientip.compare(ui->Client_IP->text().toStdString()) != 0) {
			restartoutput(1);
			std::cout << "The new IP address for the client is " << ui->Client_IP->text().toStdString() << std::endl;
			clientip = ui->Client_IP->text().toStdString();
		}
	}
}

void MainWindow::on_beaglebone_port_editingFinished() {
	if (ui->Enable_receiver->isChecked() == true) {

		if (controlport != ui->beaglebone_port->text().toInt()) {
			restartoutput(2);
			printf("The new control port address for the beaglebone is %d\n", ui->beaglebone_port->text().toInt());
			controlport = ui->beaglebone_port->text().toInt();
		}
	}
}

void MainWindow::on_beaglebone_data_port_editingFinished() {
	if (ui->Enable_receiver->isChecked() == true) {

		if (dataport != ui->beaglebone_data_port->text().toInt()) {
			restartoutput(1);
			printf("The new data port address for the beaglebone is %d\n", ui->beaglebone_data_port->text().toInt());
			dataport = ui->beaglebone_data_port->text().toInt();
		}
	}
}

void MainWindow::changemodulation() {
	//0 = mono fm
	//1 = stereo fm
	//2 = cm_am

	//    send modulation type then send tune freq

	uint32_t chmod_cmd[2];
	chmod_cmd[0] = 3;

	if (ui->modulation_combobox->currentIndex() == 0) {
		printf("Sending command for FM demodulation\n");
		chmod_cmd[1] = 0;
//	} else if (index == 1) {
//		printf("Sending command for Stereo-FM demodulation\n");
//		chmod_cmd[1] = 1;
	} else if (ui->modulation_combobox->currentIndex() == 1) {
		printf("Sending command for CB-AM demodulation\n");
		chmod_cmd[1] = 2;
	}

	if (socketconnectflag == true) {
		controlsocket->sendcommand(chmod_cmd);

		//This pause is needed so the server has time to process the command to set the mod type
		//otherwise without this sleep the tune command will be missed
		usleep(1000);

		if (ui->modulation_combobox->currentIndex() == 1) {
			//tune to the cb freq if its AM
			uint32_t cbamfreq_cmd[2];
			cbamfreq_cmd[0] = 2;
			cbamfreq_cmd[1] = ui->CB_channel_box->value();
			printf("frequency set to CB Radio channel %d\n", ui->CB_channel_box->value());
			controlsocket->sendcommand(cbamfreq_cmd);
		} else if (ui->modulation_combobox->currentIndex() == 0) {
			//tune the fm freq
			uint32_t fmfreq_cmd[2];
			fmfreq_cmd[0] = 1;
			fmfreq_cmd[1] = ui->fm_freq_BOX->text().toInt();
			controlsocket->sendcommand(fmfreq_cmd);
			printf("Frequency set to %dHz\n", ui->fm_freq_BOX->text().toInt());
		}

	} else {
		printf("Not connected to TCP socket yet, unable to change modulation\n");
	}
}

void MainWindow::changesenddatatype() {

	if (ui->Receive_data_type->currentIndex() == 0) {
		//send audio
		uint32_t data[2];
		data[0] = 5;
		data[1] = 0;
		controlsocket->sendcommand(data);

	} else if (ui->Receive_data_type->currentIndex() == 1) {
		//send raw IQ
		uint32_t data[2];
		data[0] = 5;
		data[1] = 1;
		controlsocket->sendcommand(data);
	}
}

void MainWindow::on_Receive_data_type_currentIndexChanged(int) {

	changesenddatatype();

}

void MainWindow::on_modulation_combobox_currentIndexChanged(int) {
	changemodulation();
}

void MainWindow::on_fm_freq_BOX_editingFinished() {

	printf("current fm freq = %d\n", ui->fm_freq_BOX->text().toInt());

//	if (fmfreq != ui->fm_freq_BOX->text().toInt()) {

	//checking if modulation type if fm
	if (ui->modulation_combobox->currentIndex() == 0) {
		uint32_t chfmfreq_cmd[2];
		chfmfreq_cmd[0] = 1;
		chfmfreq_cmd[1] = ui->fm_freq_BOX->text().toInt();

		if (socketconnectflag == true) {
			controlsocket->sendcommand(chfmfreq_cmd);
		} else {
			printf("Not connected to TCP socket yet\n");
		}
	} else {

		printf("FM freq not sent since the modulation type is AM\n");
	}

	fmfreq = ui->fm_freq_BOX->text().toInt();
//	}

	//    arg1.toInt()
}

void MainWindow::on_CB_channel_box_editingFinished() {

	printf("CB Channel is %d\n", ui->CB_channel_box->value());

	//first check if mod type is AM
	if (ui->modulation_combobox->currentIndex() == 1) {
		uint32_t chamfreq_cmd[2];
		chamfreq_cmd[0] = 2;
		chamfreq_cmd[1] = ui->CB_channel_box->value();

		if (socketconnectflag == true) {
			controlsocket->sendcommand(chamfreq_cmd);
		} else {
			printf("Not connected to TCP socket yet\n");
		}
	} else {
		printf("CB Channel not tuned since the modulation type is set as FM\n");
	}
}

void MainWindow::on_mp3_location_editingFinished() {

	if (Getmp3flag() == true) {
		//this will close down the file recording currently in progress
		//only if the location has actually changed
		if (mp3location.compare(ui->mp3_location->text().toStdString()) != 0) {

//			on_enable_recording_clicked(false);

			//this will start a new recording with the new filename
			//If a recording is not in progress this wont run
			restartrecording(true);

			mp3location = ui->mp3_location->text().toStdString();
		}
	} else {
		//No recording is in progress
		//do nothing, the new parameters will take effect after the recording is initialized
	}
}

void MainWindow::restartspeakers(bool flag) {

	if (flag == true) {
		pthread_mutex_lock(&audiolock);
		audio_init();
		Setaudioflag(true);

		pthread_mutex_unlock(&audiolock);

	} else if (flag == false) {
		pthread_mutex_lock(&audiolock);

		//close down speakers

		Setaudioflag(false);
		audio_close();
		datasocket->audiobufferset = false;
		pthread_mutex_unlock(&audiolock);
	}
}

void MainWindow::on_enable_speakers_clicked(bool) {

	if (ui->enable_speakers->isChecked() == true) {
		pthread_mutex_lock(&audiolock);
		audio_init();
		Setaudioflag(true);

		pthread_mutex_unlock(&audiolock);

	} else if (ui->enable_speakers->isChecked() == false) {
		pthread_mutex_lock(&audiolock);

		//close down speakers

		Setaudioflag(false);
		audio_close();
		datasocket->audiobufferset = false;
		pthread_mutex_unlock(&audiolock);

	}
}

void MainWindow::restartmp3(bool flag) {

	if (flag == true) {
		pthread_mutex_lock(&mp3lock);
		recordmp3_initialize(); //mp3 file opened in this function
		Setmp3flag(true);
		pthread_mutex_unlock(&mp3lock);

	} else if (flag == false) {

		pthread_mutex_lock(&mp3lock);

		Setmp3flag(false);
		recordmp3_close();
		fclose(mp3file);

		pthread_mutex_unlock(&mp3lock);

	}
}

void MainWindow::restartrecording(bool mp3locationchanged) {

	if (mp3locationchanged == true) {
		//close down the recording, it will open back up below
		pthread_mutex_lock(&mp3lock);

		Setmp3flag(false);

		printf("before close mp3\n");
		recordmp3_close();
		printf("after close mp3\n");
		fclose(mp3file);

		pthread_mutex_unlock(&mp3lock);

	}

	if (ui->enable_recording->isChecked() == true) {
		pthread_mutex_lock(&mp3lock);
		recordmp3_initialize(); //mp3 file opened in this function
		Setmp3flag(true);
		pthread_mutex_unlock(&mp3lock);

	} else if (ui->enable_recording->isChecked() == false) {

		pthread_mutex_lock(&mp3lock);

		Setmp3flag(false);

		printf("before close mp3\n");
		recordmp3_close();
		printf("after close mp3\n");
		fclose(mp3file);

		pthread_mutex_unlock(&mp3lock);
	}

}

void MainWindow::on_enable_recording_clicked(bool) {

	restartrecording(false);

}

void MainWindow::restartoutput(int socket) {
//1 = udp socket 2 = tcp socket
	if (socket == 1) {
		bool mp3checked = ui->enable_recording->isChecked();
		bool audiochecked = ui->enable_speakers->isChecked();

		printf("location 1\n");

		if (mp3checked == true) {
			restartmp3(false);
		}
		if (audiochecked == true) {
			restartspeakers(false);
		}

		controlsocket->Setrunningflag(false);
		datasocket->closesocket();
		printf("location 2\n");
		//empty the queue
		while (!datasocket->rcv_que->empty()) {
			datasocket->rcv_que->pop();
		}
		printf("location 3\n");
		sleep(1);

		initialize_open_udp_socket(datasocket);

		printf("location 4\n");
		if (mp3checked == true) {
			restartmp3(true);
		}
		printf("location 5\n");
		if (audiochecked == true) {
			restartspeakers(true);
		}

		printf("location 6\n");
	}

	else if (socket == 2) {
		printf("location-7\n");
		printf("location-8\n");
		//send the exit command
		uint32_t exitcommand[2];
		exitcommand[0] = 4;
		exitcommand[1] = 0;
		printf("location-9\n");
		controlsocket->sendcommand(exitcommand);

		printf("location 10\n");
		datasocket->Setrunningflag(false);
		printf("location 11\n");
		controlsocket->closesocket();
		printf("location 12\n");
	}

	initialize_open_tcp_socket(controlsocket);

}

void* MainWindow::receivethread(void *ptr) {
	MainWindow* input = (MainWindow*) ptr;

	printf("receive thread was opened\n");

	input->datasocket->Setrunningflag(true);

	while (input->datasocket->Getrunningflag() == true) {
		input->datasocket->receive();

	}

	printf("receive thread has exited\n");

//	return NULL;
	pthread_exit(NULL);

}

void* MainWindow::audiomp3thread(void *ptr) {

	MainWindow* input = (MainWindow*) ptr;

	printf("audiomp3thread launched\n");

	while (input->datasocket->Getrunningflag() == true) {

		pthread_mutex_lock(&input->mp3lock);
		if (input->Getmp3flag() == true) {
			input->recordmp3_work();
		}

		pthread_mutex_unlock(&input->mp3lock);

		//the mp3 must come before the audio since the pop from the queue is in the audio code

		pthread_mutex_lock(&input->audiolock);
		if (input->Getaudioflag() == true) {
			//send sound to speakers
			input->audio_play();

		}
		pthread_mutex_unlock(&input->audiolock);

		if ((input->Getmp3flag() == false) && (input->Getaudioflag() == false)) {
			//if not playing audio or recording mp3 keep buffer at 7500
			if ((int) input->datasocket->rcv_que->size() > 7500) {

				pthread_mutex_lock(&input->datasocket->queuelock);

				input->datasocket->rcv_que->pop();

				pthread_mutex_unlock(&input->datasocket->queuelock);
			}
		}

//		//check is the queue is in a proper state
//		if (((int) datasocket->rcv_que->size() > 8000) || ((int) datasocket->rcv_que->size() < -10)) {
//			printf("\nERROR: Receive Queue Corrupted\n\n");
//			printf("Receive Queue Length = %d\n", (int) datasocket->rcv_que->size());
//			//disable receiver
//			ui->Enable_receiver->setEnabled(false);
//			exit(0);
//		}
	}

	printf("output thread has exited\n");

//	return NULL;
	pthread_exit(NULL);

}

bool MainWindow::Getaudioflag() {
	return playaudio;
}
void MainWindow::Setaudioflag(bool input) {
	playaudio = input;
}

bool MainWindow::Getmp3flag() {
	return recordmp3;
}
void MainWindow::Setmp3flag(bool input) {
	recordmp3 = input;
}

void MainWindow::recordmp3_initialize() {
	lame = lame_init();
	lame_set_in_samplerate(lame, (48000));
	lame_set_VBR(lame, vbr_off); //sets cbr
	lame_set_VBR_q(lame, 3); // 0 = best vbr q 5=~128k
//	lame_set_out_samplerate(lame_encoder->lame, (dsp->sample_rate_audio));
//	lame_set_num_channels(lame_encoder->lame, 1);
//	lame_set_out_samplerate(lame_encoder->lame, 16000);
	lame_init_params(lame);

	mp3file = fopen(ui->mp3_location->text().toStdString().c_str(), "wb");

}

void MainWindow::recordmp3_close() {

	lame_encode_flush(lame, mp3buffer, 10240);
	lame_close(lame);

}

void MainWindow::recordmp3_work() {
	if ((int) datasocket->rcv_que->size() > 2) {

		pthread_mutex_lock(&datasocket->queuelock);

		mp3buffsize = lame_encode_buffer_ieee_float(lame, datasocket->rcv_que->front().rcvbuffer,
				datasocket->rcv_que->front().rcvbuffer, datasocket->rcv_que->front().revlength / sizeof(float),
				mp3buffer, 10240);

		pthread_mutex_unlock(&datasocket->queuelock);
		fwrite(mp3buffer, 1, mp3buffsize, mp3file);
	}

	//only pop off if the audio flag = false, otherwise the play audio function will pop
	if (Getaudioflag() == false) {
		datasocket->rcv_que->pop();
	}

}

void MainWindow::audio_init() {

	pulsespec.format = PA_SAMPLE_FLOAT32LE;
	pulsespec.channels = 1;
	pulsespec.rate = 48000;

//Not using these buffer settings
	pabuffer.maxlength = 4800;
	pabuffer.tlength = 2880;
	pabuffer.prebuf = 960;
	pabuffer.minreq = 960;

	pulsestruct = pa_simple_new(NULL, // Use the default server.
			"rtlsdr_demod_client", // Our application's name.
			PA_STREAM_PLAYBACK,
			NULL, // Use the default device.
			"Music", // Description of our stream.
			&pulsespec, // Our sample format.
			NULL, // Use default channel map
			NULL, // Use default buffering attributes.
			NULL // Ignore error code.
			);
}

void MainWindow::audio_play() {
	int error;

	if (datasocket->audiobufferset == true) {

//		printf("audio length = %d\n", socket->rcv_que->front().revlength);

		pthread_mutex_lock(&datasocket->queuelock);

		if ((int) datasocket->rcv_que->size() > 2) {
			if (pa_simple_write(pulsestruct, datasocket->rcv_que->front().rcvbuffer,
					(size_t) datasocket->rcv_que->front().revlength, &error) < 0) {
				fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
			}
			//pop the data off, the mp3 recording only will pop if play audioflag = false
			datasocket->rcv_que->pop();

		} else {
			//do nothing and let the buffer grow til its size is the min size

		}
		pthread_mutex_unlock(&datasocket->queuelock);

	} else {
		//this is the initial buffer size
		pthread_mutex_lock(&datasocket->queuelock);

		if ((int) datasocket->rcv_que->size() > 500) {
			datasocket->audiobufferset = true;
		}
		pthread_mutex_unlock(&datasocket->queuelock);

	}
}

void MainWindow::audio_close() {

	int error;
	if (pa_simple_drain(pulsestruct, &error) < 0) {
		fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));

	}
	pa_simple_free(pulsestruct);

}
