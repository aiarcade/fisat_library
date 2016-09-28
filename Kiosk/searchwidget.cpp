#include "searchwidget.h"

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{



    QHBoxLayout *searchInLayout = new QHBoxLayout;

    searchInLayout->setSpacing(10);
    //searchInLayout->setGeometry();

    QVBoxLayout *searchLayout = new QVBoxLayout;


    searchInput= new QLineEdit;

    searchInput->setPlaceholderText("Search for book ");

    QPushButton *searchButton = new QPushButton("Search");
    searchButton->setFixedHeight(50);
    searchInput->setFixedHeight(30);

    connect(searchButton,SIGNAL(clicked()),this,SLOT(search()));



    searchInLayout->addWidget(searchInput);
    searchInLayout->addWidget(searchButton);

    searchLayout->addItem(searchInLayout);



    searchView= new QTableWidget;

    connect(searchView, SIGNAL(cellClicked(int, int)), this, SLOT(resultCellClicked(int, int)));

    QHBoxLayout *searchOutLayout = new QHBoxLayout;


    //searchView->setColumnCount(4);
    //searchView->setRowCount(50);


     searchOutLayout->addWidget(searchView);

      searchLayout->addItem(searchOutLayout);

      this->setLayout(searchLayout);


}



void SearchWidget::search()
{
   /* QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
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


    */
    QList<QStringList> results=duserQuery(searchInput->text());
    QStringList headers;
    headers<< "Accession No" << "Call No" <<"Author" <<"Title" << "Location";
    searchView->setColumnCount(5);
    searchView->setRowCount(results.length());
    searchView->setHorizontalHeaderLabels(headers);
    searchView->setColumnWidth(3,300);
    searchView->setColumnWidth(2,700);

    for(int index=0;index<results.length();index++)
    {
        searchView->setItem(index,0,new QTableWidgetItem(results[index][0]));
        searchView->setItem(index,1,new QTableWidgetItem(results[index][1]));
        searchView->setItem(index,2,new QTableWidgetItem(results[index][2]));
        searchView->setItem(index,3,new QTableWidgetItem(results[index][3]));

    }


}

void SearchWidget::resultCellClicked(int r, int c)
{
    QString callNo=searchView->item(r, 1 )->text();
    MapWidget *libMap = new MapWidget();
    libMap->setLocation(callNo);

    libMap->setTitle(searchView->item(r, 2)->text(),
                     searchView->item(r, 1)->text());
    libMap->renderMap();
    libMap->show();
}

void SearchWidget::fillDummyData()
{
    QStringList headers;
    headers<< "Accession No" << "Call No" <<"Title" <<"Author" << "Location";
    searchView->setColumnCount(5);
    searchView->setRowCount(10);
    searchView->setHorizontalHeaderLabels(headers);
    searchView->setColumnWidth(3,300);
    searchView->setColumnWidth(2,700);

    for(int index=0;index<10;index++)
    {
        searchView->setItem(index,0,new QTableWidgetItem("123"));
        searchView->setItem(index,1,new QTableWidgetItem("2345"));
        searchView->setItem(index,2,new QTableWidgetItem("Intro to CS"));
        searchView->setItem(index,3,new QTableWidgetItem("Mahesh"));

    }



}

QList<QStringList>SearchWidget::duserQuery(QString userIn)
{

    QList<QStringList>  rdata;
    QString sqlText("select * from L_BookDtls where L_BD_cTitle like '%"+userIn+
                    "%' or L_BD_cAccessionNo like '%"+userIn+
                    "%' or L_BD_cKeyWords like '%"+userIn+
                    "%' or L_BD_cAuthor like '%"+userIn+
                    "%' or L_BD_cCoAuthor like '%"+userIn+
                    "%' or  L_BD_cCallNo like '%"+userIn+"%'");

    QSqlQuery query(sqlText);
    int index=0;
    while (query.next())
    {
        QStringList _temp;
        _temp << query.value(1).toString() << query.value(2).toString() << query.value(4).toString()
             << query.value(8).toString();
        rdata.append(_temp);
    }
    return rdata;



}

