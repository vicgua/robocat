#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("RoboCAT");
    MainWindow w;
    w.show();

    return a.exec();
}
