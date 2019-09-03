#include "componentforjsonscheme.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>
#include <QJsonArray>

const QMap<QString, EType> ComponentForJsonScheme::pairsForEnum = {
    {"INTEGER", EType::INTEGER},
    {"NUMBER", EType::NUMBER},
    {"STRING", EType::STRING},
    {"ENUM", EType::ENUM},
    {"BOOL", EType::BOOL}
};

ComponentJsonField::ComponentJsonField(): type(EType::UNDEFINED) {}

ComponentForJsonScheme::ComponentForJsonScheme(const QJsonObject &schemaObject): m_SchemaObject(schemaObject),  m_Logger(Logger::getLogger())
{
    m_Fields.clear();
    QJsonValue nameValue = schemaObject.value("title");
    if (nameValue == QJsonValue::Undefined || !nameValue.isString())
    {
        m_Logger << "There is no name or wrong defined\n";
    }
    else
    {
        m_Name = nameValue.toString();
    }
    QJsonValue propertiesValue = schemaObject.value("properties");
    if (propertiesValue == QJsonValue::Undefined || !propertiesValue.isObject())
    {
        m_Logger << "There is no properties or wrong defined\n";
    }
    else
    {
        QJsonObject propertiesObject = propertiesValue.toObject();
        for(auto fieldName : propertiesObject.keys())
        {
            QSharedPointer<ComponentJsonField> jsonFieldComponent(new ComponentJsonField());
            jsonFieldComponent->name = fieldName;
            QJsonValue fieldObjectValue = propertiesObject.value(fieldName);
            if (!fieldObjectValue.isObject())
            {
                m_Logger << "There is wrong defined field object\n";
            }
            else
            {
                QJsonObject fielsObject = fieldObjectValue.toObject();
                QJsonValue descriptionValue = fielsObject.value("description");
                if (descriptionValue == QJsonValue::Undefined || !descriptionValue.isString())
                {
                    m_Logger << "There is wrong defined description\n";
                }
                else
                {
                    jsonFieldComponent->description = descriptionValue.toString();
                }

                QJsonValue typeValue = fielsObject.value("type");
                if (typeValue == QJsonValue::Undefined || !typeValue.isString())
                {
                    m_Logger << "There is wrong defined type\n";
                }
                else
                {
                    EType type = getEnumType(typeValue.toString());
                    if (type == EType::UNDEFINED)
                    {
                        m_Logger << "Given type is incorrect or unhandled\n";
                    }
                    jsonFieldComponent->type = type;
                }

                QJsonValue enumValue = fielsObject.value("enum");
                if (enumValue != QJsonValue::Undefined && enumValue.isArray())
                {
                    QJsonArray array = enumValue.toArray();
                    for (auto value : array)
                    {
                        if (value.isString())
                        {
                            jsonFieldComponent->valuesForEnum.push_back(value.toString());
                        }
                        else if (value.isDouble())
                        {
                            jsonFieldComponent->valuesForEnum.push_back(QString::number(value.toDouble()));
                        }
                        else
                        {
                            m_Logger << "Wrong defind value in enum for " << fieldName << "\n";
                        }
                    }
                }

                if (jsonFieldComponent->type != EType::UNDEFINED || !jsonFieldComponent->valuesForEnum.empty())
                {
                    m_Fields.push_back(jsonFieldComponent);
                }
            }
        }
    }

    createQFormLayout();
}



QJsonDocument ComponentForJsonScheme::createJsonMessage()
{
    QJsonObject jsonObject;
    for (auto field : m_Fields)
    {
        jsonObject[field->name] = field->value;
    }
    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc;
}

EType ComponentForJsonScheme::getEnumType(QString name)
{
    auto findType = pairsForEnum.find(name.toUpper());
    EType type = findType != pairsForEnum.end() ? *findType : EType::UNDEFINED;
    return type;
}

void ComponentForJsonScheme::createQFormLayout()
{
    if (m_Fields.empty())
    {
        m_Logger << "No fields to show\n";
        return;
    }

    m_FormLayout = QSharedPointer<QFormLayout>(new QFormLayout());
    for (auto fieldIter = m_Fields.begin(); fieldIter != m_Fields.end(); ++fieldIter)
    {
        if (!(*fieldIter)->valuesForEnum.empty())
        {
            QComboBox *comboBox = new QComboBox();
            comboBox->addItem("");
            for (QString enumValue : (*fieldIter)->valuesForEnum)
            {
                comboBox->addItem(enumValue);
            }
            QObject::connect(comboBox, SIGNAL(currentIndexChanged(QString)), fieldIter->data(), SLOT(setValue(QString)));
            (*fieldIter)->widget = QSharedPointer<QWidget>(comboBox);
        }
        else if((*fieldIter)->type == EType::BOOL)
        {
            QComboBox *comboBox = new QComboBox();
            comboBox->addItem("");
            comboBox->addItem("true");
            comboBox->addItem("false");
            QObject::connect(comboBox, SIGNAL(currentIndexChanged(QString)), fieldIter->data(), SLOT(setValue(QString)));
            (*fieldIter)->widget = QSharedPointer<QWidget>(comboBox);
        }
        else //in other case line edit will be inserted
        {
            QLineEdit *lineEdit = new QLineEdit();
            switch ((*fieldIter)->type) {
            case EType::INTEGER:
                lineEdit->setPlaceholderText("Write integer");
                break;
            case EType::NUMBER:
                lineEdit->setPlaceholderText("Write number");
                break;
            case EType::STRING:
                lineEdit->setPlaceholderText("Write text");
                break;
            default:
                break;
            }
            QObject::connect(lineEdit, SIGNAL(textChanged(QString)), fieldIter->data(), SLOT(setValue(QString)));
            (*fieldIter)->widget = QSharedPointer<QWidget>(lineEdit);
        }

        if((*fieldIter)->widget != nullptr)
        {
            (*fieldIter)->label = QSharedPointer<QLabel>(new QLabel((*fieldIter)->name));
            m_FormLayout->addRow((*fieldIter)->label.data(), (*fieldIter)->widget.data());
        }
    }

    m_Logger << "Created form layout for scheme with name " << m_Name << "\n";
}
