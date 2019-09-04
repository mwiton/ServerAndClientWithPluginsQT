#include "pluginloader.h"
#include <QDebug>

const QMap<StatusEnum, QString> PluginLoader::s_StatusEnumStrigs = QMap<StatusEnum, QString>{
    {StatusEnum::SUCCESS, "SUCCESS"},
    {StatusEnum::FAILURE, "FAILURE"}
};

bool PluginLoader::loadNewPlugin(const QString &fileName)
{
    bool result(false);
    m_PluginLoader.unload();
    m_PluginLoader.setFileName(fileName);
    QObject *plugin = m_PluginLoader.instance();
    if(plugin)
    {
        PluginInterface *pluginImpl = qobject_cast<PluginInterface *>(plugin);
        if (pluginImpl)
        {
            m_Plugin = pluginImpl;
            m_Logger << "Loaded plugin: " << m_Plugin->getName() << '\n';
            result = true;
        }
        else
        {
            m_Logger << "No PluginInterface pointer\n";
        }
    }
    else
    {
        m_Logger << "No pluginLoader instance\n";
    }
    return result;
}

QSharedPointer<QWidget> PluginLoader::getPluginWidget()
{
    if (m_Plugin)
    {
        return m_Plugin->getWidget();
    }
    return nullptr;
}

void PluginLoader::receiveMessage(const QString &message)
{
    if(m_Plugin != nullptr)
    {
        QByteArray errorByteArray;
        QTextStream errorStream(&errorByteArray);
        StatusEnum status = m_Plugin->receiveMessage(message, errorStream);
        auto findStr = s_StatusEnumStrigs.find(status);
        QString statusStr = findStr != s_StatusEnumStrigs.end() ? *findStr : "";
        m_Logger << "Status of message from plugin is: " << statusStr << '\n';
        if (status == StatusEnum::FAILURE)
        {
            m_Logger << "Error from plugin: " << QString(errorByteArray);
        }
    }
    else
    {
        m_Logger << "Plugin was not loaded\n";
    }
}
