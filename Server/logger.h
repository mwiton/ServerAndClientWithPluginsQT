#ifndef LOGGER_H
#define LOGGER_H

#include <QTextStream>

/**
 *  Class which receives string communications from other classes and sends to connected classes
 */

class Logger : public QObject {
    Q_OBJECT

public:
    /**
     *  Get one created instance of logger
     */
    static Logger& getLogger();

signals:
    /**
     *  Signal with message sent from some class
     */
    void broadcastMessage(QString message);

private:
    static Logger instance;

    template <class T> friend Logger& operator<<(Logger& logger, const T &output)
    {
        QString strStream;
        QTextStream stream(&strStream);
        stream << output;
        emit logger.broadcastMessage(stream.readAll());
        return logger;
    }
};

#endif // LOGGER_H
