#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <QString>
#include <QWidget>

#include <QMouseEvent>

#include "tablewidget.h"
#include "playerwidget.h"

namespace Ui {
class Widget;
}


class Widget : public QWidget{
    Q_OBJECT

    Ui::Widget *ui;

public:
    int playerNum ;
    vector<PlayerWidget*> players;

    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void setPlayernum();

    void showNewDominos();

    void putKingConfirmed(int pos, int player);


    ///show domino placed,and
    ///show next player's domino over his/her table's center
    void addDominoConfirmed(Domino& d);


    ///winners contains the winners' indexes in the players array
    void show_winner( vector<int> winners);

    ///todo halozati jaték nézetét megírni

    ///todo:
    /// hatralevo korok kiirása
    /// maradek pakli méretének kiirasa

    //---------------------------------------------------------
signals:
    void PutKingAttempt();

    void AddDominoAttempt();

};

#endif // WIDGET_H
