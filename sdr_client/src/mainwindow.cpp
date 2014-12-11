#include "mainwindow.hpp"

#include "ui_mainwindow.h"
#include "tcpclient.hpp"

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent), ui(new Ui::MainWindow) {
	recordmp3 = false;
	playaudio = false;
	rawiqflag = false;
//	demodbufferflagset = false;
	ui->setupUi(this);
	enableall(false, true);

#if dspcode == 1
	demodulated_que = new std::queue<demodulateddata>;
	liquidobjects = new dspobjects;
	initialize_dspobjects(liquidobjects);
//	results = new demodulateddata;

#if IGNOREMUTEX == 1
	if (pthread_mutex_init(&demodquelock, NULL) != 0) {
		printf("ERROR: Unable to open demodquelock\n");
	}
#endif

#endif

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

#if IGNOREMUTEX == 1
	if (pthread_mutex_init(&audiolock, NULL) != 0) {
		printf("ERROR: Unable to open audiolock\n");
	}
	if (pthread_mutex_init(&mp3lock, NULL) != 0) {
		printf("ERROR: Unable to open mp3lock\n");
	}
	if (pthread_mutex_init(&receivetypelock, NULL) != 0) {
		printf("ERROR: Unable to open receivetypelock\n");
	}

#endif

	demodulated = fopen("demod.bin", "wb");

}

