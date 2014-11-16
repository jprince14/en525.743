#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.hpp"

#include "udpclient.hpp"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void enableall(bool,bool );
    std::tcpsocket* controlsocket;
    std::udpsocket* datasocket;
    void initialize_open_udp_socket(std::udpsocket* );

    void initialize_open_tcp_socket(std::tcpsocket*);

    bool recordmp3;
    bool playaudio;



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
};

#endif // MAINWINDOW_H
