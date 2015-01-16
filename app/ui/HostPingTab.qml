import QtQuick 2.0

import Ubuntu.Components 1.1
import Ubuntu.Components.Popups 1.0

import Networkscanner 1.0

import "../components"


Tab {
    id: hostPingTag
    title: i18n.tr("Ping Host")

    page: Page {
        PingProcess {
            id: pingProcess

            onPingReceived: {
                var line = "PING " + address +
                        " seq=" + seq +
                        " ttl=" + ttl +
                        " time=" + time.toFixed(3) + " ms"

                outputLabel.text = outputLabel.text + line + "\n"
            }

            onFinished: {
                startButton.iconName = "media-playback-start"
            }

            onError: {
                outputLabel.text = reason

                startButton.iconName = "media-playback-start"
            }
        }


        Column {
            spacing: units.gu(1)
            anchors {
                margins: units.gu(2)
                fill: parent
            }


            Row {
                id: controlsRow
                width: parent.width


                TextField {
                    id: addressField

                    text: "127.0.0.1"

                    width: parent.width - startButton.width
                }


                Button {
                    id: startButton

                    iconName: "media-playback-start"

                    width: height

                    onClicked: {
                        if(!pingProcess.running)
                        {
                            outputLabel.text = ""

                            pingProcess.start(addressField.text)

                            iconName = "media-playback-pause"
                        }
                    }
                }
            }


            Label {
                id: outputLabel

                width: parent.width
                height: parent.height - controlsRow.height
            }
        }
    }
}

