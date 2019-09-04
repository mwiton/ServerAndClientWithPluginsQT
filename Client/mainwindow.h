#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "jsonloader.h"
#include "clienttoserver.h"

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
    /**
     *  Constructor
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     *  Shows window with possibility to choose JSON schema
     */
    void choosePluginFile();

    /**
     *  Sends JSON message with values set by user when user clicks the button
     */
    void sendJsonMessage();

private:
    // Shows form layout with input fields in GUI window
    void setFormLayout();

    Ui::MainWindow *ui;
    JsonLoader m_JsonLoader;
    QSharedPointer<QFormLayout> m_FormLayout;
    QString m_LastDirectory;
    Logger &m_Logger;
    QSharedPointer<ComponentForJsonScheme> jsonComponent;
    ClientToServer m_ClientObject;
};

#endif // MAINWINDOW_H
