#ifndef QMLCONTROLLER_H
#define QMLCONTROLLER_H

#include <QObject>

class QmlController : public QObject
{
    Q_OBJECT
public:
    explicit QmlController(QObject *parent = 0);

signals:

public slots:
};

#endif // QMLCONTROLLER_H