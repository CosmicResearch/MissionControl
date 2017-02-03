#include "arduino.h"
#include <stdio.h>

Arduino::Arduino(QWidget* parent) {
    arduino_port = new QSerialPort();
    this->connect(arduino_port, SIGNAL(readyRead()), this, SLOT(read()));
}

Arduino::~Arduino() {
    arduino_port->close();
}

bool Arduino::open(quint16 vendorID, quint16 productID) {
    QSerialPortInfo info;
    QList<QSerialPortInfo> list = info.availablePorts();
    foreach (info, list) {
        if (info.productIdentifier() == productID and info.vendorIdentifier() == vendorID) {
            arduino_port->setPort(info);
        }
    }
    arduino_port->setBaudRate(115200);
    arduino_port->setDataBits(QSerialPort::Data8);
    arduino_port->setParity(QSerialPort::NoParity);
    arduino_port->setStopBits(QSerialPort::OneStop);
    arduino_port->setFlowControl(QSerialPort::NoFlowControl);

    isOpen = arduino_port->open(QSerialPort::ReadWrite);
    return isOpen;
}

bool Arduino::open(QString port) {
    arduino_port->setPortName(port);
    arduino_port->setBaudRate(115200);
    arduino_port->setDataBits(QSerialPort::Data8);
    arduino_port->setParity(QSerialPort::NoParity);
    arduino_port->setStopBits(QSerialPort::OneStop);
    arduino_port->setFlowControl(QSerialPort::NoFlowControl);

    isOpen = arduino_port->open(QSerialPort::ReadWrite);
    return isOpen;
}

void Arduino::read() {
    while(arduino_port->canReadLine()) {
        QByteArray line = arduino_port->readLine();
        processLine(line);
    }
}

void Arduino::processLine(QByteArray data) { //TODO
    float f = byteArrayToFloat(data);
    emit this->dataRead(f);
}

float Arduino::byteArrayToFloat(QByteArray data) {
    int i = 0;
    while (i < data.size() and not (data.at(i) =='\r')) {
        ++i;
    }
    data.truncate(i);
    QByteArray flipData = QByteArray();
    for (int i = data.size() - 1; i >= 0; --i) {
        flipData[data.size() - i -1] = data[i];
    }
    data = flipData;
    const unsigned char* charData = (const unsigned char*) data.toStdString().c_str();
    float output;
    *((uchar*)(&output) + 3) = charData[0];
    *((uchar*)(&output) + 2) = charData[1];
    *((uchar*)(&output) + 1) = charData[2];
    *((uchar*)(&output) + 0) = charData[3];
    return output;
}
