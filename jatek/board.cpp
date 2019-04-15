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
    Fields[domino.GetPosition().first][domino.GetPosition().second]=domino.GetColors().first;
    if(domino.GetDirection()==UP)
    {
        Fields[domino.GetPosition().first-1][domino.GetPosition().second]=domino.GetColors().second;
    }
    if(domino.GetDirection()==DOWN)
    {
        Fields[domino.GetPosition().first+1][domino.GetPosition().second]=domino.GetColors().second;
    }
    if(domino.GetDirection()==LEFT)
    {
        Fields[domino.GetPosition().first][domino.GetPosition().second+1]=domino.GetColors().second;
    }
    if(domino.GetDirection()==RIGHT)
    {
        Fields[domino.GetPosition().first][domino.GetPosition().second-1]=domino.GetColors().second;
    }
}


#endif
