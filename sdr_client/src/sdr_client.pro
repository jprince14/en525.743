#-------------------------------------------------
#
# Project created by QtCreator 2014-11-15T12:36:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sdr_client
TEMPLATE = app
LIBS += -lpthread -lasound -lmp3lame

SOURCES += main.cpp\
        mainwindow.cpp \
    tcpclient.cpp \
    udpclient.cpp

HEADERS  += mainwindow.h \
    tcpclient.hpp \
    udpclient.hpp

FORMS    += mainwindow.ui
