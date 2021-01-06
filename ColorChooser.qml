import QtQuick 6.0

ListView {
    readonly property int sqrSize: 20

    implicitWidth: colorChooserModel.cellSize + 40
    implicitHeight: colorChooserModel.cellSize * count + 40

    model: colorChooserModel
    delegate: Rectangle {
        implicitWidth: colorChooserModel.cellSize
        implicitHeight: colorChooserModel.cellSize

        width: colorChooserModel.cellSize
        height: colorChooserModel.cellSize

        color: cellColor

        Rectangle {
            anchors.centerIn: parent

            width: colorChooserModel.cellSize / 2
            height: colorChooserModel.cellSize / 3
            color: colorChooserModel.currentColor === index ? "lightgrey" : "white"

            Text {
                anchors.fill: parent
                text: cellNumber
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                colorChooserModel.currentColor = index
            }
        }
    }
}
