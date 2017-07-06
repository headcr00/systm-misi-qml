import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import CustomPlot 1.0
import QtQuick.Extras 1.4

Item{
    id: firstPage
    QPlot {
        id: item1
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 120
    }
    
    Column {
        id: column
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.right
        anchors.leftMargin: -120
        anchors.right: parent.right
        anchors.rightMargin: 0
        
        Label {
            id: label
            text: qsTr("Error, %")
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
        }
        
        Gauge {
            id: gauge
            height: 150
            value: 1
            minimumValue: 0
            maximumValue: 5
            tickmarkStepSize: 0.5
            anchors.top: label.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
        }
        
        
        
        ListView {
            id: listView
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.top: gauge.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: 5
            clip: true
            
            model: _resModel
            header: Text{
                text:qsTr("Resistance, Ohm")
                font: label.font
                
            }
            
            delegate: RadioDelegate {
                width: listView.width
                text: model.modelData.rname
                id: control
                checked: index == 0
                onClicked: model.modelData.clicked()
                
                contentItem: Text {
                    
                    text: control.text
                    font: label.font
                    opacity: enabled ? 1.0 : 0.3
                    color: control.checked ? "#ccffff" : "#0044cc"
                    
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                indicator: Rectangle{
                    visible: false
                }
                
                background:Rectangle{
                    implicitWidth: parent.width
                    implicitHeight: 10
                    
                    color:control.checked ? "#3f51b5" : "#f4f5fb"
                    
                }
                
                
            }
        }
    }
    
}
