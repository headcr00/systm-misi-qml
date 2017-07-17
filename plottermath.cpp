#include "plottermath.h"
#include <QDebug>
#include <QPointF>
#include "misiparams_typedef.h"
bool variantLessThan(const QPointF &v1, const QPointF &v2);
Plottermath::Plottermath(QObject *parent) : QObject(parent)
{
    x = new QVector<double>;
    adc0 = new QVector<double>;
    adc1 = new QVector<double>;
    adc2 = new QVector<double>;
    err1 = new QVector<double>;
    err5 = new QVector<double>;
    errpoints = new QList<QPointF>;

}

void Plottermath::pm_cleardata()
{
    adc0->clear();
    adc1->clear();
    adc2->clear();
    err1->clear();
    err5->clear();
    errpoints->clear();
    x->clear();

}

void Plottermath::getRefData(MisiParams mp)
{
   mparams = mp;
}

void Plottermath::getVoltData(int *arr)
{
    double measres1;
    double measres2;
    static double errgauge;
    double medianerr1;
    double medianerr5;
    double koeff = 0.1;
    // Work in progress here
    QVector<int> edistrx;
    QVector<int> edistry;

    //Ends here
    if (x->size() == 0)
        x->append(0.001);
    else
        x->append(x->last()+0.001);
    if (mparams.useMcuVolt == true)
    {
        adc0->append((*arr)*mparams.mcuVolt/(4096*1000));
        adc1->append(*(arr+1)*mparams.mcuVolt/(4096*1000));
        adc2->append(*(arr+2)*mparams.mcuVolt/(4096*1000));
    }
    else
    {
        adc0->append((*arr)*mparams.refvolt/(1000*(*(arr+2))));
        adc1->append(*(arr+1)*mparams.refvolt/(1000*(*(arr+2))));
        adc2->append(*(arr+2)*mparams.mcuVolt/(4096*1000));
    }
    measres1 = mparams.submres*(mparams.cblockres*((mparams.supvolt/adc0->last())*mparams.shuntres-mparams.protres-mparams.shuntres)/(mparams.cblockres-(mparams.supvolt/adc0->last())*mparams.shuntres+mparams.protres+mparams.shuntres)-mparams.lineres)/(mparams.submres+mparams.lineres-mparams.cblockres*((mparams.supvolt/adc0->last())*mparams.shuntres-mparams.protres-mparams.shuntres)/(mparams.cblockres-(mparams.supvolt/adc0->last())*mparams.shuntres+mparams.protres+mparams.shuntres));
    err1->append(abs(100-(measres1*100/resistance)));
    measres2 = mparams.submres*(mparams.cblockres*((mparams.supvolt/(adc1->last()/10))*mparams.shuntres-mparams.protres-mparams.shuntres)/(mparams.cblockres-(mparams.supvolt/(adc1->last()/10))*mparams.shuntres+mparams.protres+mparams.shuntres)-mparams.lineres)/(mparams.submres+mparams.lineres-mparams.cblockres*((mparams.supvolt/(adc1->last()/10))*mparams.shuntres-mparams.protres-mparams.shuntres)/(mparams.cblockres-(mparams.supvolt/(adc1->last()/10))*mparams.shuntres+mparams.protres+mparams.shuntres));
    err5->append(abs(100-(measres2*100/resistance)));


    foreach(double i, *err1)
    {
        medianerr1 = (i + medianerr1)/2;

    }

    foreach(double i, *err5)
    {
        medianerr5 = (i + medianerr5)/2;

    }

    if (medianerr1 > medianerr5)
    {
        errgauge = koeff * medianerr5 + (1 - koeff)*errgauge;
    }
    else
    {
        errgauge = koeff * medianerr1 + (1 - koeff)*errgauge;
    }


    if (x->size() > 1024)
    {
        x->removeFirst();
        adc0->removeFirst();
        adc1->removeFirst();
        adc2->removeFirst();
        err1->removeFirst();
        err5->removeFirst();
    }
    errpoints->clear();
    //Work in progress here

    foreach (double i, medianerr1 > medianerr5 ?  *err5 : *err1)
    {
        int index;

        index = searchpoint_x(static_cast<int>(i));


        if (index >= 0)
        {
            (*errpoints)[index].setY(errpoints->at(index).y() + 1);
        }
        else
        {
            errpoints->append(QPointF(static_cast<int>(i), 1));
        }
    }

    qSort(errpoints->begin(), errpoints->end(), variantLessThan);
    norm_points(errpoints);
    //qDebug() << errgauge << measres1 << measres2;
    emit sendmedianerr(errgauge);
    emit senderrdistr(errpoints);
    emit sendvoltagedata(*x,*adc0,*adc1,*adc2);
    emit senderrordata(*x, *err1, *err5);

}

void Plottermath::getResistance(int res)
{
    resistance = res;
}

int Plottermath::searchpoint_x(int x)
{
    for (int i = 0; i < errpoints->size(); i++)
    {
        int point = static_cast<int>((*errpoints)[i].x());
        if (point == x)
            return i;
    }
    return -1;

}

void Plottermath::norm_points(QList<QPointF> *plist)
{
    double maxval = 0;

    foreach (QPointF pt, *plist) {
        if (pt.y() > maxval)
            maxval = static_cast<double>(pt.y());

    }

    for (int i = 0; i < plist->size(); i++)
    {
        (*plist)[i].setY((*plist)[i].y()/maxval);
    }

}

// Compare two variants.
bool variantLessThan(const QPointF &v1, const QPointF &v2)
{
    return v1.x() < v2.x();
}

