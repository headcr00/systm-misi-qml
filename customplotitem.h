#ifndef CUSTOMPLOTITEM_H
#define CUSTOMPLOTITEM_H
#pragma once
#include "qcustomplot.h"
#include <QtQuick>
class QCustomPlot;

class CustomPlotItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString yTitle READ getYTitle WRITE setYTitle NOTIFY yTitleChanged)
    Q_PROPERTY(double ymin READ getymin WRITE setymin NOTIFY yminChanged)
    Q_PROPERTY(double ymax READ getymax WRITE setymax NOTIFY ymaxChanged)

public:
    CustomPlotItem( QQuickItem* parent = 0 );
    virtual ~CustomPlotItem();

    void paint( QPainter* painter );

    Q_INVOKABLE void initCustomPlot();


    void setYTitle(const QString &b);
    QString getYTitle();
    double getymin() const;
    double getymax() const;
    void createPlots(int amount);
    void plotArr(QVector<double> arr, int graphno);

public slots:
    //void updatedata(int *arr);

    void setymin(double ymin);
    void setymax(double ymax);
    void plotVoltageData(QVector<double> x, QVector<double> v1, QVector<double> v2, QVector<double> v3);
    void plotErrorData(QVector<double> x, QVector<double> e1, QVector<double> e5);

protected:
    void routeMouseEvents( QMouseEvent* event );
    void routeWheelEvents(QWheelEvent *event);
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void wheelEvent(QWheelEvent *event);


signals:
    void yTitleChanged();

    void yminChanged(double ymin);
    void ymaxChanged(double ymax);

private:
    Q_INVOKABLE QCustomPlot* m_CustomPlot;
    QString yTitle = "Title";
    void plotSetup();
    QVector <double> *datax;
    QVector <double> *datay0;
    QVector <double> *datay1;
    QVector <double> *datay2;
    bool toggleDatabool = false;
    double m_ymin = 0;
    double m_ymax = 5;
    double lastx = 0;

private slots:
    void graphClicked( QCPAbstractPlottable* plottable );
    void onCustomReplot();
    void updateCustomPlotSize();
    void updatePlot();


};

#endif // CUSTOMPLOTITEM_H
