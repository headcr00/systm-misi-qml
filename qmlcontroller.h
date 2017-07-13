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
    void toggleClicked(bool status);
    void connectedClicked();
    void selectResistance(QVariant res);
    void applyClicked(QVariantMap a);
    void updateSeries (QVariant a);
    void get_errgauge(double err);
    void get_errdistr(QList<QPointF>* pt);
    void clearPlotsClicked();
    //void setRefvoltage(int refvoltage);


private:
    QQmlApplicationEngine * appengine;
    ComPort * cp;
    CustomPlotItem * voltageplot;
    CustomPlotItem * errorplot;
    QLineSeries * errdistplot;
    bool m_portStatus = false;
    double m_errgauge;
    QList<QObject*> * resList;
    Plottermath * pmath;


};

#endif // QMLCONTROLLER_H
