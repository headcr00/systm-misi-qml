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
    /* legacy
    void sendvoltagedata(QVector<double>, QVector<double>, QVector<double>, QVector<double>);
    void senderrordata(QVector<double>, QVector<double>,QVector<double>);
    */
    void sendvoltagedata(QList<QPointF>*, QList<QPointF>*, QList<QPointF>*);
    void senderrordata(QList<QPointF>*, QList<QPointF>*);
    void senderrdistr(QList<QPointF>*);
    void sendmedianerr(double);


public slots:
    void getRefData(MisiParams mp);
    void getResistance(int res);
    void getSerialData(int * arr);
    void processSerialData();

private:
    int resistance = 10000;
    char counter = 0;
    MisiParams mparams;
    /*Legacy
    QVector<double> * adc0;
    QVector<double> * adc1;
    QVector<double> * adc2;
    QVector<double> * err1;
    QVector<double> * err5;
    QVector<double> * x;
    */
    QList<QPointF> * errpoints;
    QList<QPointF> * adc0points;
    QList<QPointF> * adc1points;
    QList<QPointF> * adc2points;
    QList<QPointF> * err1points;
    QList<QPointF> * err5points;

    int searchpoint_x(int x);
    void norm_points(QList<QPointF> *plist);



};

#endif // PLOTTERMATH_H
