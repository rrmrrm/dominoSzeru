#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QVector>

#include "color.h"
#include "tablewidget.h"
#include "playerwidget.h"

#include "model.h"
#include "dominobutton.h"
namespace Ui {
class Widget;
}

using namespace std;
class Widget : public QWidget, ColorConverter{
    Q_OBJECT

    Ui::Widget *ui;
    model* m;
    vector<DominoButton*> dominoRow1;
    vector<DominoButton*> dominoRow2;
    bool isFirstTurn;
    int dominoSideSize;


    void addSecondDominoRow();
public:
    int playerNum ;
    int activePlayer;
    vector<PlayerWidget*> players;

    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void notTheFirstTurn();

    void dominoRow1Clicked();
    void dominoRow2Clicked();
    void activePlayerUpdated(int);
    void showNewDominos(vector<Domino> v);
    void putKingConfirmed(bool firstDominoRow,int pos, int player);
    void rotateDominoConfirmed(int player, DIR newDir);

    ///show domino placed,and
    ///show next player's domino over his/her table's center
    void addDominoConfirmed(QVector< QVector<COLOR> > newDominos);


    ///winners contains the winners' indexes in the players array
    void show_winner( vector<int> winners);

    void playerDominoClicked();

    //kirajzolja az aktiv jatekos forgathato/lehelyezhető dominóját
    void showChosenDomino(Domino d);
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
