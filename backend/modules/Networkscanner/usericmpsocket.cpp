#include <QDebug>

#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

#include "pingprocess.h"


UserICMPSocket::UserICMPSocket(QObject *parent) :
    QObject(parent)
{
    // Allocate the socket
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);

    if(m_socket < 0)
    {
        qDebug() << "socket() errno " << QString::number(errno);
    }
}


UserICMPSocket::~UserICMPSocket() {
    close(m_socket);
}



void UserICMPSocket::sendEchoRequest(QHostAddress address)
{
    struct sockaddr_in addr;
    struct icmphdr icmp_hdr;
    char packetdata[sizeof(icmp_hdr) + 5];

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(address.toIPv4Address());

    memset(&icmp_hdr, 0, sizeof(icmp_hdr));
    icmp_hdr.type = ICMP_ECHO;
    icmp_hdr.un.echo.id = 1234;
    icmp_hdr.un.echo.sequence = 1;

    memcpy(packetdata, &icmp_hdr, sizeof(icmp_hdr));
    memcpy(packetdata + sizeof(icmp_hdr), "12345", 5);

    if(sendto(m_socket, packetdata, sizeof(packetdata), 0, (struct sockaddr*) &addr, sizeof(addr)) < 0)
        qDebug() << "sendto() errno" << QString::number(errno);
    else
        qDebug("ICMP sent");
}
