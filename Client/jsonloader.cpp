#include "jsonloader.h"
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QJsonDocument>

JsonLoader::JsonLoader() :  m_Logger(Logger::getLogger())
{

}

bool JsonLoader::loadFile(QString fileName)
{
    bool result = false;
    QFile jsonFile(fileName);
    if(!jsonFile.open(QIODevice::ReadOnly))
    {
        m_Logger << "File " << fileName << " cannot be opened\n";
    }
    QByteArray byteData = jsonFile.readAll();
    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(byteData, &jsonError);
    if (jsonDocument.isNull())
    {
        m_Logger << "Error during loading json document: " << jsonError.errorString() << '\n';
    }
    if (!jsonDocument.isObject())
    {
        m_Logger << "Schema should be a json object\n";
    }
    else
    {
        m_CurrrentJsonScheme = QSharedPointer<ComponentForJsonScheme>(new ComponentForJsonScheme(jsonDocument.object()));
        result = true;
    }
    return result;
}

QSharedPointer<ComponentForJsonScheme> JsonLoader::getJsonComponent()
{
    return m_CurrrentJsonScheme;
}


