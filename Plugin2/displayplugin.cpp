#include "displayplugin.h"
#include <QJsonDocument>
#include <QLabel>
#include <QDebug>

DisplayPlugin::DisplayPlugin():
    m_DisplayWidget(new Display()),
    m_PluginName("Text Label Plugin")
{

}

const QString& DisplayPlugin::getName() const
{
    return m_PluginName;
}

QSharedPointer<QWidget> DisplayPlugin::getWidget()
{
    return m_DisplayWidget;
}

StatusEnum DisplayPlugin::receiveMessage(QString message, QTextStream &errorStream)
{
    StatusEnum status = StatusEnum::FAILURE;
    QJsonDocument jsonMessage = QJsonDocument::fromJson(message.toUtf8());

    if (!jsonMessage.isNull())
    {
        if(jsonMessage.isObject())
        {
            auto messageObject = jsonMessage.object();
            bool allFieldsFound = true;

            QString text;
            if (messageObject.contains("text"))
            {
                auto textValue = messageObject.value("text");
                if (textValue.isString())
                {
                    text = textValue.toString();
                }
                else
                {
                    errorStream << "Text field does not contain string\n";
                    allFieldsFound = false;
                }
            }
            else
            {
                errorStream << "In JSON message there is no text field\n";
                allFieldsFound = false;
            }

            QString colorStylesheet;
            if (messageObject.contains("color"))
            {
                auto colorValue = messageObject.value("color");
                if (colorValue.isString())
                {
                    colorStylesheet = "QLabel { color : " + colorValue.toString() + "; }";
                }
                else
                {
                    errorStream << "Color field does not contain string\n";
                    allFieldsFound = false;
                }
            }
            else
            {
                errorStream << "In JSON message there is no color field\n";
                allFieldsFound = false;
            }

            int size=0;
            if (messageObject.contains("size"))
            {
                auto sizeValue = messageObject.value("size");

                if (sizeValue.isString())
                {
                    bool isNumber = false;
                    size = sizeValue.toString().toInt(&isNumber);
                    if(!isNumber)
                    {
                        errorStream << "Size field is not integer\n";
                        allFieldsFound = false;
                    }
                }
                else
                {
                    errorStream << "Size field does not contain string\n";
                    allFieldsFound = false;
                }
            }
            else
            {
                errorStream << "In JSON message there is no size field\n";
                allFieldsFound = false;
            }

            bool alignToRight=false;
            if (messageObject.contains("alignRight"))
            {
                auto alignValue = messageObject.value("alignRight");
                if (alignValue.isString() && (alignValue.toString() == "true" || alignValue.toString() == "false"))
                {
                    if (alignValue.toString() == "true")
                    {
                        alignToRight = true;
                    }
                    else
                    {
                        alignToRight = false;
                    }
                }
                else
                {
                    errorStream << "alignRight field does not contain bool value\n";
                    allFieldsFound = false;
                }
            }
            else
            {
                errorStream << "In JSON message there is no alignRight field\n";
                allFieldsFound = false;
            }

            if (allFieldsFound)
            {
                mutex.lock();
                QLabel *labelObject = m_DisplayWidget->ui->textLabel;
                labelObject->setText(text);
                auto fontObject = labelObject->font();
                fontObject.setPointSize(size);
                labelObject->setFont(fontObject);
                labelObject->setStyleSheet(colorStylesheet);
                if(alignToRight)
                {
                    labelObject->setAlignment(Qt::AlignRight);
                }
                else
                {
                    labelObject->setAlignment(Qt::AlignLeft);
                }
                mutex.unlock();
                status = StatusEnum::SUCCESS;
            }
        }
        else
        {
            errorStream << "Sent JSON is not an object\n";
        }
    }
    else
    {
        errorStream << "Sent JSON is invalid\n";
    }
    errorStream.flush();
    return status;
}
