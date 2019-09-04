#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QFormLayout>
#include <QJsonObject>
#include <QSharedPointer>

#include "componentforjsonscheme.h"

/**
 *  Class which loads JSON file with JSON schema
 */

class JsonLoader
{
public:
    /**
     *  Constructor
     */
    JsonLoader();

    /**
     *  Loads file with JSON schema and creates object representing it
     *  @param fileName Path of JSON file
     */
    bool loadFile(QString fileName);

     /**
     *  Return created object with JSON schema
     *  @return JSON schema object
     */
    QSharedPointer<ComponentForJsonScheme> getJsonComponent();

private:
    QSharedPointer<ComponentForJsonScheme> m_CurrrentJsonScheme;
    Logger &m_Logger;
};

#endif // JSONLOADER_H
