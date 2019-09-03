#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "plugininterface.h"
#include "logger.h"


class PluginLoader
{
public:
    PluginLoader() : m_Plugin(nullptr), m_Logger(Logger::getLogger()) {}
    bool loadNewPlugin(const QString &fileName);
    QSharedPointer<QWidget> getPluginWidget();
    void receiveMessage(const QString &message);

private:
    PluginInterface *m_Plugin;
    Logger &m_Logger;

    static const QMap<StatusEnum, QString> s_StatusEnumStrigs;
};



#endif // PLUGINLOADER_H
