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

}

MainWindow::~MainWindow() {
	delete ui;
	delete datasocket;
	delete controlsocket;
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

#warning - start receive thread from here and from receive thread then kick off writng to mp3 and/or play audio

}

void MainWindow::on_beaglebone_ip_editingFinished() {
//	printf("on_beaglebone_ip_editingFinished was run\n");

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

	if (index == 0) {

	} else if (index == 1) {

	} else if (index == 2) {

	}

}

void MainWindow::on_fm_freq_BOX_editingFinished()

{
	//first check if mod type is FM

	//    arg1.toInt()
}

void MainWindow::on_CB_channel_box_editingFinished() {

	//first check if mod type is AM

}

void MainWindow::on_mp3_location_editingFinished() {
	//close old file then open new one

//    arg1.toStdString().c_str();

}

void MainWindow::on_enable_speakers_clicked(bool checked) {
	if (checked == true) {

		Setaudioflag(true);
#warning - first initialize speakers

	} else if (checked == false) {

		//close down speakers

		Setaudioflag(false);

	}
}

void MainWindow::on_enable_recording_clicked(bool checked) {

	if (checked == true) {

		Setmp3flag(true);
#warning - first initialize file

	} else if (checked == false) {

		//close down file

		Setmp3flag(false);

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

	input->datasocket->Setrunningflag(true);

	while (input->datasocket->Getrunningflag() == true) {
		input->datasocket->receive(input->datasocket->receivebuffer);
		if (input->Getaudioflag() == true) {
			//send sound to speakers
		}
		if (input->Getmp3flag() == true) {

			//write to mp3
		}

	}

	return NULL;
}

void* MainWindow::testthread(void *x_void_ptr) {

	/* increment x to 100 */
	int *x_ptr = (int *) x_void_ptr;

	printf("testthread was created, tc %d\n", *x_ptr);

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
