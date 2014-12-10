#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.hpp"
#include "udpclient.hpp"
#include "structures.h"

#if dspcode == 1
#include "dsp.h"
#endif

#include <pthread.h>
#include <string.h>
#include <string>
#include <lame/lame.h>
#include <pulse/pulseaudio.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <queue>

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
	pa_buffer_attr pabuffer;
	pa_sample_spec pulsespec;

//	struct demodulateddata results;

	static void* receivethread(void*);
	static void* audiomp3thread(void*);
	static void* demodthread(void*);

//	bool socketconnectflag;
	bool Getaudioflag();
	void Setaudioflag(bool);
	bool Getmp3flag();
	void Setmp3flag(bool);

#if IGNOREMUTEX == 1
	pthread_mutex_t audiolock;
	pthread_mutex_t mp3lock;
	pthread_mutex_t receivetypelock;

#if dspcode == 1
	pthread_mutex_t demodquelock;
#endif
#endif

#if dspcode == 1
	struct dspobjects* liquidobjects;
	bool rawiqflag;
	bool demodbufferflagset;
#endif

	unsigned char mp3buffer[10240];
	lame_t lame;
	unsigned int mp3buffsize;
	FILE* mp3file;

	pthread_t receive_pthread;
	pthread_t output_pthread;
	pthread_t demod_thread;

#if dspcode == 1
	std::queue<demodulateddata> *demodulated_que;
	void audio_play_dsp();
	void recordmp3_work_dsp();
#endif

	void recordmp3_initialize();
	void recordmp3_close();
	void recordmp3_work();
	void audio_play();
	void audio_init();
	void audio_close();
	void changemodulation();
	void restartrecording(bool);
	void changesenddatatype();

//	/http://freedesktop.org/software/pulseaudio/doxygen/simple.html#overv_sec

private slots:

	void on_Enable_receiver_clicked();

	void on_beaglebone_ip_editingFinished();

	void on_beaglebone_port_editingFinished();

	void on_modulation_combobox_currentIndexChanged(int);

	void on_fm_freq_BOX_editingFinished();

	void on_CB_channel_box_editingFinished();

	void on_mp3_location_editingFinished();

	void on_enable_speakers_clicked(bool checked);

	void on_enable_recording_clicked(bool checked);

	void on_beaglebone_data_port_editingFinished();

	void on_Client_IP_editingFinished();

	void on_Receive_data_type_currentIndexChanged(int);

private:
	Ui::MainWindow *ui;
	bool recordmp3;
	bool playaudio;
	int dataport;
	int controlport;
	std::string beagleip;
	std::string clientip;
	std::string mp3location;
	int fmfreq;
}
;

#endif // MAINWINDOW_H
