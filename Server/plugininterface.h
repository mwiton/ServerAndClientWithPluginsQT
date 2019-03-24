#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QSharedPointer>

enum class StatusEnum{
    SUCCESS,
    FAILURE
};

class PluginInterface
{
public:
    virtual ~PluginInterface() {}

    virtual const QString& getName() const = 0;
    virtual QSharedPointer<QWidget> getWidget() = 0;
    virtual StatusEnum receiveMessage(QString message) = 0;
};

#define PLUGININTERFACE_iid "pl.mwiton.PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PLUGININTERFACE_iid)

#endif // PLUGININTERFACE_H
