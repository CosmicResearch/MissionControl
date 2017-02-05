#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T16:18:01
#
#-------------------------------------------------

QT       += core gui serialport webengine webenginewidgets network positioning charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = MissionControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    arduino.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    arduino.h \
    qcustomplot.h

FORMS    += mainwindow.ui

DISTFILES += \
    google_maps.html \
    js.js

RESOURCES += \
    map.qrc
