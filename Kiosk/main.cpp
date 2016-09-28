#include "mainwindow.h"
#include <QApplication>
#include <QPluginLoader>
#include <QFontDatabase>
#include <QFile>


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);


    QStringList list;
    list << "goodtimes.ttf";
    int fontID(-1);
    bool fontWarningShown(false);
    for (QStringList::const_iterator constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator) {
        QFile res(":/fonts/" + *constIterator);
        if (res.open(QIODevice::ReadOnly) == false) {
            if (fontWarningShown == false) {
                QMessageBox::warning(0, "Application", (QString)"Cant open fonts " + QChar(0x00AB) + " DejaVu Serif " + QChar(0x00BB) + ".");
                fontWarningShown = true;
            }
        } else {
            fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
            if (fontID == -1 && fontWarningShown == false) {
                QMessageBox::warning(0, "Application", (QString)"Cant open fonts  " + QChar(0x00AB) + " DejaVu Serif " + QChar(0x00BB) + ".");
                fontWarningShown = true;
            }
        }
    }



    MainWindow w;

    w.showFullScreen();
    w.show();

    return a.exec();
}
