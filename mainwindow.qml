import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4 as Controls
import QtQuick.Window 2.2
import QtQuick.Templates 2.0

Controls.ApplicationWindow {
    id: window
    width: 600
    height: 400
    title: "Test App"
    visible: true
    minimumWidth:  250
    minimumHeight: 250
    maximumWidth:  40000
    maximumHeight: 40000

    signal calculate(variant source, variant target)

    MessageDialog {
        id: aboutDialog
        icon: StandardIcon.Information
        title: "About"
        text: "Qt Quick Controls Gallery"
        informativeText: "This example demonstrates most of the available Qt Quick Controls."
    }

    menuBar : Controls.MenuBar {
        Controls.Menu {
            title: "&File"
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit()
            }
        }
        Controls.Menu {
            title: "&Help"
            MenuItem {
                text: qsTr("H&elp")
                onTriggered: aboutDialog.open()
            }
        }
    }

    ColumnLayout {
        width: 600
        height: 400
        spacing: 1
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Layout.preferredWidth: 600
            PointInput {
                id: point1
                objectName: "firstPoint"
                title: "First Point"
                width: 200
                height: 100
            }

            PointInput {
                id: point2
                objectName: "secondPoint"
                title: "Second Point"
                width: 200
                height: 100
            }

            PointInput {
                id: point3
                objectName: "thirdPoint"
                title: "Third Point"
                width: 200
                height: 100
            }

//            PointInput {
//                id: point4
//                objectName: "targetInput"
//                title: "Target"
//                width: 200
//                height: 100
//            }
        }

        Controls.Button {
            id: calculate
            text: qsTr("Calculate")
            checkable: false
            onClicked: _demo.output(sourceinput.values(), targetinput.values());
        }

        ColumnLayout {
            id: bigOutputLayout
            Layout.fillHeight: false
            Layout.fillWidth: true
            width: parent.width
            spacing: 0
            Layout.preferredHeight: parent.height / 2
            Layout.preferredWidth: parent.width


            Text {
                id: output_text
                text: qsTr("Result")
                Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
                Layout.fillWidth: true
                Layout.fillHeight: false
                verticalAlignment: Text.AlignBottom
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 18
            }
            RowLayout {
                id: outputLayout
                width: parent.width
                height: parent.height
                Layout.fillWidth: true
                Layout.rowSpan: 1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 10
                Layout.fillHeight: true
            }

            RowLayout {
                Controls.CheckBox {
                    id: enableOSC
                    pressed: _demo.oscEnabled
                    text: qsTr("Enable OSC Output")
                    onClicked: _demo.oscEnabled = enableOSC.checked
                }
            }

            RowLayout {
                Text {
                    id: ipAddress_Label
                    text: qsTr("Console IP:")
                    font.pixelSize: 12
                }

                Controls.TextField {
                    id: ipAddress
                    text: _demo.ipAddress
                    Layout.columnSpan: 1
                    Layout.preferredWidth: -1
                    readOnly: false
                    onEditingFinished: _demo.setIpAddress(ipAddress.text);
                    font.pixelSize: 12
                }
            }

        }
    }

    Connections {
        target: calculate
        onClicked: print("clicked")
    }


}
