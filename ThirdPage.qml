import QtQuick 2.0
import QtCharts 2.0
Item {
    id: errc

    ChartView {
        id: errDisChart
                    objectName: "errDisChart"
        title: "Error distribution"
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 120
        legend.alignment: Qt.AlignBottom
        antialiasing: true
animationOptions: ChartView.AllAnimations

        ValueAxis{
            id: valueAxisX
            titleText: "Error, %"
            //base: 10
            min: 0
            max: 20
            minorTickCount: 5
        }
        ValueAxis{
            titleText: "Amplitude"
            id:valueAxisY
            minorTickCount: 5
            min: 0
            max: 1
        }

        LineSeries {
            id: seriesl
                visible: true
               name: "Error"
               axisX: valueAxisX
               axisY: valueAxisY
               useOpenGL: true

           }
        LineSeries{
            useOpenGL: true
            name: "5%"
            color: "red"
            XYPoint{
                x:5
                y:0
            }

            XYPoint{
                x:5
                y:1
            }
        }

        LineSeries{
            useOpenGL: true
            name: "2%"
            color: "red"
            style: Qt.DashLine
            XYPoint{
                x:2
                y:0
            }

            XYPoint{
                x:2
                y:1
            }
        }

    }


    Component.onCompleted: {
        _contr.initDistrPlot(errDisChart)

    }
}

