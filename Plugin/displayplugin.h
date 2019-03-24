#ifndef DISPLAYPLUGIN_H
#define DISPLAYPLUGIN_H

#include "plugininterface.h"
#include "display.h"

#include <QObject>
#include <QtPlugin>

class DisplayPlugin : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "pl.mwiton.PluginInterface" FILE "displayplugin.json")
    Q_INTERFACES(PluginInterface)
public:
    DisplayPlugin(): m_DisplayWidget(new Display()), m_PluginName("Progress Bar Plugin") {}
    virtual ~DisplayPlugin() {}
    virtual const QString& getName() const override;
    virtual QSharedPointer<QWidget> getWidget() override;
    virtual StatusEnum receiveMessage(QString message) override;

private:
    QSharedPointer<Display> m_DisplayWidget;
    const QString m_PluginName;
};

#endif // DISPLAYPLUGIN_H
