#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mapWindow = new MapWindow(this);
    this->arduino = new Arduino();
    connect(arduino, SIGNAL(dataRead(float)), this, SLOT(receiveData(float)));
    connect(this, SIGNAL(updateLocation(double,double)), mapWindow, SLOT(updateLocation(double,double)));
    connectToArduino();
    this->mapWindow->show();
}

void MainWindow::connectToArduino() {
    if(not this->arduino->open(Arduino::ARDUINO_VENDOR_ID, Arduino::ARDUINO_UNO_PRODUCT_ID)) {
        int reply = QMessageBox::question(this, "Arduino not found!",
                                          "No Arduino has been detected, please connect one to a USB port and click \'Retry\'",
                                          QMessageBox::Retry, QMessageBox::Cancel);
        if (reply == QMessageBox::Retry) {
            connectToArduino();
            qDebug() << "Retry";
        }
        else {
            exit(EXIT_FAILURE);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveData(float dataReceived) { //TODO
    double data = (double) dataReceived;
    emit updateAltitude(data);
    emit updateLocation(data, data);
    emit updateVelocity(data);
    emit updatePitch(data);
    emit updateRoll(data);
    emit updateYaw(data);
}
