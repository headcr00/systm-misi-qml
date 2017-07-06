import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Extras 1.4
Item {
    id: item1



    GridLayout {
        id: gridLayout
        x: 270
        width: 296
        columns: 2
        rows: 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20

        Button {
            id: b_Connect
            text: qsTr("      Connect")

            Layout.fillWidth: true
            transformOrigin: Item.Center
            onClicked: _contr.connectedClicked()

            StatusIndicator
            {
                anchors.verticalCenter:  parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 5
                active: _contr.portStatus
                color: "green"
            }
        }

        Button {
            id: b_Apply
            text: qsTr("Apply")
            Layout.fillWidth: true
            transformOrigin: Item.Center
            onClicked: _contr.applyClicked()
        }

        Label{
            id: resText
            text: "ADC Reference: "
        }

        TextField {
            id: adcRefText
            objectName: "adcRefText"
            validator: IntValidator{}
            text: "2"
            maximumLength: 8
            width: 30
        }

        Label{
            text: "Reference voltage, mV: "
        }

        TextField {
            id: refVoltText
            objectName: "refVoltText"
            anchors.left: adcRefText.left

            validator: IntValidator{}
            maximumLength: 8
            width: 30
            text: _contr.refvoltage
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        }

        Label{
            text: qsTr("Supply voltage, V:")
        }

        TextField{
            id: supplyText
            objectName: "supplyText"
            text: "60"
        }

        Label{
            text: qsTr("Shunt resistance, kOhm:")
        }

        TextField{
            id: shuntResText
            objectName: "shuntResText"
            text: "1"
        }

        Label{
            text: qsTr("Protection resistance, kOhm:")
        }

        TextField{
            id: protResText
            objectName: "protResText"
            text: "100"
        }


    }
}
