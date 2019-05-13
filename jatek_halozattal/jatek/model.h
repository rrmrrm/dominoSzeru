#ifndef MODEL_H
#define MODEL_H

#include "board.h"
#include "common.h"
#include "domino.h"
#include "king.h"
#include "player.h"
#include <vector>
#include <QIcon>
#include <QTcpSocket>
#include <QTcpServer>

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
    QTcpSocket *socket;
    QTcpServer *server;
    bool isServer=false;
    bool isClient=false;
    vector<QTcpSocket*> sockets;
    int clientnum=0;


public:
    model();
public slots:
    void setPlayernum(int);
    void startGame();
    void PutKingAttempt(bool firstDominRow,int place);
    void AddDominoAttempt(int x, int y);
    void rotateDominoAttempt(int player, DIR newDir);
    void playerNumChanged();
    void startServer();
    void connect();
    void newConnnection();
    void readSocket();
    void wantToRead(QString);
signals:
    void PutKingConfirm(bool firstDominRow,int place, int number);
    void AddDominoConfirm(QVector<QVector<COLOR>> currentBoard);
    void rotateDominoConfirm(int player, DIR newDir);
    void showChosenDomino(Domino d);
    void newDominos(vector<Domino> dominos);
    void gameOver(  vector<int> winners) ;
    void updateTurnsleft(int number);
    void updateDeckSize(int number);
    void updateActivePlayer(int number);
    void sendPlayerNum(int number);
    void notTheFirstTurn();
    void readyRead();
    void wantToSend(QString);




};

#endif // MODEL_H
