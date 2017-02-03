#include "mainwindow.h"
#include <QApplication>
#include <QtWebEngine>

int main(int argc, char *argv[])
{
    char* argv2[argc+1];
    for (int i = 0; i < argc; ++i) {
        argv2[i] = argv[i];
    }
    argv2[argc] = "--disable-web-security";
    int argc2 = argc+1;
    QApplication a(argc2, argv2);
    QtWebEngine::initialize();
    MainWindow w;
    w.show();

    return a.exec();
}
