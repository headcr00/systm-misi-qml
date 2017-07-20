#include "plottermath.h"
#include <QDebug>
#include <QPointF>
#include "misiparams_typedef.h"
bool variantLessThan(const QPointF &v1, const QPointF &v2);
Plottermath::Plottermath(QObject *parent) : QObject(parent)
{
    errpoints = new QList<QPointF>;
    adc0points = new QList<QPointF>;
    adc1points = new QList<QPointF>;
    adc2points = new QList<QPointF>;
    err1points = new QList<QPointF>;
    err5points = new QList<QPointF>;
}

void Plottermath::pm_cleardata()
{
    adc0points->clear();
    adc1points->clear();
    adc2points->clear();
    err1points->clear();
    err5points->clear();

}

void Plottermath::getRefData(MisiParams mp)
{
   mparams = mp;
}



void Plottermath::getResistance(int res)
{
    resistance = res;
}

/*!
 * \brief Plottermath::getSerialData
 * Gets serial data from port and stores them in adc0, adc1 and adc2.
 *
 * ADC0 is channel 1, without amplification, ADC1 is x10, ADC2 is VREF.
 * ERR1 is error for 1st channel and ERR5 for second.
 *
 * \param arr - array of data
 */
void Plottermath::getSerialData(int *arr)
{

    if (adc0points->size() == 0)
    {
        adc0points->append(QPointF(0, (*arr)*mparams.mcuVolt/(4096*1000)));
        adc1points->append(QPointF(0, (*(arr+1)*mparams.mcuVolt/(4096*1000))));
        adc2points->append(QPointF(0, (*(arr+2)*mparams.mcuVolt/(4096*1000))));
    }

    if (mparams.useMcuVolt == true)
    {
        adc0points->append(QPointF(adc0points->last().x()+1, (*arr)*mparams.mcuVolt/(4096*1000)));
        adc1points->append(QPointF(adc0points->last().x()+1, (*(arr+1)*mparams.mcuVolt/(4096*1000))));
        adc2points->append(QPointF(adc0points->last().x()+1, (*(arr+2)*mparams.mcuVolt/(4096*1000))));
    }
    else
    {
        adc0points->append(QPointF(adc0points->last().x()+1, (*arr)*mparams.refvolt/(1000*(*(arr+2)))));
        adc1points->append(QPointF(adc0points->last().x()+1, (*(arr+1)*mparams.refvolt/(1000*(*(arr+2))))));
        adc2points->append(QPointF(adc0points->last().x()+1, (*(arr+2)*mparams.mcuVolt/(4096*1000))));
    }

    if (adc0points->size() > 1024)
    {
        adc0points->removeFirst();
        adc1points->removeFirst();
        adc2points->removeFirst();
    }


    counter++;


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
/*!
 * \brief Plottermath::processSerialData
 * This is main math function which calculates resistance and error. Uses Kahlmann filter for error gauge (GUI).
 * Called by timer.
 * Sends to plots via signals.
 */
void Plottermath::processSerialData()
{
    double measres1;
    double measres2;
    static double errgauge;
    double medianerr1;
    double medianerr5;
    double koeff = 0.1;
    static int xs;


    if (adc0points->size() == 0)
    {
        xs = 0;
        return;
    }

    if (xs == counter)
        return;

    xs = counter;


    err1points->clear();
    err5points->clear();

    foreach (QPointF p, *adc0points) {
        double i;
        i = p.y();
        measres1 = mparams.submres*(mparams.cblockres*((mparams.supvolt/i)*mparams.shuntres-mparams.protres-mparams.shuntres)/(mparams.cblockres-(mparams.supvolt/i)*mparams.shuntres+mparams.protres+mparams.shuntres)-mparams.lineres)/(mparams.submres+mparams.lineres-mparams.cblockres*((mparams.supvolt/i)*mparams.shuntres-mparams.protres-mparams.shuntres)/(mparams.cblockres-(mparams.supvolt/i)*mparams.shuntres+mparams.protres+mparams.shuntres));
        err1points->append(QPointF(p.x(), abs(100-(measres1*100/resistance))));
        medianerr1 = (err1points->last().y() + medianerr1)/2;
    }


    foreach (QPointF p, *adc1points) {
        double i;
        i = p.y();
        measres2 = mparams.submres*(mparams.cblockres*((mparams.supvolt/i)*mparams.shuntres-mparams.protres-mparams.shuntres)/(mparams.cblockres-(mparams.supvolt/i)*mparams.shuntres+mparams.protres+mparams.shuntres)-mparams.lineres)/(mparams.submres+mparams.lineres-mparams.cblockres*((mparams.supvolt/i)*mparams.shuntres-mparams.protres-mparams.shuntres)/(mparams.cblockres-(mparams.supvolt/i)*mparams.shuntres+mparams.protres+mparams.shuntres));
        err5points->append(QPointF(p.x(), abs(100-(measres2*100/resistance))));
        medianerr5 = (err5points->last().y() + medianerr5)/2;
    }



    if (medianerr1 > medianerr5)
    {
        errgauge = koeff * medianerr5 + (1 - koeff)*errgauge;
    }
    else
    {
        errgauge = koeff * medianerr1 + (1 - koeff)*errgauge;
    }


    errpoints->clear();


    foreach (QPointF i, medianerr1 > medianerr5 ? *err5points : *err1points) {
        int index;
        index = searchpoint_x(static_cast<int>(i.y()));
        if (index >= 0)
        {
            (*errpoints)[index].setY(errpoints->at(index).y() + 1);
        }
        else
        {
            errpoints->append(QPointF(static_cast<int>(i.y()), 1));
        }
    }


    std::sort(errpoints->begin(), errpoints->end(), variantLessThan);
    norm_points(errpoints);

    emit sendmedianerr(errgauge);
    emit senderrdistr(errpoints);
    emit sendvoltagedata(adc0points, adc1points, adc2points);
    emit senderrordata(err1points, err5points);
}

// Compare two variants.
bool variantLessThan(const QPointF &v1, const QPointF &v2)
{
    return v1.x() < v2.x();
}

