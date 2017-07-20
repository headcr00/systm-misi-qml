#include "qmlcontroller.h"
#include "comport.h"
#include "customplotitem.h"
#include <QVariant>
#include <QVariantMap>
#include <QtCharts>
#include <qobject.h>
#include "resistanceitem.h"
#include "plottermath.h"
#include "misiparams_typedef.h"

using namespace QtCharts;
MisiParams misiparams;

QmlController::QmlController(QQmlApplicationEngine * engine, QObject *parent) : QObject(parent)
  , appengine(engine), resList(new QList<QObject*>)
{
    cp = new ComPort();
    pmath = new Plottermath();

    appengine->rootContext()->setContextProperty("_contr", this);
    qmlRegisterType<CustomPlotItem>("CustomPlot", 1, 0, "CustomPlotItem");

    resList->append(new ResistanceItem("10k", 10000));
    resList->append(new ResistanceItem("20k", 20000));
    resList->append(new ResistanceItem("30k", 30000));
    resList->append(new ResistanceItem("40k", 40000));
    resList->append(new ResistanceItem("50k", 50000));
    resList->append(new ResistanceItem("60k", 60000));
    resList->append(new ResistanceItem("70k", 70000));
    resList->append(new ResistanceItem("80k", 80000));
    resList->append(new ResistanceItem("90k", 90000));
    resList->append(new ResistanceItem("100k", 100000));
    resList->append(new ResistanceItem("200k", 200000));
    resList->append(new ResistanceItem("300k", 300000));
    resList->append(new ResistanceItem("400k", 400000));
    resList->append(new ResistanceItem("500k", 500000));
    resList->append(new ResistanceItem("600k", 600000));
    resList->append(new ResistanceItem("700k", 700000));
    resList->append(new ResistanceItem("800k", 800000));
    resList->append(new ResistanceItem("900k", 900000));
    resList->append(new ResistanceItem("1M", 1000000));
    resList->append(new ResistanceItem("2M", 2000000));
    resList->append(new ResistanceItem("3M", 3000000));
    resList->append(new ResistanceItem("4M", 4000000));
    resList->append(new ResistanceItem("5M", 5000000));
    resList->append(new ResistanceItem("6M", 6000000));
    resList->append(new ResistanceItem("7M", 7000000));
    resList->append(new ResistanceItem("8M", 8000000));
    resList->append(new ResistanceItem("9M", 9000000));
    resList->append(new ResistanceItem("10M", 10000000));
    appengine->rootContext()->setContextProperty("_resModel", QVariant::fromValue(*resList));
    QObject::connect(cp, SIGNAL(readyRead()), cp, SLOT(readOscData()));

}

void QmlController::connectedClicked()
{

    if (cp->connectbyPID() == 0)
        m_portStatus = true;
    else
        m_portStatus = false;
    emit portStatusChanged();
}

void QmlController::setObjects()
{

    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), pmath, SLOT(processSerialData()));
    timer->start(100);

    connect (cp, SIGNAL(sendvoltagedata(int*)), pmath, SLOT(getSerialData(int*)));   //connect com port with math slot.
    connect(pmath, SIGNAL(sendmedianerr(double)), this, SLOT(get_errgauge(double))); //Connect math to error gauge
    connect(pmath, SIGNAL(senderrdistr(QList<QPointF>*)), this, SLOT(getDistrPlotData(QList<QPointF>*)));//Connect math to third graph
    connect(pmath, SIGNAL(senderrordata(QList<QPointF>*,QList<QPointF>*)), this, SLOT(getErrorPlotData(QList<QPointF>*,QList<QPointF>*)));//Connect math to sec graph
    connect(pmath, SIGNAL(sendvoltagedata(QList<QPointF>*,QList<QPointF>*,QList<QPointF>*)), this, SLOT(getVoltagePlotData(QList<QPointF>*,QList<QPointF>*,QList<QPointF>*)));//Connect math to sec graph


/*

    //Check if we have right object
    if (QString::compare(voltageplot->objectName(), "voltagePlot") == 0){
        qDebug() << "Found voltage plot";
        voltageplot->createPlots(3);
        connect (cp, SIGNAL(sendvoltagedata(int*)), pmath, SLOT(getSerialData(int*)));
        connect(pmath, SIGNAL(sendvoltagedata(QVector<double>,QVector<double>,QVector<double>,QVector<double>)),voltageplot,SLOT(plotVoltageData(QVector<double>,QVector<double>,QVector<double>,QVector<double>)));

    }
    else
        qDebug() << "Somehow err";

    //Check if we have right object
    if (QString::compare(errorplot->objectName(), "errorPlot") == 0){
        qDebug() << "Found error plot";
        errorplot->createPlots(2);
        connect(pmath, SIGNAL(senderrordata(QVector<double>,QVector<double>,QVector<double>)),errorplot,SLOT(plotErrorData(QVector<double>,QVector<double>,QVector<double>)));
    }
    else
        qDebug() << "Somehow err";*/


}
/*!
 * \brief QmlController::initVoltagePlot
 * Initializes ADCx series for voltage plot. Called from FirstPage.qml
 * \param plobj chartview object
 */
