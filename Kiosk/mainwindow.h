#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

#include <QDebug>
#include"searchwidget.h"
#include "glwidget.h"
#include "proximityreader.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    GLWidget *screensaver;
    ProximityReader *facedetector;
    void enableSearchWidget();
    void enableScreenSaver();

    ~MainWindow();

private:

    Ui::MainWindow *ui;
    int activeWidget; //0 for sc, 1 for search
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QVBoxLayout *bottomLayout;
    SearchWidget *swidget;
    QTimer *widgetTimer;
private slots:
       void updateWidgets();


};

#endif // MAINWINDOW_H
