#ifndef PLOTTERMATH_H
#define PLOTTERMATH_H
#include <QPointF>
#include <QObject>
#include "misiparams_typedef.h"

class Plottermath : public QObject
{
    Q_OBJECT
public:
    explicit Plottermath(QObject *parent = 0);
    void pm_cleardata();

signals:
    void sendvoltagedata(QVector<double>, QVector<double>, QVector<double>, QVector<double>);
    void senderrordata(QVector<double>, QVector<double>,QVector<double>);
    void senderrdistr(QList<QPointF>*);
    void sendmedianerr(double);


public slots:
    void getRefData(MisiParams mp);
    void getVoltData(int * arr);
    void getResistance(int res);

private:
    int resistance = 10000;
    MisiParams mparams;
    QVector<double> * adc0;
    QVector<double> * adc1;
    QVector<double> * adc2;
    QVector<double> * err1;
    QVector<double> * err5;
    QVector<double> * x;
    QList<QPointF> * errpoints;

    int searchpoint_x(int x);
    void norm_points(QList<QPointF> *plist);


};

#endif // PLOTTERMATH_H
