#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

     ui->setupUi(this);


    mainLayout = new QVBoxLayout;

    topLayout = new QHBoxLayout;


    mainLayout->addItem(topLayout);



    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");
    QPushButton *button3 = new QPushButton("Three");
    QPushButton *button4 = new QPushButton("Four");
    QPushButton *button5 = new QPushButton("Five");


    topLayout->addWidget(button1);
    topLayout->addWidget(button2);
    topLayout->addWidget(button3);
    topLayout->addWidget(button4);
    topLayout->addWidget(button5);


     bottomLayout = new QVBoxLayout;

    mainLayout->addItem(bottomLayout);

    swidget= new SearchWidget();




    bottomLayout->addWidget(swidget);
    screensaver= new GLWidget();
    bottomLayout->addWidget(screensaver);
    screensaver->updateGL();
    //screensaver->paintGL();










    QWidget *window = new QWidget();
    window->setLayout(mainLayout);

            // Set QWidget as the central layout of the main window
    setCentralWidget(window);

    facedetector= new ProximityReader();


    widgetTimer = new QTimer(this);

    activeWidget=0;

    connect(widgetTimer, SIGNAL(timeout()), this, SLOT(updateWidgets()));
        widgetTimer->start(1000);







}

void MainWindow::enableSearchWidget()
{

    if(activeWidget==1)
        return

           /* bottomLayout->removeWidget(screensaver);
            delete screensaver;
            swidget= new SearchWidget();
            bottomLayout->addWidget(swidget);*/
            screensaver->hide();
            swidget->show();
            activeWidget=1;





}

void MainWindow::enableScreenSaver()
{

            if(activeWidget==0)
                return
/*
            bottomLayout->removeWidget(swidget);
            delete swidget;
            screensaver= new GLWidget();
            bottomLayout->addWidget(screensaver);
            screensaver->updateGL();*/
            swidget->hide();
            screensaver->show();
            activeWidget=0;
            qDebug()<<"enabled sc";



}
void MainWindow::updateWidgets()
{
    qDebug()<<"times up"<<facedetector->isPerson()<<activeWidget;
    if(facedetector->isPerson()==0) enableScreenSaver();
    else enableSearchWidget();
}


MainWindow::~MainWindow()
{
    delete ui;
}

