#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plugininterface.h"
#include <QSharedPointer>
#include "pluginloader.h"
#include "logger.h"
#include "serverforclients.h"

namespace Ui {
class MainWindow;
}

/**
 *  Class which represents GUI window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     *  Sends received message from server to loaded plugin object
     *  @param Content of message
     */
    void sendMessageToPlugin(QString data);

private slots:
    /**
     *  Shows file choosing window for dll plugin
     */
    void choosePluginFile();

private:
    Ui::MainWindow *ui;
    PluginLoader m_PluginLoader;
    QString m_LastDirectory;
    QSharedPointer<QWidget> m_CurrentPluginWidget;
    Logger &m_Logger;
    QSharedPointer<ServerForClients> serverObject;

    // Shows widget from plugin in GUI window
    void setPluginDisplay();
};

#endif // MAINWINDOW_H
