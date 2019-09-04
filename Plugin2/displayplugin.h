#ifndef DISPLAYPLUGIN_H
#define DISPLAYPLUGIN_H

#include "plugininterface.h"
#include "display.h"

#include <QObject>
#include <QtPlugin>
#include <QMutex>

class DisplayPlugin : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "pl.mwiton.PluginInterface" FILE "textplugin.json")
    Q_INTERFACES(PluginInterface)
public:
    DisplayPlugin();
    virtual ~DisplayPlugin() {}
    virtual const QString& getName() const override;
    virtual QSharedPointer<QWidget> getWidget() override;
    virtual StatusEnum receiveMessage(QString message, QTextStream &errorStream) override;

private:
    // get value of field sent in JSON
    QPair <QString, bool> DisplayPlugin::getStringFromJSON(const QJsonObject &messageObject, const QString &nameOfValue, QTextStream &errorStream);

    QSharedPointer<Display> m_DisplayWidget;
    const QString m_PluginName;
    QMutex mutex;
};

#endif // DISPLAYPLUGIN_H
