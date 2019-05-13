/********************************************************************************
** Form generated from reading UI file 'playerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERWIDGET_H
#define UI_PLAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerWidget
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *PlayerWidget)
    {
        if (PlayerWidget->objectName().isEmpty())
            PlayerWidget->setObjectName(QStringLiteral("PlayerWidget"));
        PlayerWidget->resize(400, 300);
        formLayout = new QFormLayout(PlayerWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout);


        retranslateUi(PlayerWidget);

        QMetaObject::connectSlotsByName(PlayerWidget);
    } // setupUi

    void retranslateUi(QWidget *PlayerWidget)
    {
        PlayerWidget->setWindowTitle(QApplication::translate("PlayerWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerWidget: public Ui_PlayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERWIDGET_H
