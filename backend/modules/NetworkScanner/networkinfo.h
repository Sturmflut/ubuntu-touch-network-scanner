#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QObject>
#include <QVariantList>

#include <QNetworkConfigurationManager>

#include "networkaddress.h"


class NetworkInfo : public QObject
{
    Q_OBJECT

public:
    explicit NetworkInfo(QObject *parent = 0);
    ~NetworkInfo();

    Q_INVOKABLE QVariantList getActiveAddresses();
};

#endif // NETWORKINFO_H
