#ifndef MODEL_H
#define MODEL_H

#include "board.h"
#include "common.h"
#include "Domino.h"
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
    int playernum;
    Player *currentplayer;
    int currentnumber;

public:
    model();

public slots:
    void setPlayernum(int);
    void startGame();
    void PutKingAttempt(int place);
    void AddDominoAttempt();

signals:
    void PutKingConfirm(int place);
    void AddDominoConfirm();

    void newDominos(vector<Domino> dominos);

    void gameOver(  vector<int> winners) ;


    void updateTurnsleft(int number);
    void updateDeckSize(int number);





};

#endif // MODEL_H
