#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QMainWindow>
#include <QtWebEngineWidgets>
#include <QWebEngineView>

namespace Ui {
class MapWindow;
}

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();

public slots:

    void updateLocation(double latitude, double longitude);

private:
    Ui::MapWindow *ui;
};

#endif // MAPWINDOW_H
