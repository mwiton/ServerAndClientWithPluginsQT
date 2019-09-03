/********************************************************************************
** Form generated from reading UI file 'display.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Display
{
public:
    QLabel *textLabel;

    void setupUi(QWidget *Display)
    {
        if (Display->objectName().isEmpty())
            Display->setObjectName(QStringLiteral("Display"));
        Display->resize(458, 83);
        Display->setMinimumSize(QSize(135, 66));
        textLabel = new QLabel(Display);
        textLabel->setObjectName(QStringLiteral("textLabel"));
        textLabel->setGeometry(QRect(20, 0, 421, 71));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        textLabel->setPalette(palette);
        QFont font;
        font.setPointSize(8);
        textLabel->setFont(font);

        retranslateUi(Display);

        QMetaObject::connectSlotsByName(Display);
    } // setupUi

    void retranslateUi(QWidget *Display)
    {
        Display->setWindowTitle(QApplication::translate("Display", "Display", Q_NULLPTR));
        textLabel->setText(QApplication::translate("Display", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Display: public Ui_Display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAY_H
