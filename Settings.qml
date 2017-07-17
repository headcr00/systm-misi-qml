import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Extras 1.4
Item {
    id: settingsPage

    Component.onCompleted: sendFormData()
    function sendFormData()
    {
        var rval = {
            refvolt : refVoltText.text,
            supvolt : supplyText.text,
            shuntres : shuntResText.text,
            protres: protResText.text,
            lineres: lineResText.text,
            submres: smResText.text,
            cblockres: cblockResText.text,
            mcuVolt: mcuVoltage.text,
            useMcuVolt: chbox_vref.checked


        }
        console.log(chbox_vref.checked)
        _contr.applyClicked(rval)
    }

    GridLayout {
        id: gridLayout
        x: 270
        width: 296
        columns: 2
        rows: 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20





        Label{
            text: "Reference voltage, mV: "
        }

        TextField {
            id: refVoltText
            objectName: "refVoltText"


            validator: DoubleValidator{}
            maximumLength: 8
            width: 30
            text:"1228"
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        }

        Label{
            text: qsTr("Supply voltage, V:")
        }

        TextField{
            id: supplyText
            objectName: "supplyText"
            validator: DoubleValidator{}
            text: "254"
        }

        Label{
            text: qsTr("Shunt resistance, kOhm:")
        }

        TextField{
            id: shuntResText
            objectName: "shuntResText"
            validator: DoubleValidator{}
            text: "1"
        }

        Label{
            text: qsTr("Protection resistance, kOhm:")
        }

        TextField{
            id: protResText
            objectName: "protResText"
            validator: DoubleValidator{}
            text: "124"
        }

        Label{
            text: qsTr("Line resistance, kOhm:")
        }

        TextField{
            id: lineResText
            objectName: "lineResText"
            validator: DoubleValidator{}
            text: "0.5"
        }

        Label{
            text: qsTr("Sub block resistance, kOhm:")
        }

        TextField{
            id: smResText
            validator: DoubleValidator{}
            text: "9000"
        }


        Label{
            text: qsTr("Ctrl block resistance, kOhm:")
        }

        TextField{
            id: cblockResText
            validator: DoubleValidator{}
            text: "7399"
        }
        CheckBox
        {
            id: chbox_vref
            text: qsTr("Use supply as ref, mV:")
            onClicked: sendFormData()
        }
        TextField{
            id: mcuVoltage
            validator: DoubleValidator{}
            enabled: chbox_vref.checked ? true : false

            text: "3312"
        }
        Button {
            id: b_Apply
            text: qsTr("Apply")
            Layout.fillWidth: true
            transformOrigin: Item.Center
            onClicked: sendFormData()//_contr.applyClicked()
        }





    }
}
