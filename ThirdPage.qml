import QtQuick 2.0
import QtCharts 2.0
Item {


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

        ValueAxis{
            id: valueAxisX
            //base: 10
            min: 0
            max: 15
            minorTickCount: 15
        }
        ValueAxis{
            id:valueAxisY
            min: 0
            max: 700
        }

        LineSeries {
            id: seriesl
                visible: true
               name: "LineSeries"
               axisX: valueAxisX
               axisY: valueAxisY
           }
        LineSeries{
            color: "red"
            XYPoint{
                x:5
                y:0
            }

            XYPoint{
                x:5
                y:700
            }
        }

        LineSeries{
            color: "red"
            style: Qt.DashLine
            XYPoint{
                x:2
                y:0
            }

            XYPoint{
                x:2
                y:700
            }
        }

    }


    Component.onCompleted: {
        _contr.updateSeries(errDisChart)

    }
}

