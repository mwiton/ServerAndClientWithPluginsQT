#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QFormLayout>
#include <QJsonObject>
#include <QSharedPointer>

#include "componentforjsonscheme.h"

class JsonLoader
{
public:
    JsonLoader();
    bool loadFile(QString fileName);
    QSharedPointer<QFormLayout> getFormLayout();

private:
    QSharedPointer<ComponentForJsonScheme> m_CurrrentJsonScheme;
    Logger &m_Logger;
};

#endif // JSONLOADER_H
