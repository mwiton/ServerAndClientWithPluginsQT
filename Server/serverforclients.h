#ifndef SERVERFORCLIENTS_H
#define SERVERFORCLIENTS_H

#include <QTcpServer>
#include <QVector>
#include "serverthread.h"

/**
 *  Class which initializes server litening for JSONs
 */
class ServerForClients : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerForClients(QObject *parent = 0);

    /**
     *  Starts server
     *  @param port On which port server will listen
     */
    void startServer(int port);
    ~ServerForClients();

signals:
    /**
     *  Receives message from one of client sockets
     *  @param message Content of message
     */
    void messageReceived(QString message);

public slots:
    /**
     *  Receives message from thread which listen to client
     *  @param message Content of message
     */
    void receiveMessageFromThread(QString message);

protected:
    /**
     *  Initialized connection from new client and creates thread with socket for this client
     *  @param socketDescriptor Descriptor of new socket
     */
    void incomingConnection(qintptr socketDescriptor);

private:
    Logger &m_Logger;
    QVector<QSharedPointer<ServerThread>> threads;
};

#endif // SERVERFORCLIENTS_H
