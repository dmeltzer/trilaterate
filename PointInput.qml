import QtQuick 2.0
import QtQuick.Controls 1.4 as Controls
import QtQuick.Layouts 1.1

Rectangle {
    id: rectangle
    property string title
    property alias rectangle: rectangle
    width: 225
    height: 200

    function values() {
        return [xField.displayText, yField.displayText, zField.displayText, lineLength.displayText, axis.displayText];
    }

    Text {
        id: inputLabel
        x: 8
        y: 8
        text: title
        font.bold: true
        font.pixelSize: 18
    }


    ColumnLayout {
        id: columnLayout
        x: 8
        y: 36
        width: 210
        height: 130

        RowLayout {
            id: axisLayout
            Layout.preferredWidth: -1
            Layout.fillWidth: true

            Text {
                id: axisText
                text: qsTr("Axis:")
                Layout.minimumWidth: 75

                font.pixelSize: 12
            }

            Controls.TextField {
                id: axis
                placeholderText: qsTr("Axis")
            }
        }

        RowLayout {
            id: xLayout
            Layout.preferredWidth: -1
            Layout.fillWidth: true

            Text {
                id: xText
                text: qsTr("X:")
                Layout.minimumWidth: 75

                font.pixelSize: 12
            }

            Controls.TextField {
                id: xField
                placeholderText: qsTr("X")
            }
        }
        RowLayout {
            id: yLayout
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: yText
                text: qsTr("Y:")
                Layout.minimumWidth: 75
                font.pixelSize: 12
            }

            Controls.TextField {
                id: yField
                placeholderText: qsTr("Y")
            }
        }
        RowLayout {
            id: zLayout
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: zText
                text: qsTr("Z:")
                Layout.minimumWidth: 75
                font.pixelSize: 12
            }

            Controls.TextField {
                id: zField
                placeholderText: qsTr("Z")
            }
        }
        RowLayout {
            id: lineLengthLayout
            Layout.fillHeight: true
            Layout.fillWidth: true
            Text {
                id: lineLength_Text
                text: qsTr("Cable Length")
                font.pixelSize: 12
                Layout.minimumWidth: 75
            }

            Controls.TextField {
                id: lineLength
                readOnly: true
                placeholderText: qsTr("0")
            }
        }

        RowLayout {
            id: staticCable0Layout
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: cable0_text
                text: qsTr("Cable to 0")
                Layout.minimumWidth: 75
                font.pixelSize: 12
            }

            Controls.TextField {
                id: cable0
                placeholderText: qsTr("Line Length")
            }

        }
    }

}
