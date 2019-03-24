#include "pluginloader.h"
#include <QPluginLoader>
#include <QDebug>

const QMap<StatusEnum, QString> PluginLoader::s_StatusEnumStrigs = QMap<StatusEnum, QString>{
    {StatusEnum::SUCCESS, "SUCCESS"},
    {StatusEnum::FAILURE, "FAILURE"}
};

bool PluginLoader::loadNewPlugin(const QString &fileName)
{
    bool result(false);
    QPluginLoader pluginLoader(fileName);
    QObject *plugin = pluginLoader.instance();
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

void PluginLoader::receiveMessage(const QString message)
{
    StatusEnum status = m_Plugin->receiveMessage(message);
    auto findStr = s_StatusEnumStrigs.find(status);
    QString statusStr = findStr != s_StatusEnumStrigs.end() ? *findStr : "";
    m_Logger << "Status of message from plugin is: " << statusStr << '\n';
}
