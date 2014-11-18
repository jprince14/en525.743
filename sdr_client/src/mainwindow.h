#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.hpp"
#include "udpclient.hpp"
#include <pthread.h>
#include <string.h>
#include <string>
#include <lame/lame.h>
#include <pulse/pulseaudio.h>
#include <pulse/simple.h>
#include <pulse/error.h>

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void enableall(bool, bool);
	std::tcpsocket* controlsocket;
	std::udpsocket* datasocket;
	void initialize_open_udp_socket(std::udpsocket*);

	void initialize_open_tcp_socket(std::tcpsocket*);

	pa_simple *pulsestruct;
	pa_sample_spec pulsespec;

	static void* receivethread(void*);
	bool socketconnectflag;
	bool Getaudioflag();

	void Setaudioflag(bool);
	bool Getmp3flag();
	void Setmp3flag(bool);
	pthread_mutex_t audiolock;
	pthread_mutex_t mp3lock;

	unsigned char mp3buffer[10240];
	lame_t lame;
	int mp3buffsize;
	FILE* mp3file;

	pthread_t receive_pthread;

	void recordmp3_initialize();
	void recordmp3_close();
	void recordmp3_work(float*, int, FILE*);
	void audio_play(float*, int);
	void audio_init();
	void audio_close();

//	/http://freedesktop.org/software/pulseaudio/doxygen/simple.html#overv_sec

private slots:

	void on_Enable_receiver_clicked();

	void on_beaglebone_ip_editingFinished();

	void on_beaglebone_port_editingFinished();

	void on_modulation_combobox_currentIndexChanged(int index);

	void on_fm_freq_BOX_editingFinished();

	void on_CB_channel_box_editingFinished();

	void on_mp3_location_editingFinished();

	void on_enable_speakers_clicked(bool checked);

	void on_enable_recording_clicked(bool checked);

	void on_beaglebone_data_port_editingFinished();

private:
	Ui::MainWindow *ui;
	bool recordmp3;
	bool playaudio;
}
;

#endif // MAINWINDOW_H
