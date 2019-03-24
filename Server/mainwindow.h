#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plugininterface.h"
#include <QSharedPointer>
#include "pluginloader.h"
#include "logger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void choosePluginFile();

private:
    Ui::MainWindow *ui;
    PluginLoader m_PluginLoader;
    QString m_LastDirectory{"."};
    QSharedPointer<QWidget> m_CurrentPluginWidget;
    Logger &m_Logger;

    void setPluginDisplay();
};

#endif // MAINWINDOW_H
