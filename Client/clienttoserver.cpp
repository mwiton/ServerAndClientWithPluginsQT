#include "clienttoserver.h"

ClientToServer::ClientToServer(QObject *parent) : QObject(parent), m_Logger(Logger::getLogger()), m_ConnectedSocket(false)
{

}

void ClientToServer::connectToServer(QString address, int port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

    m_Logger << "Connecting to server program...\n";

    socket->connectToHost(address, port);
}

void ClientToServer::connected()
{
    m_ConnectedSocket = true;
    m_Logger << "Connected to server program.\n";
}

void ClientToServer::disconnected()
{
    m_ConnectedSocket = false;
    m_Logger << "Disconnected from server program.\n";
}

void ClientToServer::bytesWritten(qint64 bytes)
{
    m_Logger << bytes << " bytes were sent.\n";
}

void ClientToServer::readyRead()
{
    m_Logger << "Received messag from server: " << socket->readAll() << '\n';
}

void ClientToServer::sendJsonMessage(const QByteArray &jsonMessage)
{
    if (m_ConnectedSocket)
    {
        socket->write(jsonMessage);
    }
    else
    {
        m_Logger << "The socket is not connected to server.\n";
    }
}

ClientToServer::~ClientToServer()
{
    socket->disconnectFromHost();
    delete socket;
}
