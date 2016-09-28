#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "glmap.h"
#include "dbhelper.h"
class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = 0);
    QLabel *bgLabel;
    QPixmap bgPixmap;
    QTimer *routeTimer;
    DbHelper *cdata;

    QString title;
    QString callNo;

    void setLocation(QString);
    void setTitle(QString,QString);



    void renderMap();

    int i;

    QList<QByteArray> loc;

signals:

public slots:
    void routeBlink();
     void closeMap();

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MAPWIDGET_H
