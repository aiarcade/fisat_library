#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>

#include <QPushButton>
#include <QHBoxLayout>



#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>


#include "mapwidget.h"

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = 0);
    void fillDummyData();
    QList<QStringList> duserQuery(QString);




signals:

public slots:

private:
    QTableWidget * searchView;
    QLineEdit *searchInput;
   // MapWidget *libMap;

private slots:
    void search();
    void resultCellClicked(int, int);



};

#endif // SEARCHWIDGET_H
