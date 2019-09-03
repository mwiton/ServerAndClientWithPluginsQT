#ifndef COMPONENTFORJSONSCHEME_H
#define COMPONENTFORJSONSCHEME_H

#include <QVector>
#include <QFormLayout>
#include <QWidget>
#include <QJsonObject>
#include <QObject>
#include <QDebug>
#include <QLabel>

#include "logger.h"

enum class EType {
    UNDEFINED,
    INTEGER,
    NUMBER,
    STRING,
    ENUM,
    BOOL
};

class ComponentJsonField: public QObject
{
    Q_OBJECT

public:
    ComponentJsonField();

    EType type;
    QString name;
    QString description;
    QVector<QString> valuesForEnum;
    QString value;
    QSharedPointer<QWidget> widget;
    QSharedPointer<QLabel> label;

public slots:
    void setValue(const QString &newValue)
    {
        value = newValue;
    }
};

class ComponentForJsonScheme
{
public:
    ComponentForJsonScheme(const QJsonObject &schemaObject);
    QJsonDocument createJsonMessage();

    const QString& getName()
    {
        return m_Name;
    }

    QSharedPointer<QFormLayout> getFormLayout()
    {
        return m_FormLayout;
    }


private:
    EType getEnumType(QString name);
    void createQFormLayout();

    QJsonObject m_SchemaObject;
    QSharedPointer<QFormLayout> m_FormLayout;
    QVector<QSharedPointer<ComponentJsonField>> m_Fields;
    QString m_Name;
    Logger &m_Logger;

    static const QMap<QString, EType> pairsForEnum;
};

#endif // COMPONENTFORJSONSCHEME_H
