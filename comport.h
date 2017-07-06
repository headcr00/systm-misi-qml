#ifndef COMPORT_H
#define COMPORT_H
#include <QSerialPort>

class ComPort : public QSerialPort
{
    Q_OBJECT
public:
   explicit ComPort();
public slots:
    void readOscData();

signals:
    void senddata(int * arr);
protected:
    void processData(QByteArray *data);
};

#endif // COMPORT_H
