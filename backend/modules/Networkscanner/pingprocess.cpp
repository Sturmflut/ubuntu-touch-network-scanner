#include <QDebug>

#include "pingprocess.h"


PingProcess::PingProcess(QObject *parent) :
    QObject(parent),
    m_running(false),
    m_numPings(3),
    m_delay(1),
    m_timer(this)
{

}


PingProcess::~PingProcess() {

}


void PingProcess::start(QString address)
{
    if(m_running)
        return;

    m_running = true;

    // Path to the ping binary
    QString program = "/bin/ping";

    // Process arguments
    QStringList arguments;
    arguments << "-c" << QString::number(numPings());
    arguments << "-i" << QString::number(delay());
    arguments << "-s" << "64";
    arguments << address;

    // Process environment
    QProcessEnvironment environment;
    environment.insert("LANG", "C");

    // Create process object
    m_process = new QProcess(this);
    m_process->setReadChannel(QProcess::StandardOutput);
    m_process->setProcessEnvironment(environment);

    // Wire up signals
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(processHasOutput()));
    connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished()));

    // Start process
    m_process->start(program, arguments);
}


void PingProcess::processHasOutput()
{
    // Read all lines from standard output
    while(m_process->canReadLine())
    {
        QString line = QString::fromLocal8Bit(m_process->readLine());

        line = line.replace("\n", "");
        line = line.replace("\r", "");

        qDebug() << line;


        // Parse output
        QStringList list = line.split(" ");

        if((list.length() == 8  || list.length() == 9) && list.at(1) == "bytes" && list.at(2) == "from")
        {
            bool ok;

            // Parse first field (bytes)
            int bytes = list.at(0).toInt(&ok);

            if(!ok)
            {
                qDebug() << "Error converting bytes field of " + line + " to int";
                continue;
            }

            // Parse fourth field (address)
            QString address = list.at(list.length() - 5);
            address = address.left(address.length() - 1);
            address = address.replace("(", "");
            address = address.replace(")", "");

            // Parse fifth field (sequence number)
            QString seqString = list.at(list.length() - 4);
            seqString = seqString.right(seqString.length() - 9);
            int seq = seqString.toInt(&ok);

            if(!ok)
            {
                qDebug() << "Error converting sequence field of " + line + " to int";
                continue;
            }

            // Parse sixth field (TTL)
            QString ttlString = list.at(list.length() - 3);
            ttlString = ttlString.right(ttlString.length() - 4);
            int ttl = ttlString.toInt(&ok);

            if(!ok)
            {
                qDebug() << "Error converting ttl field of " + line + " to int";
                continue;
            }

            // Parse seventh field (time)
            QString timeString = list.at(list.length() - 2);
            timeString = timeString.right(timeString.length() - 5);
            float time = timeString.toFloat(&ok);

            if(!ok)
            {
                qDebug() << "Error converting time field of " + line + " to int";
                continue;
            }

            emit pingReceived(bytes, address, seq, ttl, time);
        }
    }
}


void PingProcess::processError(QProcess::ProcessError processError)
{
    qDebug() << "Process signaled an error";

    processHasOutput();

    delete m_process;

    m_running = false;

    if(processError == QProcess::FailedToStart)
        emit error("Failed to start");
    else
        if(processError == QProcess::Crashed)
            emit error("Crashed");
        else
            emit error("");
}


void PingProcess::processFinished()
{
    qDebug() << "Process is finished";

    processHasOutput();

    delete m_process;

    m_running = false;

    emit finished();
}
