#include "resistanceitem.h"
#include <QDebug>
ResistanceItem::ResistanceItem(QString  name, int res, QObject *parent) : QObject(parent)
{
    rres = res;
    rname.append(name);

}

void ResistanceItem::clicked()
{
    qDebug()<< rname;
    emit resistanceChanged(rres);
}

