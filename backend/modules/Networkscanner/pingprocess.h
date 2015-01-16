#ifndef PINGPROCESS_H
#define PINGPROCESS_H

#include <QObject>

#include <QProcess>

#include <QTimer>


class PingProcess : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running)
    Q_PROPERTY(int numPings READ numPings WRITE setNumPings)
    Q_PROPERTY(int delay READ delay WRITE setDelay)


public:
    explicit PingProcess(QObject *parent = 0);
    ~PingProcess();


    bool running() const { return m_running; }

    int numPings() { return m_numPings; }
    void setNumPings(int num) { m_numPings = num; }

    int delay() { return m_delay; }
    void setDelay(int delay) { m_delay = delay; }


    Q_INVOKABLE void start(QString address);


Q_SIGNALS:
    void pingReceived(int bytes, QString address, int seq, int ttl, float time);
    void error(QString reason);
    void finished();


private slots:
    void processHasOutput();
    void processError(QProcess::ProcessError processError);
    void processFinished();


private:
    bool m_running;

    int m_numPings;
    int m_delay;

    QProcess* m_process;
    QTimer* m_timer;
};

#endif // PINGPROCESS_H
