#include "displayplugin.h"
#include <QDebug>


const QString& DisplayPlugin::getName() const
{
    return m_PluginName;
}

QSharedPointer<QWidget> DisplayPlugin::getWidget()
{
    return m_DisplayWidget;
}

StatusEnum DisplayPlugin::receiveMessage(QString message)
{
    qDebug() << "Receive message: " << message << "\n";
    return StatusEnum::SUCCESS;
}
