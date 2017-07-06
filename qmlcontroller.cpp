#include "qmlcontroller.h"
#include "comport.h"
#include "customplotitem.h"
#include <qobject.h>
#include "resistanceitem.h"
#include "plottermath.h"

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

    signalMapper = new QSignalMapper(this);


    QMutableListIterator<QObject*> i(*resList);

    while(i.hasNext())
    {
        QObject::connect(i.next(), SIGNAL(resistanceChanged(int)), pmath, SLOT(getResistance(int)));

    }



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

    connect (cp, SIGNAL(sendvoltagedata(int*)), pmath, SLOT(getVoltData(int*)));   //connect com port with math slot.

    QQuickWindow *window = qobject_cast<QQuickWindow *>(appengine->rootObjects().first());
    voltageplot = window->findChild<CustomPlotItem *>("voltagePlot");
    errorplot = window->findChild<CustomPlotItem *>("errorPlot");

    //Check if we have right object
    if (QString::compare(voltageplot->objectName(), "voltagePlot") == 0){
        qDebug() << "Found voltage plot";
        voltageplot->createPlots(3);
        connect(cp,SIGNAL(sendvoltagedata(int*)),pmath,SLOT(getVoltData(int*)));
        connect(pmath, SIGNAL(sendvoltagedata(QVector<double>,QVector<double>,QVector<double>,QVector<double>)),voltageplot,SLOT(plotVoltageData(QVector<double>,QVector<double>,QVector<double>,QVector<double>)));

    }
    else
        qDebug() << "Somehow err";

    //Check if we have right object
    if (QString::compare(errorplot->objectName(), "errorPlot") == 0){
        qDebug() << "Found error plot";
        //QObject::connect(cp,SIGNAL(senddata(int*)),plot,SLOT(updatedata(int*)));
        errorplot->createPlots(2);
        connect(pmath, SIGNAL(senderrordata(QVector<double>,QVector<double>,QVector<double>)),errorplot,SLOT(plotErrorData(QVector<double>,QVector<double>,QVector<double>)));
    }
    else
        qDebug() << "Somehow err";
}

void QmlController::toggleClicked()
{
    QQuickWindow *window = qobject_cast<QQuickWindow *>(appengine->rootObjects().first());
    QObject *btn = window->findChild<QObject *>("toggleBtn");
    if (QString::compare(btn->objectName(), "toggleBtn") == 0){
        qDebug()<< btn->property("checked").toBool();
        if (btn->property("checked").toBool() == true)
        {
            disconnect(cp,SIGNAL(sendvoltagedata(int*)),voltageplot,SLOT(updatedata(int*)));
        }
        else
        {
            QObject::connect(cp,SIGNAL(sendvoltagedata(int*)),voltageplot,SLOT(updatedata(int*)));
        }

    }

}

void QmlController::applyClicked()
{


}


