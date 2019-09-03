#include "serverforclients.h"

ServerForClients::ServerForClients(QObject *parent) :
    QTcpServer(parent),
    m_Logger(Logger::getLogger())
{

}

void ServerForClients::startServer(int port)
{
    if(!this->listen(QHostAddress::Any,port))
    {
        m_Logger << "Could not start server.\n";
    }
    else
    {
        m_Logger << "Listening to port " << port << "...\n";
    }
}

void ServerForClients::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    m_Logger << socketDescriptor << " Connecting...";

    auto threadPointer = QSharedPointer<ServerThread>(new ServerThread(socketDescriptor, this));
    threads.push_back(threadPointer);
    connect(threadPointer.data(), SIGNAL(messageReceivedfromClient(QString)), this, SLOT(receiveMessageFromThread(QString)));

    threadPointer->start();
}

void ServerForClients::receiveMessageFromThread(QString message)
{
    emit messageReceived(message);
}

ServerForClients::~ServerForClients()
{
    for (auto thread : threads)
    {
        thread->exit(1);
    }
    close();
}
