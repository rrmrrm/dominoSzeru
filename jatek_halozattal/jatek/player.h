#ifndef PLAYER_H
#define PLAYER_H

#include "king.h"
#include "board.h"
#include "deck.h"
#include <string>

using namespace std;

class Player
{
    King king;
    Board board;
    string name;
public:
    Player();
    //~Player();
    void placeKing(int place);
    void placeDomino(Deck * deck,int x, int y);
    void moveDomino();
    void changeName(string newName) {name=newName;}
    int getKingPlace() {return king.getPlace();}
    QVector<QVector<COLOR>> getFields() { return board.getFields();}
    pair<int,int> getPoint() {return board.getPoint(); }
};

#endif // PLAYER_H
