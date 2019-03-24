#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "jsonloader.h"

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
    void setFormLayout();

    Ui::MainWindow *ui;
    JsonLoader m_JsonLoader;
    QSharedPointer<QFormLayout> m_FormLayout;
    QString m_LastDirectory{"."};
    Logger &m_Logger;
};

#endif // MAINWINDOW_H
