#include "displayplugin.h"
#include <QJsonDocument>
#include <cmath>

DisplayPlugin::DisplayPlugin():
    m_DisplayWidget(new Display()),
    m_PluginName("Progress Bar Plugin")
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

void DisplayPlugin::findValuesForFields(QMap<QString, JsonValue> &foundKeys, const QJsonObject &messageObject, QTextStream &errorStream)
{
    for (auto messageElement = messageObject.begin(); messageElement != messageObject.end(); ++messageElement)
    {
        auto jsonValue = foundKeys.find(messageElement.key());
        if (jsonValue != foundKeys.end())
        {
            if(messageElement.value().isString())
            {
                bool isNumber = false;
                double value = messageElement.value().toString().toDouble(&isNumber);
                if(isNumber)
                {
                    jsonValue.value().value = value;
                    jsonValue.value().isSet = true;
                }
                else
                {
                    errorStream << "Key " << messageElement.key() << " is not number\n";
                }
            }
            else
            {
                errorStream << "Key " << messageElement.key() << " in JSON is not type of string\n";
            }
        }
    }
}

StatusEnum DisplayPlugin::receiveMessage(QString message, QTextStream &errorStream)
{
    StatusEnum status = StatusEnum::FAILURE;
    QJsonDocument jsonMessage = QJsonDocument::fromJson(message.toUtf8());
    QMap<QString, JsonValue> foundKeys{{"value", JsonValue()}, {"minValue", JsonValue()}, {"maxValue", JsonValue()}};
    if (!jsonMessage.isNull())
    {
        if(jsonMessage.isObject())
        {
            auto messageObject = jsonMessage.object();
            findValuesForFields(foundKeys, messageObject, errorStream);
        
            bool isAllFound = true;
            QString notFoundKeys = "";
            for (auto mapPair = foundKeys.begin(); mapPair != foundKeys.end(); ++ mapPair)
            {
                if (!(mapPair.value().isSet))
                {
                    isAllFound = false;
                    notFoundKeys = notFoundKeys + mapPair.key() + " ";
                }
            }

            if (isAllFound)
            {
                double v = foundKeys["value"].value, min = foundKeys["minValue"].value, max = foundKeys["maxValue"].value, valueToSet;
                if (min <= max)
                {
                    if (v <= min) {
                        valueToSet = 0;
                    }
                    else if (v >= max)
                    {
                        valueToSet = 100;
                    }
                    else {
                        valueToSet = (v - min) / (max - min) * 100;
                    }
                    mutex.lock();
                    m_DisplayWidget->ui->progressBar->setValue(static_cast<int>(round(valueToSet)));
                    mutex.unlock();
                    status = StatusEnum::SUCCESS;
                }
                else
                {
                    errorStream << "Max value should be larger than min value\n";
                }
            }
            else
            {
                errorStream << "Not found or incorrect values in message: " << notFoundKeys << '\n';
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
