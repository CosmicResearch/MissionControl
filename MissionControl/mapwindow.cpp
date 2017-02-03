#include "mapwindow.h"
#include "ui_mapwindow.h"

MapWindow::MapWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapWindow)
{
    ui->setupUi(this);
    Q_INIT_RESOURCE(map);
    QUrl url = QUrl("qrc:///mapfiles/google_maps.html");
    ui->webEngineView->load(url);
}

MapWindow::~MapWindow()
{
    delete ui;
}

void MapWindow::updateLocation(double latitude, double longitude) {
    QString str = QString("var newLoc = new google.maps.LatLng(%1, %2); ").arg(latitude).arg(longitude) +
            QString("map.setCenter(newLoc);") + QString("marker.setPosition(newLoc);");
    ui->webEngineView->page()->runJavaScript(str);
}
