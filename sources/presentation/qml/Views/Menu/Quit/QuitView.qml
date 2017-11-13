import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Item {
    id: root

    implicitWidth: frame.width
    implicitHeight: frame.height

    Controls.Frame {
        id: frame
        width: parent.width

        ColumnLayout {
            anchors.fill: parent

            Controls.Label {
                text: qsTr("Realy quit?")
            }

            Controls.Button {
                text: qsTr("Yes")
                iconSource: "qrc:/icons/quit.svg"
                iconColor: palette.dangerColor
                onClicked: Qt.quit()
                Layout.fillWidth: true
            }

            Controls.Button {
                text: qsTr("No")
                iconSource: "qrc:/icons/remove.svg"
                onClicked: backOut()
                Layout.fillWidth: true
            }
        }
    }
}
