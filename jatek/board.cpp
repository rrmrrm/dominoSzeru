#ifndef BOARD_CPP
#define BOARD_CPP

#include "board.h"
#include "deck.h"

Board::Board()
{
    EmptyBoard();
}


void Board::EmptyBoard()
{
    Fields.resize(9);
    for(int i = 0; i < 9; i++)
    {
        Fields[i].resize(9);
    }
    Fields[4][4]=CASTLE;

}

std::pair<int,int> Board::getPoint()
{
    //TEMPORARY
    return std::pair<int,int>(0,0);
}


void Board::placeDomino(Domino domino, std::pair<int,int> coordinates)
{
    Fields[coordinates.first][coordinates.second]=domino.GetColors().first;
    if(domino.GetDirection()==UP)
    {
        Fields[coordinates.first-1][coordinates.second]=domino.GetColors().second;
    }
    if(domino.GetDirection()==DOWN)
    {
        Fields[coordinates.first+1][coordinates.second]=domino.GetColors().second;
    }
    if(domino.GetDirection()==LEFT)
    {
        Fields[coordinates.first][coordinates.second+1]=domino.GetColors().second;
    }
    if(domino.GetDirection()==RIGHT)
    {
        Fields[coordinates.first][coordinates.second-1]=domino.GetColors().second;
    }
}


#endif
