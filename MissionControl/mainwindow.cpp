#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->arduino = new Arduino();
    connect(arduino, SIGNAL(packet1Read(double,double,double,double,double,double)), this, SLOT(receivePacket1(double,double,double,double,double,double)));
    connect(arduino, SIGNAL(packet2Read(double,double,double,double,double)), this, SLOT(receivePacket2(double,double,double,double,double)));
    connect(arduino, SIGNAL(messageRead(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)));
    Q_INIT_RESOURCE(map);
    QUrl url = QUrl("qrc:///mapfiles/google_maps.html");
    ui->webEngineView->load(url);
    altitude = QVector<double>();
    time_altitude = QVector<double>();
    ui->altitudePlot->addGraph();
    ui->altitudePlot->graph(0)->setData(time_altitude, altitude);
    ui->altitudePlot->xAxis->setLabel("Time");
    ui->altitudePlot->yAxis->setLabel("Altitude");
    ui->altitudePlot->xAxis->setRange(0, maxTime);
    ui->altitudePlot->yAxis->setRange(0, maxVelocity);
    velocity = QVector<double>();
    time_velocity = QVector<double>();
    ui->velocityPlot->addGraph();
    ui->velocityPlot->graph(0)->setData(time_velocity, velocity);
    ui->velocityPlot->xAxis->setLabel("Time");
    ui->velocityPlot->yAxis->setLabel("Velocity");
    ui->velocityPlot->xAxis->setRange(0, maxTime);
    ui->velocityPlot->yAxis->setRange(0, maxVelocity);
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source) {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        source->startUpdates();
    }
    connectToArduino();
}

void MainWindow::connectToArduino() {
    if(!this->arduino->open(Arduino::ARDUINO_VENDOR_ID, Arduino::ARDUINO_UNO_PRODUCT_ID)) {
        int reply = QMessageBox::question(this, "Arduino not found!",
                                          "No Arduino has been detected, please connect one to a USB port and click \'Retry\'",
                                          QMessageBox::Retry, QMessageBox::Cancel);
        if (reply == QMessageBox::Retry) {
            connectToArduino();
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

void MainWindow::receivePacket1(double time, double pressure, double temperature, double roll, double pitch, double yaw) {
    emit updateTemperature(temperature);
    emit updateRoll(roll);
    emit updatePitch(pitch);
    emit updateYaw(yaw);
}

void MainWindow::receivePacket2(double time, double altitude, double velocity, double latitude, double longitude) {
    newAltitude(time, altitude);
    newLocation(latitude, longitude);
    newVelocity(time, velocity);
    qDebug() << "sources: " << QGeoPositionInfoSource::availableSources();
}

void MainWindow::newLocation(double latitude, double longitude) {
    QString str = QString("var newLoc = new google.maps.LatLng(%1, %2); ").arg(latitude).arg(longitude) +
            /*QString("map.setCenter(newLoc);") +*/ QString("marker.setPosition(newLoc);");
    ui->webEngineView->page()->runJavaScript(str);
    emit updateLatitude(latitude);
    emit updateLongitude(longitude);
}

void MainWindow::positionUpdated(QGeoPositionInfo info) {
    QString str = QString("var newLoc = new google.maps.LatLng(%1, %2); ").arg(info.coordinate().latitude()).arg(info.coordinate().longitude()) + QString("position.setPosition(newLoc);");
    if (firstLocation) {
        firstLocation = false;
        str += QString("map.setCenter(newLoc);");
    }
    ui->webEngineView->page()->runJavaScript(str);
}

void MainWindow::newAltitude(double time, double altitude) {
    time_altitude.push_back(time);
    this->altitude.push_back(altitude);
    ui->altitudePlot->graph(0)->setData(time_altitude, this->altitude, false);
    if (altitude > maxAltitude) {
        maxAltitude = altitude;
        ui->altitudePlot->yAxis->setRange(0, altitude);
    }
    if (time > maxTime) {
        maxTime = time;
    }
    ui->altitudePlot->xAxis->setRange(0, maxTime);
    ui->altitudePlot->replot();
    emit updateAltitude(altitude);
}

void MainWindow::newVelocity(double time, double velocity) {
    time_velocity.push_back(time);
    this->velocity.push_back(velocity);
    ui->velocityPlot->graph(0)->setData(time_velocity, this->velocity, false);
    if (velocity > maxVelocity) {
        maxVelocity = velocity;
        ui->velocityPlot->yAxis->setRange(0, velocity);
    }
    if (time > maxTime) {
        maxTime = time;
    }
    ui->velocityPlot->xAxis->setRange(0, maxTime);
    ui->velocityPlot->replot();
    emit updateVelocity(velocity);
}

void MainWindow::echo() {
    this->arduino->sendMessage("ECHO");
}
