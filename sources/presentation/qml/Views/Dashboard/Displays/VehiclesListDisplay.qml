import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: listDisplay

    property var vehicles

    implicitHeight: list.contentHeight + sizings.shadowSize

    VehiclesListDisplayPresenter {
        id: presenter
        view: listDisplay
    }

    ListView {
        id: list
        width: listDisplay.width - sizings.shadowSize
        height: parent.height
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        model: vehicles

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            width: parent.width - sizings.shadowSize
            Component.onCompleted: {
                switch (vehicleType) {
                case Vehicle.FixedWing:
                case Vehicle.FlyingWing:
                default:
                    // TODO: Special short displays for special types
                    return setSource("ShortAerialVehicleDisplay.qml", { "vehicleId": vehicleId });
                }
            }
        }
    }
}