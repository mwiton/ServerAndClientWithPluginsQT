#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPluginLoader>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_LastDirectory(QDir::currentPath()),
    m_Logger(Logger::getLogger()),
    serverObject(new ServerForClients)
{
    ui->setupUi(this);
    connect(ui->chooseFileButton, SIGNAL(released()), this, SLOT(choosePluginFile()));
    connect(ui->actionChoose_plugin, SIGNAL(triggered(bool)), this, SLOT(choosePluginFile()));
    connect(serverObject.data(), SIGNAL(messageReceived(QString)), this, SLOT(sendMessageToPlugin(QString)));
    connect(&m_Logger, SIGNAL(broadcastMessage(QString)), ui->loggerTextArea, SLOT(appendPlainText(QString)));
    serverObject->startServer(1234);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::choosePluginFile()
{
    QUrl pluginFileName = QFileDialog::getOpenFileUrl(this, "Open plugin", m_LastDirectory, "Plugin files (*.dll *.so)");
    if(!pluginFileName.isLocalFile())
    {
        return;
    }
    m_LastDirectory = pluginFileName.adjusted(QUrl::UrlFormattingOption::RemoveFilename).toLocalFile();
    bool resultLoading = m_PluginLoader.loadNewPlugin(pluginFileName.toLocalFile());
    if (resultLoading)
    {
        setPluginDisplay();
    }
    else
    {
        m_Logger << "Loading of plugin with path " << pluginFileName.toLocalFile() << " was unsuccsesful" << '\n';
    }
}

void MainWindow::setPluginDisplay()
{
    // "D:\\Wlasne_pliki\\OKNO_PW\\CPP\\Plugin\\pluginBuild\\displayplugind.dll"
    QHBoxLayout *horizontalLayout = ui->horizontalLayout;
    if (!m_CurrentPluginWidget)
    {
        horizontalLayout->takeAt(horizontalLayout->indexOf(ui->instructionLabel));
        ui->instructionLabel->setVisible(false);
        horizontalLayout->takeAt(horizontalLayout->indexOf(ui->chooseFileButton));
        ui->chooseFileButton->setVisible(false);
    }
    else
    {
        horizontalLayout->takeAt(horizontalLayout->indexOf(m_CurrentPluginWidget.data()));
    }
    m_CurrentPluginWidget = m_PluginLoader.getPluginWidget();
    if(m_CurrentPluginWidget)
    {
        QWidget *pluginWidget = m_CurrentPluginWidget.data();
        horizontalLayout->addWidget(pluginWidget);
    }
    else
    {
        m_Logger << "No plugin widget\n";
    }
}

void MainWindow::sendMessageToPlugin(QString data)
{
    m_PluginLoader.receiveMessage(data);

}
