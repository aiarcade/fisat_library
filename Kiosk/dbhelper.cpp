#include "dbhelper.h"

DbHelper::DbHelper()
{

}

QStringList DbHelper::getHighlights(int printWidth)
{
    QStringList hl;
    QString ele=QString("BOOK TITLES+");
    QString val=QString(":15290");
    hl.append(ele+val);



    ele=QString("BOOK VOLUME+");
    val=QString(":65929");
    hl.append(ele+val);

    ele=QString("JOURNAL PRINT+");
    val=QString(":267");
    hl.append(ele+val);

    ele=QString("NPTEL COURSE+");
    val=QString(":291");
    hl.append(ele+val);


    ele=QString("NEWS PAPER+");
    val=QString(":26");
    hl.append(ele+val);

    ele=QString("DVD+");
    val=QString(":2347");
    hl.append(ele+val);
    return hl;
}
