#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <string>
#include "common.h"
#include "domino.h"

using namespace std;
class Board
{
    QVector<QVector<COLOR>> Fields;
    int owner;
public:
    Board();
    //~Board();
    std::pair<int,int> getPoint();
    void setOwner(int num) {owner=num;}
    void placeDomino(Domino domino, std::pair<int,int> coordinates);
    void EmptyBoard();
};

#endif // BOARD_H
