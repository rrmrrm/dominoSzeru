#ifndef BOARD_CPP
#define BOARD_CPP

#include "board.h"
#include "deck.h"
#include "common.h"
#include <iostream>

Board::Board()
{
    EmptyBoard();
}


void Board::EmptyBoard()
{
    Fields.resize(5);
    for(int i = 0; i < 5; i++)
    {
        Fields[i].resize(5);
        for(int j = 0; j < 5; j++)
        {
            Fields[i][j]=EMPTY;
        }
    }
    Fields[2][2]=CASTLE;

}

std::pair<int,int> Board::getPoint()
{
    //TEMPORARY
    int ures=0;
    int pontok=0;
    vector<vector<bool>> calculated;
    calculated.resize(5);
    for(int i = 0; i < 5; i++)
    {
        calculated[i].resize(5);
        for(int j = 0; j < 5; j++)
        {
            calculated[i][j]=false;
        }
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j< 5; j++)
        {
            if(Fields[i][j]==EMPTY)
            {
                ures++;
            }

            if(!calculated[i][j])
            {

            }
        }
    }




    return std::pair<int,int>(25-ures,ures);

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
        Fields[coordinates.first][coordinates.second-1]=domino.GetColors().second;
    }
    if(domino.GetDirection()==RIGHT)
    {
        Fields[coordinates.first][coordinates.second+1]=domino.GetColors().second;
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            std::cout << Fields[i][j]<< " ";
        }
        std::cout << std::endl;
    }

    cout << "Pontok:" << getPoint().first << " " << getPoint().second << endl;
}



#endif
