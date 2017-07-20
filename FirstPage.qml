import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Extras 1.4
import QtCharts 2.0
Item{
    id: firstPage

    ChartView {

        id: voltagePlot
        objectName: "voltagePlot"
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 120
        Component.onCompleted: _contr.initVoltagePlot(voltagePlot)

        legend.alignment: Qt.AlignBottom
        title: "Voltage plot"
        //animationOptions: ChartView.AllAnimations





        ValueAxis{
            id: valueAxisX
            titleText: "Data frame"
            min:0
            max:1024


        }
        ValueAxis{
            titleText: "Voltage, V"
            id:valueAxisY

            tickCount: 8
            min: 0
            max: 3.5
        }

        LineSeries{
            useOpenGL: true
            id: adc0s
            axisX: valueAxisX
            axisY: valueAxisY
            name: "ADC0: 1x scale"


            onPointsReplaced: {

             voltagePlot.scrollRight(Math.round(adc0s.at(adc0s.count-1).x - valueAxisX.max)* (voltagePlot.plotArea.width/1024));

            }
        }


        LineSeries{
            useOpenGL: true
            id: adc1s
            axisX: valueAxisX
            axisY: valueAxisY
            name: "ADC1: 10x scale"
        }


        LineSeries{
            useOpenGL: true
            id: adc2s
            axisX: valueAxisX
            axisY: valueAxisY
            name: "ADC2: Reference voltage"
        }

    }


    Label {

        text: qsTr("Voltage graph")
        font.pointSize: 45

        anchors.verticalCenter: voltagePlot.verticalCenter


        anchors.horizontalCenter: voltagePlot.horizontalCenter
        anchors.horizontalCenterOffset: 30
        opacity: 0.1
    }


    
}
