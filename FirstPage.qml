import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import CustomPlot 1.0
import QtQuick.Extras 1.4
import CustomPlot 1.0
Item{
    id: firstPage



    CustomPlotItem {

        id: voltagePLot
        objectName: "voltagePlot"
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 120
        yTitle : "Voltage, mV"
        ymin: 0
        ymax: 3.5
        Component.onCompleted: initCustomPlot()



    }
    Label {

        text: qsTr("Voltage graph")
        font.pointSize: 45

        anchors.verticalCenter: voltagePLot.verticalCenter


        anchors.horizontalCenter: voltagePLot.horizontalCenter
        anchors.horizontalCenterOffset: 30
        opacity: 0.1
    }


    
}
