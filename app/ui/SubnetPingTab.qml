import QtQuick 2.0

import Ubuntu.Components 1.1
import Ubuntu.Components.Popups 1.0

import NetworkScanner 1.0

import "../components"


Tab {
    id: subnet
    title: i18n.tr("Ping Subnet")

    page: Page {
        PingScanner {
            id: pingScanner
        }


        Column {
            spacing: units.gu(1)
            anchors {
                margins: units.gu(2)
                fill: parent
            }

        }
    }
}
