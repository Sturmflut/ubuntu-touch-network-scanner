import QtQuick 2.0

import Ubuntu.Components 1.1
import Ubuntu.Components.Popups 1.0

import NetworkScanner 1.0


Component {
    Dialog {
        id: dialogue

        title: i18n.tr("Subnets")


        NetworkInfo {
            id: networkInfo
        }


        OptionSelector {
            id: interfaceSelector

            text: i18n.tr("Select a subnet:")
            model: networkInfo.getActiveAddresses()
            expanded: true
        }

        Row {
            width: parent.width


            Button {
                id: okButton
                text: i18n.tr("Ok")

                onClicked: {
                    addressSelected(interfaceSelector.model[interfaceSelector.selectedIndex])

                    PopupUtils.close(dialogue)
                }
            }


            Item {
                height: parent.height
                width: parent.width - okButton.width - cancelButton.width
            }


            Button {
                id: cancelButton
                text: i18n.tr("Cancel")

                onClicked: {
                    PopupUtils.close(dialogue)
                }
            }

        }

        signal addressSelected(string address)
    }
}
