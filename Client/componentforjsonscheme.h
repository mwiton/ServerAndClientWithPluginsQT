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

/**
 *  Enum with possible value types
 */
enum class EType {
    UNDEFINED,
    INTEGER,
    NUMBER,
    STRING,
    ENUM,
    BOOL
};

/**
 *  Class defining one row of form representing fields of JSON to send
 */
class ComponentJsonField: public QObject
{
    Q_OBJECT

public:
    ComponentJsonField();

    EType type; // type of value
    QString name; // name of value
    QString description; // description of value
    QVector<QString> valuesForEnum; // if value is enum, values possible for this enum
    QString value; // String with value
    QSharedPointer<QWidget> widget; // Widget with input for value
    QSharedPointer<QLabel> label; // Label for form row with value name

public slots:
    /**
     *  Sets new value received from GUI input
     *  @param newValue String with new value
     */
    void setValue(const QString &newValue)
    {
        value = newValue;
    }
};

/**
 *  Class with form layout created according to JSON schema
 */
class ComponentForJsonScheme
{
public:
    /**
     *  Constructor
     *  @param schemaObject JSON schema
     */
    ComponentForJsonScheme(const QJsonObject &schemaObject);

    /**
     *  Creates JSON message to send with values chosen by user in GUI form
     *  @return Object with JSON message
     */
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
    // Get enum type for string from JSON
    EType getEnumType(QString name);
    // Creates form layout with fields contained in JSON schema
    void createQFormLayout();

    QJsonObject m_SchemaObject;
    QSharedPointer<QFormLayout> m_FormLayout;
    QVector<QSharedPointer<ComponentJsonField>> m_Fields;
    QString m_Name;
    Logger &m_Logger;

    static const QMap<QString, EType> pairsForEnum;
};

#endif // COMPONENTFORJSONSCHEME_H
