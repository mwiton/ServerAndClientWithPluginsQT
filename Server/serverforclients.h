#ifndef SERVERFORCLIENTS_H
#define SERVERFORCLIENTS_H

#include <QTcpServer>
#include <QVector>
#include "serverthread.h"

class ServerForClients : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerForClients(QObject *parent = 0);
    void startServer(int port);
    ~ServerForClients();

signals:
    void messageReceived(QString message);

public slots:
    void receiveMessageFromThread(QString message);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    Logger &m_Logger;
    QVector<QSharedPointer<ServerThread>> threads;
};

#endif // SERVERFORCLIENTS_H
