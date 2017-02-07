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

void Arduino::processLine(QByteArray data) {
    int i = 0;
    while (i < data.size() and not (data.at(i) =='\r')) {
        ++i;
    }
    data.truncate(i);
    if (data.size() > 0) {
        if (data.at(0) == (char)'0') {
            QByteArray packet = data.right(data.size()-1);
            QVector<double> unpacked = unpack(packet, 6);
            emit packet1Read(unpacked[0], unpacked[1], unpacked[2], unpacked[3], unpacked[4], unpacked[5]);
        }
        else if(data.at(0) == (char)'1') {
            QByteArray packet = data.right(data.size()-1);
            QVector<double> unpacked = unpack(packet, 5);
            emit packet2Read(unpacked[0], unpacked[1], unpacked[2], unpacked[3], unpacked[4]);
        }
        else {
            emit messageRead(QString(data));
        }
    }
}

QVector<double> Arduino::unpack(QByteArray packet, int elements) {
    QVector<double> res = QVector<double>(elements);
    for (int i = 0; i < elements; ++i) {
        res[i] = byteArrayToDouble(packet.mid(8*i, 8));
    }
    return res;
}

double Arduino::byteArrayToDouble(QByteArray data) {
    float output;
    *((uchar*)(&output) + 7) = data[7];
    *((uchar*)(&output) + 6) = data[6];
    *((uchar*)(&output) + 5) = data[5];
    *((uchar*)(&output) + 4) = data[4];
    *((uchar*)(&output) + 3) = data[3];
    *((uchar*)(&output) + 2) = data[2];
    *((uchar*)(&output) + 1) = data[1];
    *((uchar*)(&output) + 0) = data[0];
    return (double)output;
}

void Arduino::sendMessage(QString message) {
    message = message.append("\n");
    this->arduino_port->write(message.toUtf8());
}
