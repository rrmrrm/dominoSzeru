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
    void placeDomino(Deck * deck);
    void moveDomino();
    void changeName(string newName) {name=newName;}
    int getKingPlace() {return king.getPlace();}
};

#endif // PLAYER_H
