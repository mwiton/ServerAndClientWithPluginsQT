#include "serverthread.h"

ServerThread::ServerThread(qintptr ID, QObject *parent):
    QThread(parent),
    m_Logger(Logger::getLogger())
{
    socketDescriptor = ID;
}

void ServerThread::run()
{
    // thread starts here
    m_Logger << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        m_Logger << "Connection with socket failed: " << socket->error() << '\n';
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    m_Logger << socketDescriptor << " Client connected.\n";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void ServerThread::readyRead()
{
    // get the information
    QByteArray data = socket->readAll();

    // will write on server side window
    m_Logger << socketDescriptor << " Received data: " << data;
    emit messageReceivedfromClient(QString(data));
    //socket->write(Data);
}

void ServerThread::disconnected()
{
    m_Logger << socketDescriptor << " Disconnected";


    socket->deleteLater();
    exit(0);
}
