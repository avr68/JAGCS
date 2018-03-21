import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

import "../DashboardControls" as DashboardControls

Controls.Pane {
    id: root

    property bool dmsFormat: settings.boolValue("Gui/coordinatesDms")

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: sizings.spacing

        Controls.ColoredIcon {
            id: snsIcon
            color: {
                switch (vehicle.satellite.fix) {
                case -1:
                case 0: return palette.sunkenColor;
                case 1: return palette.dangerColor;
                case 2: return palette.cautionColor;
                case 3:
                default: return palette.positiveColor;
                }
            }
            source: "qrc:/icons/gps.svg"
            height: sizings.controlBaseSize
            width: height
            Layout.alignment: Qt.AlignRight

            Text {
                text: vehicle.satellite.satellitesVisible
                font.pixelSize: parent.height / 4
                font.bold: true
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                color: parent.color
            }
        }

        ColumnLayout {
            id: column
            Layout.fillWidth: true
            spacing: sizings.spacing

            DashboardControls.Label {
                color: snsIcon.color
                text: qsTr("Lat.: ") + (dmsFormat ?
                           Helper.degreesToDmsString(vehicle.satellite.coordinate.latitude, false, 2) :
                           Helper.degreesToString(vehicle.satellite.coordinate.latitude, 6))
            }

            DashboardControls.Label {
                color: snsIcon.color
                text: qsTr("Lon.: ") + (dmsFormat ?
                           Helper.degreesToDmsString(vehicle.satellite.coordinate.longitude, true, 2) :
                           Helper.degreesToString(vehicle.satellite.coordinate.longitude, 6))
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Indicators.BatteryIndicator {
            id: battery
            percentage: vehicle.battery.percentage
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignRight

            DashboardControls.Label {
                color: vehicle.battery.voltage > 0.01 ? palette.textColor : palette.sunkenColor
                text: vehicle.battery.voltage.toFixed(2) + qsTr(" V")
            }

            DashboardControls.Label {
                color: {
                    if (vehicle.battery.current < -0.01) return palette.positiveColor;
                    if (vehicle.battery.current > 0.0) return palette.textColor;
                    if (vehicle.battery.current > 5.0) return palette.cautionColor;
                    if (vehicle.battery.current > 10.0) return palette.dangerColor;

                    return palette.sunkenColor;
                }
                text: vehicle.battery.current.toFixed(2) + qsTr(" A")
            }
        }
    }
}