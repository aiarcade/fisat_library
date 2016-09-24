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

    QHBoxLayout *searchLayout = new QHBoxLayout;

    bottomLayout->addItem(searchLayout);


    searchInput= new QLineEdit;

    searchInput->setPlaceholderText("Search for book ");

    QPushButton *searchButton = new QPushButton("Search");

    connect(searchButton,SIGNAL(clicked()),this,SLOT(search()));


    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);

     searchView= new QTableWidget;



    //searchView->setColumnCount(4);
    //searchView->setRowCount(50);


     bottomLayout->addWidget(searchView);









    QWidget *window = new QWidget();
    window->setLayout(mainLayout);

            // Set QWidget as the central layout of the main window
    setCentralWidget(window);








}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("172.16.170.1");
        db.setDatabaseName("FICDB");
        db.setUserName("mahesh");
        db.setPassword("mahesh");
        if (!db.open())
        {
          QMessageBox::critical(0, QObject::tr("Database Error"),
                    db.lastError().text());
        }

        QString userQuery=searchInput->text();
        QString sqlText("select * from L_BookDtls where L_BD_cTitle like '%"+userQuery+
                        "%' or L_BD_cAccessionNo like '%"+userQuery+
                        "%' or L_BD_cKeyWords like '%"+userQuery+
                        "%' or L_BD_cAuthor like '%"+userQuery+
                        "%' or L_BD_cCoAuthor like '%"+userQuery+
                        "%' or  L_BD_cCallNo like '%"+userQuery+"%'");

        QSqlQuery query(sqlText);


        searchView->setColumnCount(5);
        searchView->setRowCount(query.size());
        QStringList headers;
        headers<< "Accession No" << "Call No" <<"Author" <<"Title" << "Location";

        searchView->setHorizontalHeaderLabels(headers);
        searchView->setColumnWidth(3,300);
        searchView->setColumnWidth(2,700);

        int index=0;
        while (query.next())
        {
        searchView->setItem(index,0,new QTableWidgetItem(query.value(1).toString()));
        searchView->setItem(index,1,new QTableWidgetItem(query.value(2).toString()));
        searchView->setItem(index,2,new QTableWidgetItem(query.value(4).toString()));
        searchView->setItem(index,3,new QTableWidgetItem(query.value(8).toString()));
        index++;
        }






}
