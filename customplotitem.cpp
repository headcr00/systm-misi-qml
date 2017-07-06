#include "CustomPlotItem.h"
#include "qcustomplot.h"
#include <QDebug>
#include <QtCore>

CustomPlotItem::CustomPlotItem( QQuickItem* parent ) : QQuickPaintedItem( parent )
  , m_CustomPlot( nullptr ),
    datax(new QVector<double>),
   datay0(new QVector<double>),
   datay1(new QVector<double>),
   datay2(new QVector<double>)
{
    setFlag( QQuickItem::ItemHasContents, true );
    // setRenderTarget(QQuickPaintedItem::FramebufferObject);
    // setAcceptHoverEvents(true);
    setAcceptedMouseButtons( Qt::AllButtons );

    connect( this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &CustomPlotItem::updateCustomPlotSize );
}

CustomPlotItem::~CustomPlotItem()
{
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

void CustomPlotItem::initCustomPlot()
{
    m_CustomPlot = new QCustomPlot();

    updateCustomPlotSize();

    plotSetup();

    connect( m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot );
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePlot()));
    timer->start(50);
    m_CustomPlot->replot();
}


void CustomPlotItem::paint( QPainter* painter )
{
    if (m_CustomPlot)
    {
        QPixmap    picture( boundingRect().size().toSize() );
        QCPPainter qcpPainter( &picture );

        //m_CustomPlot->replot();
        m_CustomPlot->toPainter( &qcpPainter );

        painter->drawPixmap( QPoint(), picture );
    }
}

void CustomPlotItem::mousePressEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::mouseReleaseEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::mouseMoveEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::mouseDoubleClickEvent( QMouseEvent* event )
{
    routeMouseEvents( event );
}

void CustomPlotItem::graphClicked( QCPAbstractPlottable* plottable )
{
    //qDebug() << Q_FUNC_INFO << QString( "Clicked on graph '%1 " ).arg( plottable->name() );
}

void CustomPlotItem::routeMouseEvents( QMouseEvent* event )
{
    if (m_CustomPlot)
    {
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        //QCoreApplication::sendEvent( m_CustomPlot, newEvent );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }
}

void CustomPlotItem::routeWheelEvents( QWheelEvent* event )
{
    if (m_CustomPlot)
    {
        QWheelEvent* newEvent = new QWheelEvent( event->pos(), event->delta(), event->buttons(), event->modifiers(), event->orientation() );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }
}

void CustomPlotItem::wheelEvent( QWheelEvent *event )
{
    routeWheelEvents( event );
}

void CustomPlotItem::updateCustomPlotSize()
{
    if (m_CustomPlot)
    {
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
        m_CustomPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));
    }
}

void CustomPlotItem::onCustomReplot()
{
    update();
}


void CustomPlotItem::setYTitle(const QString &b)
{
    yTitle = b;
}

QString CustomPlotItem::getYTitle()
{
    return yTitle;
}

void CustomPlotItem::plotSetup()
{
    m_CustomPlot->setOpenGl(true);
    m_CustomPlot ->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
/*
    m_CustomPlot -> addGraph();
    m_CustomPlot -> addGraph();
    m_CustomPlot ->  addGraph();
    m_CustomPlot ->  graph(0)->setPen(QPen(Qt::red));
    m_CustomPlot ->  graph(1)->setPen(QPen(Qt::green));
    m_CustomPlot ->  graph(2)->setPen(QPen(Qt::blue));

    m_CustomPlot ->  graph(0)->setLineStyle(QCPGraph::lsStepCenter);
    m_CustomPlot -> graph(1)->setLineStyle(QCPGraph::lsStepCenter);
    m_CustomPlot -> graph(2)->setLineStyle(QCPGraph::lsStepCenter);
*/
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s:%z");

    m_CustomPlot -> xAxis->setTicker(timeTicker);

    QSharedPointer<QCPAxisTickerFixed> fixedTicker2(new QCPAxisTickerFixed);

    m_CustomPlot -> xAxis->setLabel("Time, s");
    m_CustomPlot->yAxis->setLabel(yTitle);

    m_CustomPlot -> xAxis->setRange(0, 1, Qt::AlignRight);
    m_CustomPlot -> yAxis->setRange(m_ymin, m_ymax);
    m_CustomPlot ->  replot();
}

