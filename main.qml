import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 6.0

ApplicationWindow {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Paint")

    RowLayout {
        anchors.fill: parent
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Viewport {
                width: Math.min(parent.width, implicitWidth)
                height: Math.min(parent.height, implicitHeight)
                anchors.centerIn: parent
            }
            clip: true
        }
        ColorChooser {}
    }
}
