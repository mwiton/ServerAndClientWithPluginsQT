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

QPair <QString, bool> DisplayPlugin::getStringFromJSON(const QJsonObject &messageObject, const QString &nameOfValue, QTextStream &errorStream)
{
    QPair <QString, bool> value{"", false};
    if (messageObject.contains(nameOfValue))
    {
        auto valueObject = messageObject.value(nameOfValue);
        if (valueObject.isString())
        {
            value.first = valueObject.toString();
            value.second = true;
        }
        else
        {
            errorStream << nameOfValue << " field does not contain string\n";
        }
    }
    else
    {
        errorStream << "In JSON message there is no " << nameOfValue << " field\n";
    }
    return value;
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
            auto valueFromJson = getStringFromJSON(messageObject, "text", errorStream);
            QString text = valueFromJson.first;
            allFieldsFound = valueFromJson.second : allFieldsFound ? false;

            valueFromJson = getStringFromJSON(messageObject, "color", errorStream);
            QString colorStylesheet = "QLabel { color : " + valueFromJson.first + "; }";
            allFieldsFound = valueFromJson.second : allFieldsFound ? false;

            bool isNumber = false;
            valueFromJson = getStringFromJSON(messageObject, "size", errorStream);
            int size = valueFromJson.first.toInt(&isNumber);
            allFieldsFound = valueFromJson.second : allFieldsFound ? false;
            if(!isNumber)
            {
                errorStream << "Size field is not integer\n";
                allFieldsFound = false;
            }

            valueFromJson = getStringFromJSON(messageObject, "alignRight", errorStream);
            bool alignToRight=false;
            if (valueFromJson.first.toString() == "true" || valueFromJson.first.toString() == "false")
            {
                alignToRight = valueFromJson.first.toString() == "true";
            }
            else
            {
                errorStream << "alignRight field does not contain bool value\n";
                allFieldsFound = false;
            }
            allFieldsFound = valueFromJson.second : allFieldsFound ? false;

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
