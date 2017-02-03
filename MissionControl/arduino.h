#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QWidget *parent = 0);
    ~Arduino();

    bool open(quint16 vendorID, quint16 productID);
    bool open(QString port);
    static const quint16 ARDUINO_VENDOR_ID = 9025;
    static const quint16 ARDUINO_UNO_PRODUCT_ID = 579;

public slots:

    void read();

signals:

    void dataRead(float);

private:
    QSerialPort* arduino_port;
    bool isOpen = false;

    void processLine(QByteArray data);
    float byteArrayToFloat(QByteArray data);
};

#endif // ARDUINO_H
