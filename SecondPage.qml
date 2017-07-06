import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import CustomPlot 1.0
import QtQuick.Extras 1.4
Item{
    id: secondPage

    CustomPlotItem {

        id: errorPlot
        objectName: "errorPlot"
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 120
        yTitle : "Error, %"
        ymin:0
        ymax:5
        Component.onCompleted: initCustomPlot()




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
