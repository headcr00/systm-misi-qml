import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import CustomPlot 1.0
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 768


    title: qsTr("Hello World")

    Drawer {
        id: drawer
        objectName: "drawer"
        width: 400
        height: window.height
        Settings {
            anchors.fill: parent
        }
    }

    SwipeView{
        id: view
        currentIndex: 0
        anchors.fill: parent
        ThirdPage{


        }
        FirstPage {
            id: firstPage
        }
        SecondPage {
            id: secondPage
        }


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
            value: _contr.errgauge
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
                color: Material.accent
                text:qsTr("Resistance, Ohm")
                font: label.font

            }

            delegate: RadioDelegate {

                width: listView.width
                text: model.modelData.rname
                id: control
                checked: index == 0
                onClicked: _contr.selectResistance(model.modelData.rres)
                contentItem: Text {

                    text: control.text
                    font: label.font
                    opacity: enabled ? 1.0 : 0.3
                    color: Material.accent //"#ccffff" : "#0044cc"

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                indicator: Rectangle{
                    visible: false
                }

                background:Rectangle{
                    implicitWidth: parent.width
                    implicitHeight: 10

                    color:control.checked ? Material.primary : Material.background//"#3f51b5" : "#f4f5fb"

                }


            }
        }
    }

    PageIndicator {
        id: indicator

        count: view.count
        currentIndex: view.currentIndex

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    header:ToolBar{

        RowLayout{
            anchors.fill:  parent
            ToolButton{
                id: openSettings
                onClicked: drawer.open()

                ColumnLayout{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 3
                    Repeater{

                        model:3
                        Rectangle{
                            width: 20; height: 5
                            radius: 2
                            color:"white"
                        }
                    }
                }
            }
            ToolButton{
                id: toggleBtn
                text: qsTr("Toggle")
                objectName: "toggleBtn"
                onCheckedChanged: _contr.toggleClicked(toggleBtn.checked)
                checkable: true

            }

            ToolButton
            {
                id: clrPlots
                text: qsTr("Clear plots")
                onClicked: _contr.clearPlotsClicked()
            }
        }



    }




}


