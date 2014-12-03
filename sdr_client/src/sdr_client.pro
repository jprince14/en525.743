#-------------------------------------------------
#
# Project created by QtCreator 2014-11-15T12:36:19
#
#-------------------------------------------------

QT       += core gui 

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app
QMAKE_CXXFLAGS += -lpthread -lmp3lame -lpulse-simple -lpulse
QMAKE_CFLAGS += -lpthread -lmp3lame -lpulse-simple -lpulse

LIBS += -lpthread -lmp3lame -lpulse-simple -lpulse

SOURCES += main.cpp\
        mainwindow.cpp \
    tcpclient.cpp \
    udpclient.cpp

HEADERS  += mainwindow.h \
    tcpclient.hpp \
    udpclient.hpp

FORMS    += mainwindow.ui
