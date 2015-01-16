#include "pingscanner.h"


PingScanner::PingScanner(QObject *parent) :
    QObject(parent),
    m_running(false),
    m_numPings(3),
    m_delay(1),
    m_concurrency(16)
{

}


PingScanner::~PingScanner()
{

}


void PingScanner::setConcurrency(int concurrency)
{
    m_concurrency = concurrency;

    advanceWork();
}



void PingScanner::pingHost(QString address)
{
    enqueuePing(address);
}


void PingScanner::enqueuePing(QString address)
{
    m_workList.append(address);
    m_running = true;

    advanceWork();
}


void PingScanner::advanceWork()
{
    while(!m_workList.isEmpty() && m_processList.count() < m_concurrency)
    {
        QString address = m_workList.takeFirst();

        PingProcess* process = new PingProcess(this);
        process->setNumPings(numPings());
        process->setDelay(delay());

        m_processList.append(process);

        process->start(address);
    }
}
