#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

     ui->setupUi(this);


    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *topLayout = new QHBoxLayout;


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


     QVBoxLayout *bottomLayout = new QVBoxLayout;

    mainLayout->addItem(bottomLayout);

    SearchWidget *swidget= new SearchWidget(this);




    bottomLayout->addWidget(swidget);
    screensaver= new GLWidget(this);
    bottomLayout->addWidget(screensaver);
    screensaver->updateGL();
    //screensaver->paintGL();










    QWidget *window = new QWidget();
    window->setLayout(mainLayout);

            // Set QWidget as the central layout of the main window
    setCentralWidget(window);








}

MainWindow::~MainWindow()
{
    delete ui;
}

