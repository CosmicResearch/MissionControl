#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T16:18:01
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MissionControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    arduino.cpp \
    data.cpp

HEADERS  += mainwindow.h \
    arduino.h \
    data.h

FORMS    += mainwindow.ui
