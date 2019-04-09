#ifndef PLAYER_H
#define PLAYER_H

#include "King.h"
#include "Board.h"
#include <string>

using namespace std;

class Player
{
    King* king;
    Board* board;
    string name;
public:
    Player();
    ~Player();
    void placeKing(int place);
    void placeDomino();
    void moveDomino();
    void changeName(string newName) {name=newName;}
};

#endif // PLAYER_H