#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "plugininterface.h"
#include "logger.h"

/**
 *  Class which loads plugin dll with plugin object
 */
class PluginLoader
{
public:
    PluginLoader() : m_Plugin(nullptr), m_Logger(Logger::getLogger()) {}

    /**
     *  Loads dll file with plugin
     *  @param File path for plugin to load
     *  @return If loading was succesesful
     */
    bool loadNewPlugin(const QString &fileName);

    /**
     *  Get widget from plugin
     *  @return Pointer to widget
     */
    QSharedPointer<QWidget> getPluginWidget();

    /**
     *  Sends message to plugin object from server socket
     *  @param message Message from socket
     */
    void receiveMessage(const QString &message);

private:
    PluginInterface *m_Plugin;
    Logger &m_Logger;

    static const QMap<StatusEnum, QString> s_StatusEnumStrigs;
};



#endif // PLUGINLOADER_H
