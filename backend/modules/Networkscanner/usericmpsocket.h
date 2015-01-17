#ifndef USERICMPSOCKET_H
#define USERICMPSOCKET_H

#include <QObject>

#include <QtNetwork>


class UserICMPSocket : public QObject
{
    Q_OBJECT


public:
    explicit UserICMPSocket(QObject *parent = 0);
    ~UserICMPSocket();


    void sendEchoRequest(QHostAddress address);


private:
    int m_socket;
};

#endif // USERICMPSOCKET_H
