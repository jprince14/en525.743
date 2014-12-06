/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QCheckBox *Enable_receiver;
    QGridLayout *configlayout;
    QLabel *modulationtype_label;
    QLabel *fm_freq_label;
    QLabel *ip_label;
    QCheckBox *enable_speakers;
    QLineEdit *beaglebone_data_port;
    QLabel *Client_IP_label;
    QLineEdit *mp3_location;
    QLabel *mp3_location_label;
    QLineEdit *beaglebone_port;
    QSpinBox *CB_channel_box;
    QLabel *cb_channel_label;
    QLineEdit *fm_freq_BOX;
    QLabel *port_label;
    QComboBox *modulation_combobox;
    QLabel *data_port_label;
    QCheckBox *enable_recording;
    QLineEdit *beaglebone_ip;
    QLabel *output_label;
    QLineEdit *Client_IP;
    QLabel *receivetype_label;
    QComboBox *Receive_data_type;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(748, 338);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(723, 15));

        verticalLayout->addWidget(label);

        Enable_receiver = new QCheckBox(centralWidget);
        Enable_receiver->setObjectName(QString::fromUtf8("Enable_receiver"));

        verticalLayout->addWidget(Enable_receiver);

        configlayout = new QGridLayout();
        configlayout->setSpacing(6);
        configlayout->setObjectName(QString::fromUtf8("configlayout"));
        modulationtype_label = new QLabel(centralWidget);
        modulationtype_label->setObjectName(QString::fromUtf8("modulationtype_label"));

        configlayout->addWidget(modulationtype_label, 6, 0, 1, 1);

        fm_freq_label = new QLabel(centralWidget);
        fm_freq_label->setObjectName(QString::fromUtf8("fm_freq_label"));

        configlayout->addWidget(fm_freq_label, 6, 1, 1, 1);

        ip_label = new QLabel(centralWidget);
        ip_label->setObjectName(QString::fromUtf8("ip_label"));

        configlayout->addWidget(ip_label, 1, 0, 1, 1);

        enable_speakers = new QCheckBox(centralWidget);
        enable_speakers->setObjectName(QString::fromUtf8("enable_speakers"));

        configlayout->addWidget(enable_speakers, 8, 1, 1, 1);

        beaglebone_data_port = new QLineEdit(centralWidget);
        beaglebone_data_port->setObjectName(QString::fromUtf8("beaglebone_data_port"));

        configlayout->addWidget(beaglebone_data_port, 4, 1, 1, 1);

        Client_IP_label = new QLabel(centralWidget);
        Client_IP_label->setObjectName(QString::fromUtf8("Client_IP_label"));

        configlayout->addWidget(Client_IP_label, 2, 0, 1, 1);

        mp3_location = new QLineEdit(centralWidget);
        mp3_location->setObjectName(QString::fromUtf8("mp3_location"));

        configlayout->addWidget(mp3_location, 9, 2, 1, 1);

        mp3_location_label = new QLabel(centralWidget);
        mp3_location_label->setObjectName(QString::fromUtf8("mp3_location_label"));

        configlayout->addWidget(mp3_location_label, 9, 1, 1, 1);

        beaglebone_port = new QLineEdit(centralWidget);
        beaglebone_port->setObjectName(QString::fromUtf8("beaglebone_port"));

        configlayout->addWidget(beaglebone_port, 3, 1, 1, 1);

        CB_channel_box = new QSpinBox(centralWidget);
        CB_channel_box->setObjectName(QString::fromUtf8("CB_channel_box"));
        CB_channel_box->setMinimum(1);
        CB_channel_box->setMaximum(40);

        configlayout->addWidget(CB_channel_box, 7, 2, 1, 1);

        cb_channel_label = new QLabel(centralWidget);
        cb_channel_label->setObjectName(QString::fromUtf8("cb_channel_label"));

        configlayout->addWidget(cb_channel_label, 6, 2, 1, 1);

        fm_freq_BOX = new QLineEdit(centralWidget);
        fm_freq_BOX->setObjectName(QString::fromUtf8("fm_freq_BOX"));

        configlayout->addWidget(fm_freq_BOX, 7, 1, 1, 1);

        port_label = new QLabel(centralWidget);
        port_label->setObjectName(QString::fromUtf8("port_label"));

        configlayout->addWidget(port_label, 3, 0, 1, 1);

        modulation_combobox = new QComboBox(centralWidget);
        modulation_combobox->setObjectName(QString::fromUtf8("modulation_combobox"));

        configlayout->addWidget(modulation_combobox, 7, 0, 1, 1);

        data_port_label = new QLabel(centralWidget);
        data_port_label->setObjectName(QString::fromUtf8("data_port_label"));

        configlayout->addWidget(data_port_label, 4, 0, 1, 1);

        enable_recording = new QCheckBox(centralWidget);
        enable_recording->setObjectName(QString::fromUtf8("enable_recording"));

        configlayout->addWidget(enable_recording, 8, 2, 1, 1);

        beaglebone_ip = new QLineEdit(centralWidget);
        beaglebone_ip->setObjectName(QString::fromUtf8("beaglebone_ip"));

        configlayout->addWidget(beaglebone_ip, 1, 1, 1, 1);

        output_label = new QLabel(centralWidget);
        output_label->setObjectName(QString::fromUtf8("output_label"));

        configlayout->addWidget(output_label, 8, 0, 1, 1);

        Client_IP = new QLineEdit(centralWidget);
        Client_IP->setObjectName(QString::fromUtf8("Client_IP"));

        configlayout->addWidget(Client_IP, 2, 1, 1, 1);

        receivetype_label = new QLabel(centralWidget);
        receivetype_label->setObjectName(QString::fromUtf8("receivetype_label"));

        configlayout->addWidget(receivetype_label, 5, 0, 1, 1);

        Receive_data_type = new QComboBox(centralWidget);
        Receive_data_type->setObjectName(QString::fromUtf8("Receive_data_type"));

        configlayout->addWidget(Receive_data_type, 5, 1, 1, 1);


        verticalLayout->addLayout(configlayout);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(Enable_receiver, beaglebone_ip);
        QWidget::setTabOrder(beaglebone_ip, Client_IP);
        QWidget::setTabOrder(Client_IP, beaglebone_port);
        QWidget::setTabOrder(beaglebone_port, beaglebone_data_port);
        QWidget::setTabOrder(beaglebone_data_port, Receive_data_type);
        QWidget::setTabOrder(Receive_data_type, modulation_combobox);
        QWidget::setTabOrder(modulation_combobox, fm_freq_BOX);
        QWidget::setTabOrder(fm_freq_BOX, CB_channel_box);
        QWidget::setTabOrder(CB_channel_box, enable_speakers);
        QWidget::setTabOrder(enable_speakers, enable_recording);
        QWidget::setTabOrder(enable_recording, mp3_location);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Welcome to Jeremy's En525.743 Embedded Development Receiver Client", 0, QApplication::UnicodeUTF8));
        Enable_receiver->setText(QApplication::translate("MainWindow", "Receive from BeagleBone", 0, QApplication::UnicodeUTF8));
        modulationtype_label->setText(QApplication::translate("MainWindow", "Modulation Type", 0, QApplication::UnicodeUTF8));
        fm_freq_label->setText(QApplication::translate("MainWindow", "FM - Frequency", 0, QApplication::UnicodeUTF8));
        ip_label->setText(QApplication::translate("MainWindow", "BealeBone IP", 0, QApplication::UnicodeUTF8));
        enable_speakers->setText(QApplication::translate("MainWindow", "Speakers", 0, QApplication::UnicodeUTF8));
        beaglebone_data_port->setText(QApplication::translate("MainWindow", "5678", 0, QApplication::UnicodeUTF8));
        Client_IP_label->setText(QApplication::translate("MainWindow", "Client IP", 0, QApplication::UnicodeUTF8));
        mp3_location->setText(QApplication::translate("MainWindow", "/home/jeremy/en525_743/recording.mp3", 0, QApplication::UnicodeUTF8));
        mp3_location_label->setText(QApplication::translate("MainWindow", "mp3 name/location", 0, QApplication::UnicodeUTF8));
        beaglebone_port->setText(QApplication::translate("MainWindow", "1234", 0, QApplication::UnicodeUTF8));
        cb_channel_label->setText(QApplication::translate("MainWindow", "CB - Channel", 0, QApplication::UnicodeUTF8));
        fm_freq_BOX->setText(QApplication::translate("MainWindow", "97900000", 0, QApplication::UnicodeUTF8));
        port_label->setText(QApplication::translate("MainWindow", "BeagleBone Control Port", 0, QApplication::UnicodeUTF8));
        modulation_combobox->clear();
        modulation_combobox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "FM", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "CB Radio - AM", 0, QApplication::UnicodeUTF8)
        );
        data_port_label->setText(QApplication::translate("MainWindow", "BeagleBone Data Port", 0, QApplication::UnicodeUTF8));
        enable_recording->setText(QApplication::translate("MainWindow", "Record to mp3 file", 0, QApplication::UnicodeUTF8));
        beaglebone_ip->setText(QApplication::translate("MainWindow", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        output_label->setText(QApplication::translate("MainWindow", "Output", 0, QApplication::UnicodeUTF8));
        Client_IP->setText(QApplication::translate("MainWindow", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        receivetype_label->setText(QApplication::translate("MainWindow", "Receive DataType", 0, QApplication::UnicodeUTF8));
        Receive_data_type->clear();
        Receive_data_type->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Demodulated Audio", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Raw IQ Data", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
