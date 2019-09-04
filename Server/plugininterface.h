#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QSharedPointer>
#include <QTextStream>

enum class StatusEnum{
    SUCCESS,
    FAILURE
};

/**
 *  Interface for plugin which can be changed by external JSON messages
 */
class PluginInterface
{
public:
    virtual ~PluginInterface() {}

    /**
     *  Return name of plugin
     */
    virtual const QString& getName() const = 0;

    /**
     *  Return widget with plugin content
     *  @return Pointer to plugin widget
     */
    virtual QSharedPointer<QWidget> getWidget() = 0;

    /**
     *  Receives external JSON message and changes its own widgets
     *  @param message External message with json
     *  @param errorStream stream to which are inserted messages about errors in handling JSON
     *  @return If JSON was correct and widget was changed
     */
    virtual StatusEnum receiveMessage(QString message, QTextStream &errorStream) = 0;
};

#define PLUGININTERFACE_iid "pl.mwiton.PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PLUGININTERFACE_iid)

#endif // PLUGININTERFACE_H
