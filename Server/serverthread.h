#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "logger.h"

/**
 *  Thread which listen for messages from one client
 */
class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(qintptr ID, QObject *parent = 0);

    /**
     *  Starts listening
     */
    void run();

signals:
    /**
     *  Received message from client
     *  @param message Content of message
     */
    void messageReceivedfromClient(QString message);

public slots:
    /**
     *  Received message from client and pass it to GUI
     */
    void readyRead();
    /**
     *  Invoked when client disconnects with server
     */
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    Logger &m_Logger;
};

#endif // SERVERTHREAD_H
