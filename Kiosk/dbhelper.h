#ifndef DBHELPER_H
#define DBHELPER_H
#include <QStringList>
#include <QImage>
#include <QDebug>
#include <QFile>
#include<string>

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>





class DbHelper
{
public:
    DbHelper();
    QStringList getHighlights(int printWidth);
    QString getQuoteOftheday();
    QImage getQuoteImage();
    QList<QByteArray> getLocation(QString callNo);
    QList<QList<QByteArray>>locationData;
    QSqlDatabase db;



    unsigned int distance(const std::string& s1, const std::string& s2);
};

#endif // DBHELPER_H
