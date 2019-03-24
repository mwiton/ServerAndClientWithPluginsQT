#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Logger(Logger::getLogger())
{
    ui->setupUi(this);
    connect(ui->chooseFileButton, SIGNAL(released()), this, SLOT(choosePluginFile()));
    connect(&m_Logger, SIGNAL(broadcastMessage(QString)), ui->loggerTextArea, SLOT(insertPlainText(QString)));
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
    m_FormLayout = m_JsonLoader.getFormLayout();
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

MainWindow::~MainWindow()
{
    delete ui;
}
