/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *mainLayout;
    QPushButton *setPlayerNumButton;
    QPushButton *connectButton;
    QPushButton *startServerButton;
    QGridLayout *gameMiddleLayout;
    QLCDNumber *turnsLeft;
    QGridLayout *dominosRow1Layout;
    QLabel *label_2;
    QLCDNumber *deckSize;
    QLabel *label;
    QGridLayout *dominosRow2Layout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QHBoxLayout *playerLayout;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(655, 392);
        mainLayout = new QVBoxLayout(Widget);
        mainLayout->setSpacing(6);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        setPlayerNumButton = new QPushButton(Widget);
        setPlayerNumButton->setObjectName(QStringLiteral("setPlayerNumButton"));

        mainLayout->addWidget(setPlayerNumButton);

        connectButton = new QPushButton(Widget);
        connectButton->setObjectName(QStringLiteral("connectButton"));

        mainLayout->addWidget(connectButton);

        startServerButton = new QPushButton(Widget);
        startServerButton->setObjectName(QStringLiteral("startServerButton"));

        mainLayout->addWidget(startServerButton);

        gameMiddleLayout = new QGridLayout();
        gameMiddleLayout->setSpacing(6);
        gameMiddleLayout->setObjectName(QStringLiteral("gameMiddleLayout"));
        turnsLeft = new QLCDNumber(Widget);
        turnsLeft->setObjectName(QStringLiteral("turnsLeft"));

        gameMiddleLayout->addWidget(turnsLeft, 1, 3, 1, 1);

        dominosRow1Layout = new QGridLayout();
        dominosRow1Layout->setSpacing(6);
        dominosRow1Layout->setObjectName(QStringLiteral("dominosRow1Layout"));

        gameMiddleLayout->addLayout(dominosRow1Layout, 1, 0, 2, 1);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gameMiddleLayout->addWidget(label_2, 2, 2, 1, 1);

        deckSize = new QLCDNumber(Widget);
        deckSize->setObjectName(QStringLiteral("deckSize"));

        gameMiddleLayout->addWidget(deckSize, 2, 3, 1, 1);

        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        gameMiddleLayout->addWidget(label, 1, 2, 1, 1);

        dominosRow2Layout = new QGridLayout();
        dominosRow2Layout->setSpacing(6);
        dominosRow2Layout->setObjectName(QStringLiteral("dominosRow2Layout"));

        gameMiddleLayout->addLayout(dominosRow2Layout, 1, 1, 2, 1);


        mainLayout->addLayout(gameMiddleLayout);

        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        mainLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        mainLayout->addWidget(pushButton_2);

        playerLayout = new QHBoxLayout();
        playerLayout->setSpacing(6);
        playerLayout->setObjectName(QStringLiteral("playerLayout"));

        mainLayout->addLayout(playerLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        setPlayerNumButton->setText(QApplication::translate("Widget", "jatekosszam beallitasa", nullptr));
        connectButton->setText(QApplication::translate("Widget", "csatlakozas szerverhez", nullptr));
        startServerButton->setText(QApplication::translate("Widget", "szerver inditasa", nullptr));
        label_2->setText(QApplication::translate("Widget", "pakli m\303\251rete:", nullptr));
        label->setText(QApplication::translate("Widget", "h\303\241tra l\303\251v\305\221 k\303\266r\303\266k:", nullptr));
        pushButton_3->setText(QApplication::translate("Widget", "egyg\303\251pes j\303\241t\303\251k eset\303\251n a t\303\266bbiek t\303\241bl\303\241ja is meg kell jelenjen a f\305\221ablakban", nullptr));
        pushButton_2->setText(QApplication::translate("Widget", "valahol itt lesz a kozos jatekter:2 sor domin\303\263, \303\251s a pakli", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