MainWindow::~MainWindow() {

	if (ui->Enable_receiver->isChecked()) {
		if (controlsocket->Getrunningflag() == true) {
			//send the exit command
			uint32_t exitcommand[2];
			exitcommand[0] = 4;
			exitcommand[1] = 0;
			controlsocket->sendcommand(exitcommand);
//			controlsocket->Setrunningflag(false);
//			controlsocket->closesocket();
		}

//		if (datasocket->Getrunningflag() == true) {
//			datasocket->closesocket();
////			datasocket->Setrunningflag(false);
//		}

		enableall(false, false);

		//wait for the threads to close before continuing

		if (datasocket->Getrunningflag() == true) {

#if JOINFLAG == 1
			pthread_join(receive_pthread, NULL);
			pthread_join(output_pthread, NULL);
			pthread_join(demod_thread, NULL);
#endif
		}
	}
#if IGNOREMUTEX == 1
	pthread_mutex_destroy(&audiolock);

	pthread_mutex_destroy(&mp3lock);

#endif

#if dspcode == 1
	//empty the receive queue
#if IGNOREMUTEX == 1
	pthread_mutex_lock(&demodquelock);
#endif

	while (!demodulated_que->empty()) {
		demodulated_que->pop();
	}
#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&demodquelock);
	pthread_mutex_destroy(&demodquelock);
#endif

	demod_close(liquidobjects);
	delete liquidobjects;
	delete demodulated_que;
//	delete results;
#endif

#if IGNOREMUTEX == 1
	pthread_mutex_destroy(&receivetypelock);
#endif
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

#if IGNOREMUTEX == 1
			pthread_mutex_lock(&audiolock);
#endif
			audio_init();
			Setaudioflag(ui->enable_speakers->isChecked());
#if IGNOREMUTEX == 1
			pthread_mutex_unlock(&audiolock);
#endif

#if IGNOREMUTEX == 1
			pthread_mutex_lock(&mp3lock);
#endif
			recordmp3_initialize();
			Setmp3flag(ui->enable_recording->isChecked());

#if IGNOREMUTEX == 1
			pthread_mutex_unlock(&mp3lock);
#endif
		}

		else if (flag == false) {
//			printf("location 1-3\n");

//send the exit command
			uint32_t exitcommand[2];
			exitcommand[0] = 4;
			exitcommand[1] = 0;
			controlsocket->sendcommand(exitcommand);

#if IGNOREMUTEX == 1
			pthread_mutex_lock(&audiolock);
#endif
			Setaudioflag(false);
			audio_close();

#if IGNOREMUTEX == 1
			pthread_mutex_unlock(&audiolock);
#endif
#if IGNOREMUTEX == 1
			pthread_mutex_lock(&mp3lock);
#endif
			Setmp3flag(false);
			recordmp3_close();
			fclose(mp3file);

#if IGNOREMUTEX == 1
			pthread_mutex_unlock(&mp3lock);
#endif

			datasocket->closesocket();
			controlsocket->closesocket();

//			printf("location 3\n");

//wait for the threads to close before continuing
//			if (datasocket->Getrunningflag() == true) {

#if JOINFLAG == 1
			pthread_join(receive_pthread, NULL);
			pthread_join(output_pthread, NULL);
			pthread_join(demod_thread, NULL);
#endif
//			printf("location 4\n");
//			}
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
	_socket->Setrunningflag(_socket->opensocket());

	if (_socket->Getrunningflag() == true) {
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
	datasocket->Setrunningflag(_socket->opensocket());

	//kickoff receive and process thread
	if (pthread_create(&receive_pthread, NULL, receivethread, this) != 0) {

		printf("Error creating UDP thread\n");
	}
	if (pthread_create(&output_pthread, NULL, audiomp3thread, this) != 0) {

		printf("Error creating audio and mp3 thread\n");
	}
	if (pthread_create(&demod_thread, NULL, demodthread, this) != 0) {

		printf("Error creating demod thread\n");
	}

}

void MainWindow::on_beaglebone_ip_editingFinished() {
	if (beagleip.compare(ui->beaglebone_ip->text().toStdString()) != 0) {
		if (ui->Enable_receiver->isChecked() == true) {
			printf("Unable to change BeagleBone IP while the device is enabled\n");
			ui->beaglebone_ip->setText(QString::fromStdString(beagleip));
		} else if (ui->Enable_receiver->isChecked() == false) {
			beagleip = ui->beaglebone_ip->text().toStdString();
			std::cout << "New BeagleBone IP set to " << beagleip << std::endl;
		}
	}
}

void MainWindow::on_Client_IP_editingFinished() {

	if (clientip.compare(ui->Client_IP->text().toStdString()) != 0) {
		if (ui->Enable_receiver->isChecked() == true) {
			printf("Unable to change BeagleBone Client IP while the device is enabled\n");
			ui->Client_IP->setText(QString::fromStdString(clientip));
		} else if (ui->Enable_receiver->isChecked() == false) {
			clientip = ui->Client_IP->text().toStdString();
			std::cout << "New BeagleBone Client IP set to " << clientip << std::endl;
		}
	}
}

void MainWindow::on_beaglebone_port_editingFinished() {

	if (controlport != ui->beaglebone_port->text().toInt()) {
		if (ui->Enable_receiver->isChecked() == true) {
			printf("Unable to change BeagleBone Control Port while the device is enabled\n");
			ui->beaglebone_port->setText(QString::number(controlport));
		} else if (ui->Enable_receiver->isChecked() == false) {
			controlport = ui->beaglebone_port->text().toInt();
			std::cout << "New BeagleBone Control Port set to " << controlport << std::endl;
		}
	}
}

void MainWindow::on_beaglebone_data_port_editingFinished() {

	if (dataport != ui->beaglebone_data_port->text().toInt()) {
		if (ui->Enable_receiver->isChecked() == true) {
			printf("Unable to change BeagleBone Data Port while the device is enabled\n");
			ui->beaglebone_data_port->setText(QString::number(dataport));
		} else if (ui->Enable_receiver->isChecked() == false) {
			dataport = ui->beaglebone_data_port->text().toInt();
			std::cout << "New BeagleBone Data Port set to " << dataport << std::endl;
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

	if (controlsocket->Getrunningflag() == true) {
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

	//empty the queue
#if IGNOREMUTEX == 1
	pthread_mutex_lock(&datasocket->queuelock);
#endif

#if IGNOREMUTEX == 1
//	pthread_mutex_lock(&receivetypelock);
#endif

	//empty the receive queue
	while (!datasocket->rcv_que->empty()) {
		datasocket->rcv_que->pop();
	}

	printf("queue size = %d\n", datasocket->rcv_que->size());

#if IGNOREMUTEX == 1
//	pthread_mutex_unlock(&receivetypelock);
#endif

#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&datasocket->queuelock);
#endif

#if IGNOREMUTEX == 1
	pthread_mutex_lock(&demodquelock);
#endif

	while (!demodulated_que->empty()) {
		demodulated_que->pop();
	}

#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&demodquelock);
#endif
	//pause the audio/mp3 thread
	//flush the udp receive buffer
	//resume the thread

	if (ui->Receive_data_type->currentIndex() == 0) {
		//send audio
		printf("Command sent for server to send Audio\n");
		uint32_t data[2];
		data[0] = 5;
		data[1] = 0;
		controlsocket->sendcommand(data);
		rawiqflag = false;
		usleep(10000);

	} else if (ui->Receive_data_type->currentIndex() == 1) {
		//send raw IQ
		printf("Command Sent for server to send raw IQ data\n");
		uint32_t data[2];
		data[0] = 5;
		data[1] = 1;
		controlsocket->sendcommand(data);
		rawiqflag = true;
//		demodbufferflagset = false;
		usleep(10000);
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

		if (controlsocket->Getrunningflag() == true) {
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

		if (controlsocket->Getrunningflag() == true) {
			controlsocket->sendcommand(chamfreq_cmd);
		} else {
			printf("Not connected to TCP socket yet\n");
		}
	} else {
		printf("CB Channel not tuned since the modulation type is set as FM\n");
	}
}

void MainWindow::on_mp3_location_editingFinished() {

	if (ui->Enable_receiver->isChecked() == true) {
		printf("Unable to change mp3 locaiton while the device is enabled\n");
		ui->mp3_location->setText(QString::fromStdString(mp3location));
	} else if (ui->Enable_receiver->isChecked() == false) {
		mp3location = ui->mp3_location->text().toStdString();
		std::cout << "New mp3 record location set to " << mp3location << std::endl;
	}
}

void MainWindow::on_enable_speakers_clicked(bool) {
#if IGNOREMUTEX == 1
	pthread_mutex_lock(&audiolock);
#endif
	Setaudioflag(ui->enable_speakers->isChecked());

#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&audiolock);
#endif
}

void MainWindow::on_enable_recording_clicked(bool) {

#if IGNOREMUTEX == 1
	pthread_mutex_lock(&mp3lock);
#endif
	Setmp3flag(ui->enable_recording->isChecked());

#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&mp3lock);
#endif
}

void* MainWindow::receivethread(void *ptr) {
	MainWindow* input = (MainWindow*) ptr;

	printf("receive thread was opened\n");

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

#if IGNOREMUTEX == 1
//		pthread_mutex_lock(&input->receivetypelock);
#endif

		//Process PCM Audio
		if (input->rawiqflag == false) {

#if IGNOREMUTEX == 1
			pthread_mutex_lock(&input->mp3lock);
#endif
			if (input->Getmp3flag() == true) {
				input->recordmp3_work();
			}
#if IGNOREMUTEX == 1
			pthread_mutex_unlock(&input->mp3lock);
#endif
			//the mp3 must come before the audio since the pop from the queue is in the audio code
#if IGNOREMUTEX == 1
			pthread_mutex_lock(&input->audiolock);
#endif
			if (input->Getaudioflag() == true) {
				//send sound to speakers
				input->audio_play();

			}
#if IGNOREMUTEX == 1
			pthread_mutex_unlock(&input->audiolock);
#endif
//		pthread_mutex_lock(&input->audiolock);
//		pthread_mutex_lock(&input->mp3lock);

			if ((input->Getmp3flag() == false) && (input->Getaudioflag() == false)) {
				//if not playing audio or recording mp3 keep buffer at 7500
#if IGNOREMUTEX == 1
				pthread_mutex_lock(&input->datasocket->queuelock);
#endif
				if ((int) input->datasocket->rcv_que->size() > 7500) {

					input->datasocket->rcv_que->pop();
				}
#if IGNOREMUTEX == 1
				pthread_mutex_unlock(&input->datasocket->queuelock);
#endif
			}

		}

		//Process raw IQ data

#if dspcode == 1
		else if (input->rawiqflag == true) {

//			if (input->demodbufferflagset == true) {

#if IGNOREMUTEX == 1
			pthread_mutex_lock(&input->mp3lock);
#endif
			if (input->Getmp3flag() == true) {
				input->recordmp3_work_dsp();
			}
#if IGNOREMUTEX == 1
			pthread_mutex_unlock(&input->mp3lock);
#endif
			//the mp3 must come before the audio since the pop from the queue is in the audio code
#if IGNOREMUTEX == 1
			pthread_mutex_lock(&input->audiolock);
#endif
			if (input->Getaudioflag() == true) {
				//send sound to speakers
				input->audio_play_dsp();
			}
#if IGNOREMUTEX == 1
			pthread_mutex_unlock(&input->audiolock);
#endif
//		pthread_mutex_lock(&input->audiolock);
//		pthread_mutex_lock(&input->mp3lock);

			if ((input->Getmp3flag() == false) && (input->Getaudioflag() == false)) {
				//if not playing audio or recording mp3 keep buffer at 7500
#if IGNOREMUTEX == 1
				pthread_mutex_lock(&input->demodquelock);
#endif

				if ((int) input->demodulated_que->size() > 7500) {
					input->demodulated_que->pop();
//					printf("demod queue popped bc no audio or mp3\n");
				}
#if IGNOREMUTEX == 1
				pthread_mutex_unlock(&input->demodquelock);
#endif
			}
//			}
		}

#if IGNOREMUTEX == 1
//		pthread_mutex_lock(&input->receivetypelock);
#endif

#endif

	}

	printf("output thread has exited\n");
	pthread_exit(NULL);

}

void* MainWindow::demodthread(void* ptr) {
	MainWindow* input = (MainWindow*) ptr;

//	input->demodbufferflagset = false;

	while (input->datasocket->Getrunningflag() == true) {

		if (input->rawiqflag == true) {

//			pthread_mutex_lock(&input->datasocket->queuelock);
			if ((int) input->datasocket->rcv_que->size() > 1) {
//				struct demodulateddata localresult = demod_work(input->liquidobjects,
//						input->datasocket->rcv_que->front());

//				printf("Localresult length = %d\n", localresult.length);
//				input->demodulated_que->push(localresult);

#if IGNOREMUTEX == 1
				pthread_mutex_lock(&input->demodquelock);
#endif
//					printf("rcv que size = %d, demod queue size = %d\n", (int) input->datasocket->rcv_que->size(),
//							(int) input->demodulated_que->size());
				input->demodulated_que->push(demod_work(input->liquidobjects, input->datasocket->rcv_que->front()));
//				printf("rcv que size = %d, demod queue size = %d, demod length = %d, rcv_que length = %d\n", (int) input->datasocket->rcv_que->size(),
//						(int) input->demodulated_que->size(), input->demodulated_que->front().length, input->datasocket->rcv_que->front().revlength);

//					printf("location 1\n");
#if IGNOREMUTEX == 1
				pthread_mutex_unlock(&input->demodquelock);
#endif

				pthread_mutex_lock(&input->datasocket->queuelock);

				input->datasocket->rcv_que->pop();
//					printf("location 2\n");
				pthread_mutex_unlock(&input->datasocket->queuelock);

				//build up a buffer of length 500 before using the demod data

//				printf("location 3\n");
//				if (input->demodbufferflagset == false) {
////					pthread_mutex_lock(&input->demodquelock);
//
//					if ((int) input->demodulated_que->size() > 7500) {
//						input->demodbufferflagset = true;
//						printf("Demod buffer set\n");
//					}
//					printf("location 4\n");
//				pthread_mutex_unlock(&input->demodquelock);

//			pthread_mutex_unlock(&input->datasocket->queuelock);
//			}
//			else {
//				//min buffer size has already been reached
//			}
			} else {
				//not enogh data in the queue
//				usleep(10000);
			}

		} else {
			//receiving PCM audio at the moment, demod thread does nothing
			usleep(10000);
		}

	}

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
#if IGNOREMUTEX == 1
		pthread_mutex_lock(&datasocket->queuelock);
#endif
		mp3buffsize = lame_encode_buffer_ieee_float(lame, (float*) datasocket->rcv_que->front().rcvbuffer,
				(float *) datasocket->rcv_que->front().rcvbuffer,
				(int) (datasocket->rcv_que->front().revlength) / sizeof(float), mp3buffer, 10240);

//		printf("Writing %d bytes to mp3\n", int(datasocket->rcv_que->front().revlength / sizeof(float)));
#if IGNOREMUTEX == 1
		pthread_mutex_unlock(&datasocket->queuelock);
#endif
		if (mp3buffsize > 0) {
			printf("writing to mp3 buffer size = %d\n", mp3buffsize);
			if (mp3buffsize != fwrite(mp3buffer, 1, mp3buffsize, mp3file)) {
				printf("Error writing mp3 file");
				exit(0);
			}
		}
	}

//only pop off if the audio flag = false, otherwise the play audio function will pop
#if IGNOREMUTEX == 1
	pthread_mutex_lock(&audiolock);
#endif
	if (Getaudioflag() == false) {
//pop if the audio is not playing, if audio playing pop will occur there
		datasocket->rcv_que->pop();
	}
#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&audiolock);
#endif

}

#if dspcode == 1

void MainWindow::recordmp3_work_dsp() {
//	printf("demodulated_que->front()->size() = %d\n", demodulated_que->size());

	if ((int) datasocket->rcv_que->size() > 2) {
#if IGNOREMUTEX == 1
		pthread_mutex_lock(&demodquelock);
#endif
		mp3buffsize = lame_encode_buffer_ieee_float(lame, (float*) demodulated_que->front().buffer,
				(float *) demodulated_que->front().buffer, (int) (demodulated_que->front().length), mp3buffer, 10240);

//		printf("Writing %d bytes to mp3\n", int(datasocket->rcv_que->front().revlength / sizeof(float)));
#if IGNOREMUTEX == 1
		pthread_mutex_unlock(&demodquelock);
#endif

//		printf("demodulated_que->front()->size() = %d\n", demodulated_que->size());
//		fwrite(demodulated_que->front().buffer, 1, demodulated_que->front().length,
//				demodulated);
//		printf("demodulated_que->front().length = %d\n", demodulated_que->front().length);
//		fwrite(mp3buffer, 1, mp3buffsize, mp3file);
	}

//only pop off if the audio flag = false, otherwise the play audio function will pop
#if IGNOREMUTEX == 1
	pthread_mutex_lock(&audiolock);
//	pthread_mutex_lock(&datasocket->queuelock);
#endif
	if (Getaudioflag() == false) {
//pop if the audio is not playing, if audio playing pop will occur there
		demodulated_que->pop();
	}
#if IGNOREMUTEX == 1
//	pthread_mutex_unlock(&datasocket->queuelock);
	pthread_mutex_unlock(&audiolock);
#endif

}
#endif

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

#if dspcode == 1
void MainWindow::audio_play_dsp() {
	int error;

//	if (demodbufferflagset == true) {

//		printf("dsp queue = %d\n", (int) demodulated_que->size());
//		printf("audio length = %d\n", demodulated_que->front().length);

#if IGNOREMUTEX == 1
	pthread_mutex_lock(&demodquelock);
#endif
	if ((int) demodulated_que->size() > 2) {
		if (pa_simple_write(pulsestruct, (void*) demodulated_que->front().buffer,
				(size_t) demodulated_que->front().length * sizeof(float), &error) < 0) {
			fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
		}

//		printf("demodulated_que->front()->size() = %d\n", demodulated_que->size());
//		fwrite(demodulated_que->front().buffer, 1, demodulated_que->front().length, demodulated);
//		printf("demodulated_que->front().length = %d\n", demodulated_que->front().length);

//pop the data off, the mp3 recording only will pop if play audioflag = false
//		printf("pre-pop dsp queue = %d\n", (int) demodulated_que->size());
		demodulated_que->pop();
//		printf("post-pop dsp queue = %d\n", (int) demodulated_que->size());
//			printf("demod que popped in audio thread\n");
	} else {
//do nothing and let the buffer grow til its size is the min size
	}

#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&demodquelock);
#endif
//	}
}
#endif

void MainWindow::audio_play() {
	int error;

//	if (datasocket->audiobufferset == true) {

//		printf("audio length = %d\n", socket->rcv_que->front().revlength);
#if IGNOREMUTEX == 1
	pthread_mutex_lock(&datasocket->queuelock);
#endif
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
#if IGNOREMUTEX == 1
	pthread_mutex_unlock(&datasocket->queuelock);
#endif
}

void MainWindow::audio_close() {

	int error;
	if (pa_simple_drain(pulsestruct, &error) < 0) {
		fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));

	}
	pa_simple_free(pulsestruct);

}
