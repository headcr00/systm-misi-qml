import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import CustomPlot 1.0
import QtQuick.Extras 1.4

CustomPlotItem {
    
    id: errorPlot
    objectName: "errorPlot"
    anchors.topMargin: 0
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.rightMargin: 120
    Component.onCompleted: initCustomPlot()
    
    
}
