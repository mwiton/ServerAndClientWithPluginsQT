#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QJsonDocument>

const QString ADDRESS = "localhost";
const int PORT = 1234;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_LastDirectory(QDir::currentPath()),
    m_Logger(Logger::getLogger()),
    m_ClientObject(this)
{
    ui->setupUi(this);
    connect(ui->chooseFileButton, SIGNAL(released()), this, SLOT(choosePluginFile()));
    connect(&m_Logger, SIGNAL(broadcastMessage(QString)), ui->loggerTextArea, SLOT(insertPlainText(QString)));

    connect(ui->sendMessageButton, SIGNAL(released()), this, SLOT(sendJsonMessage()));

    m_ClientObject.connectToServer(ADDRESS, PORT);
}

void MainWindow::choosePluginFile()
{
    QUrl jsonFileName = QFileDialog::getOpenFileUrl(this, "Open schema file", m_LastDirectory, "Json schema files (*.json)");
    if(!jsonFileName.isLocalFile())
    {
        return;
    }
    m_LastDirectory = jsonFileName.adjusted(QUrl::UrlFormattingOption::RemoveFilename).toLocalFile();
    bool resultLoading = m_JsonLoader.loadFile(jsonFileName.toLocalFile());
    if (resultLoading)
    {
        jsonComponent = m_JsonLoader.getJsonComponent();
        setFormLayout();
    }
    else
    {
        m_Logger << "Loading of schema with path " << jsonFileName.toLocalFile() << " was unsuccsesful" << '\n';
    }
}

void MainWindow::setFormLayout()
{
    QVBoxLayout *verticalLayout = ui->verticalLayout;
    if (m_FormLayout)
    {
         verticalLayout->takeAt(1);
    }
    m_FormLayout = jsonComponent->getFormLayout();
    if(m_FormLayout)
    {
        QLayout *formWidget = m_FormLayout.data();
        verticalLayout->insertLayout(1, formWidget);
    }
    else
    {
        m_Logger << "No form widget\n";
    }
}

void MainWindow::sendJsonMessage()
{
    if (jsonComponent)
    {
        QJsonDocument jsonDocument = jsonComponent->createJsonMessage();
        auto dataToSend = jsonDocument.toJson();
        m_ClientObject.sendJsonMessage(dataToSend);
        m_Logger << "Sent json: " << QString(dataToSend) << '\n';
    }
    else
    {
        m_Logger << "No json file selected\n";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
