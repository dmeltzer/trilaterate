import QtQuick 2.0
import QtQuick.Controls 1.4 as Controls
import QtQuick.Layouts 1.1

Rectangle {
    property string title

    function values() {
        return [xField.displayText, yField.displayText, zField.displayText, lineLength.displayText];
    }

    ColumnLayout {
        id: sourceLayout
        x: 8
        y: 8
        transformOrigin: Item.Center
        spacing: 1

        Text {
            id: inputLabel
            text: title
            font.bold: true
            font.pixelSize: 18
        }

        RowLayout {
            Layout.preferredWidth: -1
            Layout.fillWidth: true

            Text {
                id: xText
                text: qsTr("X:")
                font.pixelSize: 12
            }

            Controls.TextField {
                id: xField
                placeholderText: qsTr("X")
            }
        }

        RowLayout {

            Text {
                id: yText
                text: qsTr("Y:")
                font.pixelSize: 12
            }

            Controls.TextField {
                id: yField
                placeholderText: qsTr("Y")
            }
        }

        RowLayout {

            Text {
                id: zText
                text: qsTr("Z:")
                font.pixelSize: 12
            }

            Controls.TextField {
                id: zField
                placeholderText: qsTr("Z")
            }
        }

        RowLayout {

            Text {
                id: lineLength_text
                text: qsTr("L:")
                font.pixelSize: 12
            }

            Controls.TextField {
                id: lineLength
                placeholderText: qsTr("Line Length")
            }
        }

    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
