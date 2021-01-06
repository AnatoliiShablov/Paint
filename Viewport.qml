import QtQuick 6.0
import QtQuick.Controls 6.0

TableView {
    implicitHeight: paintModel.cellSize * rows
    implicitWidth: paintModel.cellSize * columns

    model: paintModel
    delegate: Rectangle {
        implicitWidth: paintModel.cellSize
        implicitHeight: paintModel.cellSize

        width: paintModel.cellSize
        height: paintModel.cellSize

        color: cellColor

        border.width: 1
        border.color: "black"

        Rectangle {
            width: paintModel.cellSize / 2
            height: paintModel.cellSize / 3

            anchors.centerIn: parent

            color: "white"

            Text {
                anchors.fill: parent
                text: cellNumber
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            visible: !correct
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                cellColor = colorChooserModel.currentColor
            }
        }
    }
}
