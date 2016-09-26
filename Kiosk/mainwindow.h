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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    GLWidget *screensaver;
    ~MainWindow();

private:

    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
