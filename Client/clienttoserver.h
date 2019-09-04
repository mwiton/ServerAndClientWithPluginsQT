#ifndef CLIENTTOSERVER_H
#define CLIENTTOSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include "logger.h"

/**
 *  Class for communication with server
 */

class ClientToServer : public QObject
{
    Q_OBJECT
public:
    /**
     * A constructor.
     */
    explicit ClientToServer(QObject *parent = 0);

    /**
     * Create socket with connection to server with given port and address.
     * @param address Address of server.
     * @param port Port of server
     */
    void connectToServer(QString address, int port);

    /**
     * Send message with json to server
     * @param jsonMessage Byte array containing json
     */
    void sendJsonMessage(const QByteArray &jsonMessage);

    /**
     * A destructor.
     */
    ~ClientToServer();

signals:

public slots:
    /**
     * On established connection with server
     */
    void connected();
    /**
     * On disconnected connection with server
     */
    void disconnected();
    /**
     * On succsessful sent message to server
     */
    void bytesWritten(qint64 bytes);
    /**
     * On received message from server
     */
    void readyRead();

private:
    QTcpSocket *socket;
    Logger &m_Logger;
    bool m_ConnectedSocket;
};

#endif // CLIENTTOSERVER_H
