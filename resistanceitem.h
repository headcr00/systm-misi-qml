#ifndef RESISTANCEITEM_H
#define RESISTANCEITEM_H

#include <QObject>

class ResistanceItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString rname MEMBER rname NOTIFY rnameNotify)
    Q_PROPERTY(int rres MEMBER rres NOTIFY rresNotify)

public:
    explicit ResistanceItem(QString name, int res, QObject *parent = 0);

signals:
    void resistanceChanged(int res);
    void rnameNotify();
    void rresNotify();



private:
    QString rname;
    int rres;

};

#endif // RESISTANCEITEM_H
