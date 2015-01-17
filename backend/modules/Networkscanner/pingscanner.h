#ifndef PINGSCANNER_H
#define PINGSCANNER_H

#include <QObject>

#include "pingprocess.h"


class PingScanner : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int numPings READ numPings WRITE setNumPings)
    Q_PROPERTY(int delay READ delay WRITE setDelay)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout)
    Q_PROPERTY(int running READ isRunning)
    Q_PROPERTY(int concurrency READ concurrency WRITE setConcurrency)


public:
    explicit PingScanner(QObject *parent = 0);
    ~PingScanner();


    int numPings() const { return m_numPings; }
    void setNumPings(int num) { m_numPings = num; }

    int delay() const { return m_delay; }
    void setDelay(int delay) { m_delay = delay; }

    int timeout() const { return m_timeout; }
    void setTimeout(int timeout) { m_timeout = timeout; }

    bool isRunning() const { return m_running; }

    int concurrency() const { return m_concurrency; }
    void setConcurrency(int concurrency);


    Q_INVOKABLE void pingHost(QString address);


Q_SIGNALS:
    void pingReceived(QString address, int bytes, int seq, int ttl, float time);
    void pingTimedOut(QString address, int bytes, int seq, int ttl, float time);
    void finished();


private:
    bool m_running;

    int m_numPings;
    int m_delay;
    int m_timeout;

    int m_concurrency;

    UserICMPSocket m_socket;

    QList<QString> m_workList;
    QList<PingProcess*> m_processList;

    void enqueuePing(QString address);
    void advanceWork();
};

#endif // PINGSCANNER_H

