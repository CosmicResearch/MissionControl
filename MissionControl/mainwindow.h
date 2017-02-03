#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include "mapwindow.h"
#include "arduino.h"

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
    void updateLocation(double, double);
    void updateVelocity(double);
    void updatePitch(double);
    void updateRoll(double);
    void updateYaw(double);

public slots:

    void receiveData(float data);

private:
    Ui::MainWindow *ui;
    Arduino* arduino;
    MapWindow* mapWindow;
};

#endif // MAINWINDOW_H
