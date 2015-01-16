#include <QtNetwork>

#include "networkinfo.h"


NetworkInfo::NetworkInfo(QObject *parent) :
    QObject(parent)
{

}


NetworkInfo::~NetworkInfo() {

}


QVariantList NetworkInfo::getActiveAddresses() {
    QVariantList addressList;

    foreach(QNetworkInterface intf, QNetworkInterface::allInterfaces())
    {
        foreach(QNetworkAddressEntry address, intf.addressEntries())
        {
            if(!address.ip().isLoopback() && address.ip().protocol() == QAbstractSocket::IPv4Protocol)
                addressList.append(address.ip().toString() + "/" + address.netmask().toString());
        }
    }

    return addressList;
}

