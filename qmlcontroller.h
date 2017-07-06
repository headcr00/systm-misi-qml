#ifndef QMLCONTROLLER_H
#define QMLCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "comport.h"
#include "customplotitem.h"
#include "resistanceitem.h"
#include "plottermath.h"

class QmlController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool portStatus MEMBER m_portStatus NOTIFY portStatusChanged)


public:
    explicit QmlController(QQmlApplicationEngine *engine, QObject *parent = 0 );

    void setObjects();


signals:
    void portStatusChanged();



public slots:
    void toggleClicked();
    void connectedClicked();

    void applyClicked();
    //void setRefvoltage(int refvoltage);


private:
    QQmlApplicationEngine * appengine;
    ComPort * cp;
    CustomPlotItem * voltageplot;
    CustomPlotItem * errorplot;
    bool m_portStatus = false;
    QList<QObject*> * resList;
    Plottermath * pmath;
    QSignalMapper * signalMapper;

};

#endif // QMLCONTROLLER_H
