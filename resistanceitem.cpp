#include "resistanceitem.h"
#include <QDebug>

ResistanceItem::ResistanceItem(QString  name, int res, QObject *parent) : QObject(parent)
{
    rres = res;
    rname.append(name);
}


