import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Extras 1.4
import QtCharts 2.0


Item{
    id: secondPage
    ChartView {

        id: errorPlot
        objectName: "errorPlot"
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 120
        Component.onCompleted: _contr.initErrorPlot(errorPlot)
        legend.alignment: Qt.AlignBottom
        //animationOptions: ChartView.AllAnimations
        title: "Error plot"
        ValueAxis{
            id: valueAxisX
            titleText: "Data frame"
            min:0
            max:1024


        }
        ValueAxis{
            titleText: "Error, %"
            id:valueAxisY

            tickCount: 5
            minorTickCount: 4
            min: 0
            max: 20
        }

        LineSeries{
            useOpenGL: true
            id: err0s
            axisX: valueAxisX
            axisY: valueAxisY
            name: "ERR1: 1x scale"
            onPointsReplaced: {
            errorPlot.scrollRight(Math.round(err0s.at(err0s.count-1).x - valueAxisX.max) * (errorPlot.plotArea.width/1024));

            }
        }


        LineSeries{
            useOpenGL: true
            id: err1s
            axisX: valueAxisX
            axisY: valueAxisY
            name: "ERR5: 10x scale"
        }
    }


    Label {
        text: qsTr("Error graph")
        font.pointSize: 45
        anchors.verticalCenter: errorPlot.verticalCenter
        anchors.horizontalCenter: errorPlot.horizontalCenter
        anchors.horizontalCenterOffset: 30
        opacity: 0.1
    }


}
