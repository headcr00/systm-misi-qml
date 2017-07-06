#include "plottermath.h"
#include <QDebug>
Plottermath::Plottermath(QObject *parent) : QObject(parent)
{
    x = new QVector<double>;
    adc0 = new QVector<double>;
    adc1 = new QVector<double>;
    adc2 = new QVector<double>;
    err1 = new QVector<double>;
    err5 = new QVector<double>;

}

void Plottermath::getRefData(int adc, int volt)
{

}

void Plottermath::getVoltData(int *arr)
{
    double measres1;
    double measres2;
    if (x->size() == 0)
        x->append(0.001);
    else
        x->append(x->last()+0.001);
    adc0->append((*arr)*3.333/4096);
    adc1->append(*(arr+1)*3.333/4096);
    adc2->append(*(arr+2)*3.333/4096);

    measres1 =((((60*32396) / adc0->last())-1001460-32396)*13544900)/(13544900-((60*32396)/adc0->last())+1001460+32396);
    err1->append(100-(measres1*100/resistance));
    measres2=((((59.96*32396)/(adc1->last()/5+1.231))-1001460-32396)*13544900)/(13544900-((59.96*32396)/(adc1->last()/5+1.231))+1001460+32396);
    qDebug() << adc1->last();
    err5->append(100-(measres2*100/resistance));
    qDebug()<< measres1 << measres2;


    if (x->size() > 1024)
    {
        x->removeFirst();
        adc0->removeFirst();
        adc1->removeFirst();
        adc2->removeFirst();
        err1->removeFirst();
        err5->removeFirst();
    }




    emit sendvoltagedata(*x,*adc0,*adc1,*adc2);


    emit senderrordata(*x, *err1, *err5);

}

void Plottermath::getResistance(int res)
{
    resistance = res;
}
