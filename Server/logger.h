#ifndef LOGGER_H
#define LOGGER_H

#include <QTextStream>

class Logger : public QObject {
    Q_OBJECT

public:
    static Logger& getLogger();

signals:
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
