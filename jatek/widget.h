#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

#include "tablewidget.h"
#include "playerwidget.h"

#include "model.h"
namespace Ui {
class Widget;
}

using namespace std;
class Widget : public QWidget{
    Q_OBJECT

    Ui::Widget *ui;
    model* m;
    vector<QPushButton*> dominoRow1;
public:
    int playerNum ;
    vector<PlayerWidget*> players;

    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void showNewDominos(vector<Domino>);

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
