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
    void sendMessage(QString message);

public slots:

    void read();

signals:

    void packet1Read(double, double, double, double, double, double);
    void packet2Read(double, double, double, double, double);
    void messageRead(QString);

private:
    QSerialPort* arduino_port;
    bool isOpen = false;

    void processLine(QByteArray data);
    QVector<double> unpack(QByteArray packet, int elements);
    double byteArrayToDouble(QByteArray data);
};

#endif // ARDUINO_H
