#include "mapwidget.h"

MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{

    cdata = new DbHelper();




}

void MapWidget::setLocation(QString callNo)
{

    loc=cdata->getLocation(callNo);
}

void MapWidget::setTitle(QString t, QString c)
{
    title=t;
    callNo=c;
}

void MapWidget::renderMap()
{



    QGridLayout *topLayout=new  QGridLayout(this);
      //*topLayout=new   QGridLayout ;

//FLOOR,SECTION,STACK_ROOM,SHELF_NO,ROW,SUBJECT,CALLNO_FROM,CALLNO_TO

    QFont m( "goodtimes", 30, QFont::Bold);

    QLabel *titleLabel= new QLabel();
    titleLabel->setText(title);

   titleLabel->setFont( m);
   titleLabel->setWordWrap(true);



    QLabel *callLabel= new QLabel();
    callLabel->setFont(m);
    callLabel->setText("CALL NO: "+callNo);
    callLabel->setFixedHeight(100);


    QFont f( "goodtimes", 22, QFont::Bold);

    QLabel *floorLabel= new QLabel();
    floorLabel->setText("FLOOR: "+loc[0]);

     floorLabel->setFont( f);

    QLabel *secLabel= new QLabel();
    secLabel->setFont( f);
    secLabel->setText("SECTION: "+loc[1]);

    QLabel *stackLabel= new QLabel();
    stackLabel->setFont( f);
    stackLabel->setText("STACK ROOM NO: "+loc[2]);

    QLabel *shelfLabel= new QLabel();
    shelfLabel->setFont( f);
   shelfLabel->setText("SHELF: "+loc[3]);

   QLabel *rowLabel= new QLabel();
   rowLabel->setFont( f);
   rowLabel->setText("ROW: "+loc[4]);


    QLabel *subLabel= new QLabel();
    subLabel->setFont( f);
    subLabel->setText("SUBJECT: "+loc[5]);

    topLayout->addWidget(titleLabel,0,0,1,2);
    topLayout->addWidget(callLabel,1,0,1,2);




    topLayout->addWidget(floorLabel,2,0);

    topLayout->addWidget(secLabel,2,1);

    topLayout->addWidget(stackLabel,3,0);

    topLayout->addWidget(shelfLabel,3,1);


    topLayout->addWidget(subLabel,4,0);

    topLayout->addWidget(rowLabel,4,1);



    QString iname;

    if(loc[1].indexOf('GENERAL')>-1)
        iname=":/images/general.png";
    if(loc[1].indexOf("REFERENCE")>-1)
        iname=":/images/mcareference.png";
     if(loc[1].indexOf("ENGINEERING REFERENCE")>-1)
         iname=":/images/generalreference.png";
     if(loc[1].indexOf("BANK")>-1)
         iname=":/images/bookbank.png";

     qDebug()<<iname;

    QImage level1Image= QImage(iname);
    this->setGeometry(QRect(0,0,level1Image.width(),level1Image.height()));
    bgLabel=new QLabel(this);
    bgLabel->setGeometry(0,0,this->width(),this->height());

    bgPixmap=QPixmap::fromImage(level1Image);


    //QVBoxLayout *bottomLayout = new QVBoxLayout(this);



    QPushButton *closebttn = new QPushButton("BACK");
    closebttn->setFixedHeight(100);
    closebttn->setFont(m);


     connect(closebttn,SIGNAL(clicked()),this,SLOT(closeMap()));


    QPainter painter(&bgPixmap);


    painter.setRenderHint(QPainter::Antialiasing);
    //painter.drawImage(0,0,level1Image);
    painter.end();


    bgLabel->setPixmap(bgPixmap);

     //mainLayout->addWidget(locLabel);

    topLayout->addWidget(closebttn,5,0,1,2);

    topLayout->addWidget(bgLabel,6,0,1,2);


    routeTimer = new QTimer(this);

    //activeWidget=0;

    connect( routeTimer , SIGNAL(timeout()), this, SLOT(routeBlink()));
    i=0;
    //routeTimer ->start(5000);

}

void MapWidget::routeBlink()
{
   int path[]={ 539, 216,
    387, 624,
    408, 621,
    431 ,620,
    457, 619,
    488, 614,
    488, 600,
    499, 576,
    538, 568,
    572, 570,
    590, 570,
    614, 572};
   QPainter painter(&bgPixmap);
   painter.setPen(Qt::black);
   if(i>=24) i=0;
        painter.drawLine(path[i],path[i+1],path[i+2],path[i+3]);
   i=i+4;

   bgLabel->setPixmap(bgPixmap);



}

void MapWidget::closeMap()
{
    this->close();
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->x()<<event->y();
}
