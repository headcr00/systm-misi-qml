#ifndef QMLCONTROLLER_H
#define QMLCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "comport.h"
#include "customplotitem.h"
#include "resistanceitem.h"
#include "plottermath.h"
#include "QtCharts/QLineSeries"

using namespace QtCharts;

class QmlController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool portStatus MEMBER m_portStatus NOTIFY portStatusChanged)
    Q_PROPERTY(double errgauge MEMBER m_errgauge NOTIFY errgaugeChanged)


public:
    explicit QmlController(QQmlApplicationEngine *engine, QObject *parent = 0 );

    void setObjects();



signals:
    void portStatusChanged();
    void errgaugeChanged();



public slots:

    //GUI manipulation

    void clearPlotsClicked();
    void toggleClicked(bool status);
    void connectedClicked();
    void selectResistance(QVariant res);
    void applyClicked(QVariantMap a);
    void get_errgauge(double err);
    //Plot manipulation
    void initVoltagePlot(QVariant plobj);
    void initErrorPlot(QVariant plobj);
    void initDistrPlot (QVariant plobj);

    void getVoltagePlotData(QList<QPointF>* pt0, QList<QPointF>* pt1, QList<QPointF>* pt2);
    void getErrorPlotData(QList<QPointF>* pt0, QList<QPointF>* pt1);
    void getDistrPlotData(QList<QPointF>* pt0);





private:
    QQmlApplicationEngine * appengine;
    ComPort * cp;
    CustomPlotItem * voltageplot;
    CustomPlotItem * errorplot;
    //Graph series
    QLineSeries * errdistplot;
    QLineSeries * adc0series;
    QLineSeries * adc1series;
    QLineSeries * adc2series;
    QLineSeries * err1series;
    QLineSeries * err5series;

    bool m_portStatus = false;
    double m_errgauge;
    QList<QObject*> * resList;
    Plottermath * pmath;


};

#endif // QMLCONTROLLER_H
