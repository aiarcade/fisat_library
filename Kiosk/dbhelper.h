#ifndef DBHELPER_H
#define DBHELPER_H
#include <QStringList>



class DbHelper
{
public:
    DbHelper();
    QStringList getHighlights(int printWidth);
};

#endif // DBHELPER_H
