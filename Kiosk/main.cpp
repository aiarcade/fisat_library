#include "mainwindow.h"
#include <QApplication>
#include <QPluginLoader>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;

    //w.showFullScreen();
    w.show();

    return a.exec();
}