void QmlController::initVoltagePlot(QVariant plobj)
{
    QAbstractSeries* series;
    QObject * obj = qvariant_cast<QObject*>(plobj);
    QMetaObject::invokeMethod(obj, "series", Qt::AutoConnection, Q_RETURN_ARG(QAbstractSeries*, series), Q_ARG(int, 0));
    adc0series = qobject_cast<QLineSeries*> (series);
    QMetaObject::invokeMethod(obj, "series", Qt::AutoConnection, Q_RETURN_ARG(QAbstractSeries*, series), Q_ARG(int, 1));
    adc1series = qobject_cast<QLineSeries*> (series);
    QMetaObject::invokeMethod(obj, "series", Qt::AutoConnection, Q_RETURN_ARG(QAbstractSeries*, series), Q_ARG(int, 2));
    adc2series = qobject_cast<QLineSeries*> (series);


}
/*!
 * \brief QmlController::initErrorPlot
 * Initializes ERRx series for error plot. Called from SeconPage.qml
 * \param plobj chartview object
 */
void QmlController::initErrorPlot(QVariant plobj)
{
    QAbstractSeries* series;
    QObject * obj = qvariant_cast<QObject*>(plobj);
    QMetaObject::invokeMethod(obj, "series", Qt::AutoConnection, Q_RETURN_ARG(QAbstractSeries*, series), Q_ARG(int, 0));
    err1series = qobject_cast<QLineSeries*> (series);
    QMetaObject::invokeMethod(obj, "series", Qt::AutoConnection, Q_RETURN_ARG(QAbstractSeries*, series), Q_ARG(int, 1));
    err5series = qobject_cast<QLineSeries*> (series);
}



void QmlController::toggleClicked(bool status)
{
  /*  qDebug() << status;

        if (status == true)
        {
            disconnect(cp,SIGNAL(sendvoltagedata(int*)),pmath,SLOT(getVoltData(int*)));
        }
        else
        {
            connect(cp,SIGNAL(sendvoltagedata(int*)),pmath,SLOT(getVoltData(int*)));
        }*/

}

void QmlController::applyClicked(QVariantMap a)
{
    misiparams.refvolt = a.value("refvolt").toDouble();
    misiparams.supvolt = a.value("supvolt").toDouble();
    misiparams.shuntres = a.value("shuntres").toDouble()*1000;
    misiparams.protres = a.value("protres").toDouble()*1000;
    misiparams.lineres = a.value("lineres").toDouble()*1000;
    misiparams.submres = a.value("submres").toDouble()*1000;
    misiparams.cblockres = a.value("cblockres").toDouble()*1000;
    misiparams.mcuVolt = a.value("mcuVolt").toDouble();
    misiparams.useMcuVolt = a.value("useMcuVolt").toBool();
    pmath->getRefData(misiparams);
}


void QmlController::selectResistance(QVariant res)
{
    pmath->pm_cleardata();
    pmath->getResistance(res.toInt());
}


void QmlController::initDistrPlot(QVariant plobj)
{

    QAbstractSeries* series;
    QObject * obj = qvariant_cast<QObject*>(plobj);
    QMetaObject::invokeMethod(obj, "series", Qt::AutoConnection, Q_RETURN_ARG(QAbstractSeries*, series), Q_ARG(int, 0));    
    errdistplot = qobject_cast<QLineSeries*> (series);
}
/*!
 * \brief QmlController::getVoltagePlotData
 * Updates voltage data. This slot is connected to pmath
 * \param pt0   adc0 series
 * \param pt1   adc1 series
 * \param pt2   vref series
 */
void QmlController::getVoltagePlotData(QList<QPointF> *pt0, QList<QPointF> *pt1, QList<QPointF> *pt2)
{
    adc0series->replace(*pt0);
    adc1series->replace(*pt1);
    adc2series->replace(*pt2);

}
/*!
 * \brief QmlController::getErrorPlotData
 * Updates error data. This slot is connected to pmath
 * \param pt0   err1 series
 * \param pt1   err5 series
 */
void QmlController::getErrorPlotData(QList<QPointF> *pt0, QList<QPointF> *pt1)
{
    err1series->replace(*pt0);
    err5series->replace(*pt1);


}
/*!
 * \brief QmlController::get_errgauge
 * Updates value in error gauge in main.qml. Connected to pmath
 * \param err
 */
void QmlController::get_errgauge(double err)
{
    qDebug()<<err;
    m_errgauge = err;
    emit errgaugeChanged();
}

/*!
 * \brief QmlController::getDistrPlotData
 * Updates error distribution series in firstpage.qml. Connected to pmath.
 * \param pt0
 */
void QmlController::getDistrPlotData(QList<QPointF> *pt0)
{
    errdistplot->replace(*pt0);


}

void QmlController::clearPlotsClicked()
{
pmath->pm_cleardata();
}

