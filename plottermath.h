#ifndef PLOTTERMATH_H
#define PLOTTERMATH_H

#include <QObject>

class Plottermath : public QObject
{
    Q_OBJECT
public:
    explicit Plottermath(QObject *parent = 0);

signals:
    void sendvoltagedata(QVector<double>, QVector<double>, QVector<double>, QVector<double>);
    void senderrordata(QVector<double>, QVector<double>,QVector<double>);
    void sendmedianerr(double);
public slots:
    void getRefData(int adc, int volt);
    void getVoltData(int * arr);
    void getResistance(int res);

private:
    int resistance = 10000;
    int referenceadc;
    int referencevoltage;
    QVector<double> * adc0;
    QVector<double> * adc1;
    QVector<double> * adc2;
    QVector<double> * err1;
    QVector<double> * err5;
    QVector<double> * x;

};

#endif // PLOTTERMATH_H
