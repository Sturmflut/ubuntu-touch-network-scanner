import QtQuick 2.0
import Ubuntu.Components 1.1

import "ui"


MainView {
    id: mainView

    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "mainView"

    // Note! applicationName needs to match the "name" field of the click manifest
    applicationName: "com.ubuntu.developer.sturmflut.networkscanner"

    /*
     This property enables the application to change orientation
     when the device is rotated. The default is false.
    */
    //automaticOrientation: true

    // Removes the old toolbar and enables new features of the new header.
    useDeprecatedToolbar: false

    width: units.gu(50)
    height: units.gu(75)


    Tabs {
        id: tabs


        HostPingTab {
            id: mainPage
        }

        //SubnetPingTab {
        //    id: subnetPingTab
        //}
    }
}

