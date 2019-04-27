#ifndef MODEL_H
#define MODEL_H

#include "board.h"
#include "common.h"
#include "domino.h"
#include "king.h"
#include "player.h"
#include <vector>
#include <QIcon>

using namespace std;

class model : public QObject
{
    Q_OBJECT
    vector<Player> players;
    vector<int> sorrend;
    Deck *deck;
    int playernum=3;
    Player *currentplayer;
    int currentnumber;
    bool firstTurn;

public:
    model();

public slots:
    void setPlayernum(int);
    void startGame();
    void PutKingAttempt(bool firstDominRow,int place);
    void AddDominoAttempt(int x, int y);

signals:
    void PutKingConfirm(bool firstDominRow,int place, int number);
    void AddDominoConfirm(QVector<QVector<COLOR>> currentBoard);

    void newDominos(vector<Domino> dominos);

    void gameOver(  vector<int> winners) ;


    void updateTurnsleft(int number);
    void updateDeckSize(int number);
    void updateActivePlayer(int number);

    void notTheFirstTurn();




};

#endif // MODEL_H
