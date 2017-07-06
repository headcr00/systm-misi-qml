#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "CustomPlotItem.h"
#include <QtWidgets/QApplication>
#include <QtCore>
#include "comport.h"
#include "qmlcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);



    QQmlApplicationEngine engine;
    QmlController * qcont = new QmlController(&engine);


    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    qcont->setObjects();
    return app.exec();
}