/*void CustomPlotItem::updateVoltageData(int * arr)
{
    if (datax->size() != 0){
        datax->append(datax->last()+0.001);
    }
    else
        datax->append(0.001);

    datay0->append(*arr);
    datay1->append(*(arr+1));
    datay2->append(*(arr+2));
    m_CustomPlot ->graph(0)->setData(*datax,*datay0, true);
    m_CustomPlot ->graph(1)->setData(*datax,*datay1);
    m_CustomPlot ->graph(2)->setData(*datax,*datay2);
    m_CustomPlot->xAxis->setRangeUpper(datax->last());
    m_CustomPlot->xAxis->setRangeLower(datax->last()-1);
}

void CustomPlotItem::updateErrorData(int * arr)
{

}
*/
double CustomPlotItem::getymin() const
{
    return m_ymin;
}

void CustomPlotItem::setymin(double ymin)
{
    if (m_ymin == ymin)
        return;

    m_ymin = ymin;
    emit yminChanged(ymin);
}

double CustomPlotItem::getymax() const
{
    return m_ymax;
}

void CustomPlotItem::setymax(double ymax)
{
    if (m_ymax == ymax)
        return;

    m_ymax = ymax;
    emit ymaxChanged(ymax);
}

void CustomPlotItem::updatePlot()
{
        m_CustomPlot ->replot();
}

void CustomPlotItem::createPlots(int amount)
{
    /*Creates number amount of plots*/

    for (int i = 0; i < amount; i++)
    {
        m_CustomPlot->addGraph();
        m_CustomPlot->graph(i)->setLineStyle(QCPGraph::lsStepCenter);


    }
    m_CustomPlot->legend->setVisible(true);
}
void CustomPlotItem::plotVoltageData(QVector<double> x, QVector<double> v1, QVector<double> v2, QVector<double> v3)
{
    /* Plots qvector to specific arr */

    if (m_CustomPlot->graphCount() == 0)
    {
        qDebug() << "No greaphs created";
        return;
    }
    m_CustomPlot ->  graph(0)->setPen(QPen(Qt::red));
    m_CustomPlot ->  graph(1)->setPen(QPen(Qt::green));
    m_CustomPlot ->  graph(2)->setPen(QPen(Qt::blue));

    m_CustomPlot->graph(0)->setData(x,v1,true);

    m_CustomPlot->graph(1)->setData(x,v2,true);
    m_CustomPlot->graph(2)->setData(x,v3,true);
    m_CustomPlot->xAxis->setRangeUpper(x.last());
    m_CustomPlot->xAxis->setRangeLower(x.last()-1);

    m_CustomPlot->graph(0)->setName("1-scale factor");
    m_CustomPlot->graph(1)->setName("5-scale factor");
    m_CustomPlot->graph(2)->setName("Reference voltage");

}

void CustomPlotItem::plotErrorData(QVector<double> x, QVector<double> e1, QVector<double> e5)
{
    /* Plots qvector to specific arr */

    if (m_CustomPlot->graphCount() == 0)
    {
        qDebug() << "No greaphs created";
        return;
    }

    m_CustomPlot ->  graph(0)->setPen(QPen(Qt::red));
    m_CustomPlot ->  graph(1)->setPen(QPen(Qt::blue));
    m_CustomPlot->graph(0)->setData(x,e1,true);
    m_CustomPlot->graph(1)->setData(x,e5,true);
    m_CustomPlot->xAxis->setRangeUpper(x.last());
    m_CustomPlot->xAxis->setRangeLower(x.last()-1);


}
