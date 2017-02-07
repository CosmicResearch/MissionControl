#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QtWebEngineWidgets>
#include <QWebEngineView>
#include <QtPositioning>
#include "arduino.h"
#include <QLineSeries>
#include <QChart>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectToArduino();

signals:

    void updateAltitude(double);
    void updateLatitude(double);
    void updateLongitude(double);
    void updateVelocity(double);
    void updatePitch(double);
    void updateRoll(double);
    void updateYaw(double);
    void updateTemperature(double);

public slots:

    void receivePacket1(double time, double pressure, double temperature, double roll, double pitch, double yaw);
    void receivePacket2(double time, double altitude, double velocity, double latitude, double longitude);
    void positionUpdated(QGeoPositionInfo info);
    void echo();

private:
    Ui::MainWindow *ui;
    Arduino* arduino;
    QVector<double> time_altitude, altitude;
    QVector<double> time_velocity, velocity;
    double maxAltitude = 10;
    double maxTime = 10;
    double maxVelocity = 10;
    void newLocation(double latitude, double longitude);
    void newAltitude(double time, double altitude);
    void newVelocity(double time, double velocity);
    bool firstLocation = true;
};

#endif // MAINWINDOW_H
