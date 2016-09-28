#include "dbhelper.h"


DbHelper::DbHelper()
{
    QFile file(":db/lib.csv");
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();

        }
        ;

        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            locationData.append(line.split(','));

        }
     db = QSqlDatabase::addDatabase("QMYSQL");
     db.setHostName("172.16.170.1");
     db.setDatabaseName("FICDB");
     db.setUserName("mahesh");
     db.setPassword("mahesh");
     if (!db.open())
      {
          QMessageBox::critical(0, QObject::tr("Database Error"),
                            db.lastError().text());
      }

}

QStringList DbHelper::getHighlights(int printWidth)
{
    QStringList hl;
    QString ele=QString("BOOK TITLES+");
    QString val=QString(":15451");
    hl.append(ele+val);



    ele=QString("BOOK VOLUME+");
    val=QString(":66954");
    hl.append(ele+val);

    ele=QString("JOURNAL PRINT+");
    val=QString(":267");
    hl.append(ele+val);

    ele=QString("NPTEL COURSE+");
    val=QString(":260");
    hl.append(ele+val);


    ele=QString("NEWS PAPER+");
    val=QString(":26");
    hl.append(ele+val);

    ele=QString("DVD+");
    val=QString(":2500");
    hl.append(ele+val);
    return hl;
}

QString DbHelper::getQuoteOftheday()
{
    QString _quote="A single cloud can weight more than 1 million pounds";
    return _quote;
}

QImage DbHelper::getQuoteImage()
{
    QImage quoteImage;
    quoteImage.load("/tmp/el.jpg");
    return quoteImage;
}

unsigned int DbHelper::distance(const std::string& s1, const std::string& s2)
{
    const std::size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    d[0][0] = 0;
    for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
    for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

    for(unsigned int i = 1; i <= len1; ++i)
        for(unsigned int j = 1; j <= len2; ++j)
                      // note that std::min({arg1, arg2, arg3}) works only in C++11,
                      // for C++98 use std::min(std::min(arg1, arg2), arg3)
                      d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
    return d[len1][len2];
}

QList<QByteArray> DbHelper::getLocation(QString callNo)
{
        unsigned int similarity=500;
        //("FLOOR", "SECTION", "STACKROOM", "SHELF NO", "ROW", "SUBJECT",
        //"CALLNO FROM", "CALLNO TO\n")

        QList<QByteArray> temp;
        for(int i=0;i<locationData.length();i++)
        {
           int d= distance(locationData[i][6].toStdString(),callNo.toStdString()) ;
            if(d<similarity)
            {
                similarity=d;
                temp=locationData[i];

            }



        }

        qDebug()<<similarity<<locationData.length();
        return temp;
}
