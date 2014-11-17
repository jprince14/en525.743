#include "mainwindow.h"
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

	if (pthread_mutex_init(&audiolock, NULL) != 0) {
		printf("ERROR: Unable to open audiolock\n");
	}
	if (pthread_mutex_init(&mp3lock, NULL) != 0) {
		printf("ERROR: Unable to open mp3lock\n");
	}

}

MainWindow::~MainWindow() {
	delete datasocket;
	delete controlsocket;
	delete ui;

}

void MainWindow::enableall(bool flag, bool startup) {
	ui->beaglebone_ip->setEnabled(flag);
	ui->beaglebone_port->setEnabled(flag);
	ui->CB_channel_box->setEnabled(flag);
	ui->cb_channel_label->setEnabled(flag);
	ui->cb_channel_label->setEnabled(flag);
	ui->enable_recording->setEnabled(flag);
	ui->enable_speakers->setEnabled(flag);
	ui->fm_freq_BOX->setEnabled(flag);
	ui->fm_freq_label->setEnabled(flag);
	ui->ip_label->setEnabled(flag);
	ui->modulationtype_label->setEnabled(flag);
	ui->modulation_combobox->setEnabled(flag);
	ui->mp3_location->setEnabled(flag);
	ui->mp3_location_label->setEnabled(flag);
	ui->port_label->setEnabled(flag);
	ui->output_label->setEnabled(flag);
	ui->data_port_label->setEnabled(flag);
	ui->beaglebone_data_port->setEnabled(flag);

	if (startup == false) {
		if (flag == true) {

			initialize_open_tcp_socket(controlsocket);
			initialize_open_udp_socket(datasocket);
		}

		else if (flag == false) {
			datasocket->closesocket();
			controlsocket->closesocket();
		}
	}
}

void MainWindow::on_Enable_receiver_clicked() {
//	printf("on_Enable_receiver_clicked was run\n");
	enableall(ui->Enable_receiver->isChecked(), false);
}

void MainWindow::initialize_open_tcp_socket(std::tcpsocket* socket) {
	socket->assignipaddr(ui->beaglebone_ip->text().toStdString());
	socket->assignport(ui->beaglebone_port->text().toInt());
	socket->createsocket();
	socket->opensocket();

}

void MainWindow::initialize_open_udp_socket(std::udpsocket* socket) {
//	printf("initialize_open_udp_socket was run\n");

	socket->assignipaddr(ui->beaglebone_ip->text().toStdString());
	socket->assignport(ui->beaglebone_data_port->text().toInt());
	socket->createsocket();
	socket->opensocket();

	//kickoff receive and process thread
	if (pthread_create(&receive_pthread, NULL, receivethread, this) != 0) {

		printf("Error creating UDP thread\n");
	}

}

void MainWindow::on_beaglebone_ip_editingFinished() {
//	printf("on_beaglebone_ip_editingFinished was run\n");
	controlsocket->Setrunningflag(false);
	datasocket->Setrunningflag(false);
	controlsocket->closesocket();
	datasocket->closesocket();
	initialize_open_tcp_socket(controlsocket);
	initialize_open_udp_socket(datasocket);

}

void MainWindow::on_beaglebone_port_editingFinished() {

	controlsocket->closesocket();
	datasocket->closesocket();
	initialize_open_tcp_socket(controlsocket);
	initialize_open_udp_socket(datasocket);
}

void MainWindow::on_modulation_combobox_currentIndexChanged(int index) {
	//0 = mono fm
	//1 = stereo fm
	//2 = cm_am

	//    send modulation type then send tune freq

	struct commandstructure chmod_cmd;
	chmod_cmd.cmd = 0;

	if (index == 0) {
		chmod_cmd.param = 0;
	} else if (index == 1) {
		chmod_cmd.param = 0;
	} else if (index == 2) {
		chmod_cmd.param = 0;
	}

	controlsocket->sendcommand(chmod_cmd);

}

void MainWindow::on_fm_freq_BOX_editingFinished()

{

	//checking if modulation type if fm
	if (ui->modulation_combobox->currentIndex() == 0 || ui->modulation_combobox->currentIndex() == 1) {
		struct commandstructure chfmfreq_cmd;
		chfmfreq_cmd.cmd = 0;
		chfmfreq_cmd.param = ui->fm_freq_BOX->text().toInt();

		controlsocket->sendcommand(chfmfreq_cmd);
	}

	//    arg1.toInt()
}

void MainWindow::on_CB_channel_box_editingFinished() {

	//first check if mod type is AM
	if (ui->modulation_combobox->currentIndex() == 2) {
		struct commandstructure chamfreq_cmd;
		chamfreq_cmd.cmd = 0;
		chamfreq_cmd.param = ui->fm_freq_BOX->text().toInt();

		controlsocket->sendcommand(chamfreq_cmd);

	}

}

void MainWindow::on_mp3_location_editingFinished() {
	//close old file then open new one

//    arg1.toStdString().c_str();

}

void MainWindow::on_enable_speakers_clicked(bool checked) {
	if (checked == true) {
		pthread_mutex_lock(&audiolock);

		Setaudioflag(true);

#warning - first initialize speakers

		pthread_mutex_unlock(&audiolock);

	} else if (checked == false) {
		pthread_mutex_lock(&audiolock);

		//close down speakers

		Setaudioflag(false);
		pthread_mutex_unlock(&audiolock);

	}
}

void MainWindow::on_enable_recording_clicked(bool checked) {

	if (checked == true) {
		pthread_mutex_lock(&mp3lock);

		mp3file = fopen("fmdemod_demod.bin", "wb");

		Setmp3flag(true);
		pthread_mutex_unlock(&mp3lock);

	} else if (checked == false) {

		pthread_mutex_lock(&mp3lock);

		fclose(mp3file);

		Setmp3flag(false);
		pthread_mutex_unlock(&mp3lock);

	}
}

void MainWindow::on_beaglebone_data_port_editingFinished() {
	controlsocket->closesocket();
	datasocket->closesocket();
	initialize_open_tcp_socket(controlsocket);
	initialize_open_udp_socket(datasocket);
}

void* MainWindow::receivethread(void *ptr) {
	MainWindow* input = (MainWindow*) ptr;

	printf("thread was opened\n");

	input->datasocket->Setrunningflag(true);
	int rcv_length;
	while (input->datasocket->Getrunningflag() == true) {
		rcv_length = input->datasocket->receive(input->datasocket->receivebuffer);

		pthread_mutex_lock(&input->mp3lock);
		if (input->Getaudioflag() == true) {
			//send sound to speakers
		}
		pthread_mutex_unlock(&input->mp3lock);

		pthread_mutex_lock(&input->audiolock);
		if (input->Getmp3flag() == true) {

			if (rcv_length > 0) {
				printf("length = %d\n", rcv_length);
			}
			fwrite(input->datasocket->receivebuffer, 1, rcv_length, input->mp3file);

			//write to mp3
		}
		pthread_mutex_unlock(&input->audiolock);

	}

	return NULL;
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
