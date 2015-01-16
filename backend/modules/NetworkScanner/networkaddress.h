#ifndef NETWORKADDRESS_H
#define NETWORKADDRESS_H

#include <QObject>

#include <QNetworkConfigurationManager>


class NetworkAddress : public QObject
{
    Q_OBJECT

public:
    explicit NetworkAddress();

    ~NetworkAddress();
};

#endif // NETWORKADDRESS_H
