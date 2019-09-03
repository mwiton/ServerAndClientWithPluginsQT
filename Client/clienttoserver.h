#ifndef CLIENTTOSERVER_H
#define CLIENTTOSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include "logger.h"

class ClientToServer : public QObject
{
    Q_OBJECT
public:
    explicit ClientToServer(QObject *parent = 0);
    void connectToServer(QString address, int port);
    void sendJsonMessage(const QByteArray &jsonMessage);
    ~ClientToServer();

signals:

public slots:

    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;
    Logger &m_Logger;
    bool m_ConnectedSocket;
};

#endif // CLIENTTOSERVER_H
