#include "comport.h"
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
ComPort::ComPort()
{

}

int ComPort::connectbyPID()
{
    QSerialPortInfo portInfo;
    QList<QSerialPortInfo> portList;
    portList = portInfo.availablePorts();
    if (this->isOpen() == true)
    {
        this->close();
        return 1;
    }
    foreach (QSerialPortInfo port, portList) {
        if (port.hasVendorIdentifier())
        {
            this->setPortName(port.portName());
            this->open(QIODevice::ReadOnly);
            this->setBaudRate(this->Baud115200);
            this->setStopBits(this->OneStop);
            this->setFlowControl(this->NoFlowControl);
            this->setParity(this->NoParity);
            this->setDataBits(this->Data8);
            this->setReadBufferSize(0);
            this->flush();

            qDebug() << this->portName();
            return 0;
        }
    }
    if (this->portName() == NULL){
        qDebug() << "No ports found";
        return 1;
    }
    return 1;
}

void ComPort::readOscData()
{

    QByteArray data;

    //Warning! This function should be threaded.
    if(this->isOpen() == false)
    {
        return;
        qDebug()<< "Open port!";
    }

    while (this->canReadLine())
    {
        data = this->readLine();

        this->processData(&data);

    }


}

void ComPort::processData(QByteArray * data)
{
    QRegExp rx("(\\d+)");
    QStringList list;
    int pos = 0;
    int cnt = 0;
    int retv[3];
    while ((pos = rx.indexIn(*data, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
        cnt++;
    }
    if (cnt++ == 3)
    {
        for (int i = 0; i < list.size(); i++){
            retv[i] = list.at(i).toInt();

        }
        emit sendvoltagedata(retv);
    }

}


