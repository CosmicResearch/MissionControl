#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T16:18:01
#
#-------------------------------------------------

QT       += core gui serialport webengine webenginewidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MissionControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    arduino.cpp \
    data.cpp \
    mapwindow.cpp

HEADERS  += mainwindow.h \
    arduino.h \
    data.h \
    mapwindow.h

FORMS    += mainwindow.ui \
    mapwindow.ui

DISTFILES += \
    google_maps.html \
    js.js

RESOURCES += \
    map.qrc
