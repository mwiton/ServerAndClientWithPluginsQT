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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Display
{
public:
    QProgressBar *progressBar;

    void setupUi(QWidget *Display)
    {
        if (Display->objectName().isEmpty())
            Display->setObjectName(QStringLiteral("Display"));
        Display->resize(135, 66);
        Display->setMinimumSize(QSize(135, 66));
        progressBar = new QProgressBar(Display);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 20, 118, 23));
        progressBar->setValue(24);

        retranslateUi(Display);

        QMetaObject::connectSlotsByName(Display);
    } // setupUi

    void retranslateUi(QWidget *Display)
    {
        Display->setWindowTitle(QApplication::translate("Display", "Display", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Display: public Ui_Display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAY_H
