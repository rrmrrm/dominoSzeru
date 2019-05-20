#ifndef DECK_CPP
#define DECK_CPP

#include "deck.h"
#include "common.h"
#include "domino.h"



#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand


Deck::Deck()
{
    dominoes.resize(0);
}


Deck::Deck(int playerNumber)
{
    if(playerNumber==3)
    {
        newOnes.resize(3);
        current.resize(3);
        taken.resize(3);
    }
    else
    {
        newOnes.resize(4);
        current.resize(4);
        taken.resize(4);
    }
    deckSize=playerNumber*12;    
    dominoes.resize(static_cast<unsigned long long>(deckSize));
    Domino dom(SWAMP, FOREST, 2, 1);
    dominoes[0]=Domino(SWAMP, FOREST, 2, 1);
    dominoes[1]=Domino(MOUNTAIN, FOREST, 2, 0);
    dominoes[2]=Domino(FOREST, WHEATFIELD, 0, 0);
    dominoes[3]=Domino(MOUNTAIN, WHEATFIELD, 2, 0);
    dominoes[4]=Domino(MOUNTAIN, WHEATFIELD, 3, 0);
    dominoes[5]=Domino(PASTURE, PASTURE, 0, 0);
    dominoes[6]=Domino(LAKE, FOREST, 0, 0);
    dominoes[7]=Domino(PASTURE, WHEATFIELD, 1, 0);
    dominoes[8]=Domino(PASTURE, SWAMP, 0, 0);
    dominoes[9]=Domino(LAKE, FOREST, 1, 1);
    dominoes[10]=Domino(FOREST, WHEATFIELD, 0, 0);
    dominoes[11]=Domino(WHEATFIELD, WHEATFIELD, 0, 0);
    dominoes[12]=Domino(LAKE, SWAMP, 0, 0);
    dominoes[13]=Domino(WHEATFIELD, WHEATFIELD, 0, 0);
    dominoes[14]=Domino(PASTURE, PASTURE, 1, 0);
    dominoes[15]=Domino(FOREST, WHEATFIELD, 0, 0);
    dominoes[16]=Domino(LAKE, PASTURE, 0, 0);
    dominoes[17]=Domino(PASTURE, WHEATFIELD, 0, 0);
    dominoes[18]=Domino(LAKE, LAKE, 1, 0);
    dominoes[19]=Domino(LAKE, FOREST, 0, 0);
    dominoes[20]=Domino(PASTURE, FOREST, 0, 1);
    dominoes[21]=Domino(LAKE, FOREST, 0, 0);
    dominoes[22]=Domino(SWAMP, WHEATFIELD, 0, 1);
    dominoes[23]=Domino(PASTURE, MOUNTAIN, 2, 1);

    if(playerNumber>2)
    {

        dominoes[24]=Domino(MOUNTAIN, WHEATFIELD, 0, 1);
        dominoes[25]=Domino(LAKE, WHEATFIELD, 0, 0);
        dominoes[26]=Domino(FOREST, WHEATFIELD, 0, 0);
        dominoes[27]=Domino(FOREST, WHEATFIELD, 0, 0);
        dominoes[28]=Domino(WHEATFIELD, WHEATFIELD, 1, 1);
        dominoes[29]=Domino(SWAMP, WHEATFIELD, 0, 0);
        dominoes[30]=Domino(LAKE, WHEATFIELD, 1, 0);
        dominoes[31]=Domino(MOUNTAIN, WHEATFIELD, 2, 1);
        dominoes[32]=Domino(LAKE, FOREST, 0, 0);
        dominoes[33]=Domino(SWAMP, FOREST, 1, 0);
        dominoes[34]=Domino(PASTURE, FOREST, 0, 1);
        dominoes[35]=Domino(LAKE, WHEATFIELD, 0, 0);
    }
    if(playerNumber>3)
    {

        dominoes[36]=Domino(SWAMP, WHEATFIELD, 0, 0);
        dominoes[37]=Domino(FOREST, WHEATFIELD, 0, 0);
        dominoes[38]=Domino(LAKE, SWAMP, 1, 2);
        dominoes[39]=Domino(FOREST, WHEATFIELD, 1, 0);
        dominoes[40]=Domino(FOREST, WHEATFIELD, 0, 0);
        dominoes[41]=Domino(LAKE, PASTURE, 0, 0);
        dominoes[42]=Domino(SWAMP, FOREST, 1, 0);
        dominoes[43]=Domino(LAKE, FOREST, 0, 1);
        dominoes[44]=Domino(LAKE, LAKE, 1, 1);
        dominoes[45]=Domino(FOREST, FOREST, 0, 0);
        dominoes[46]=Domino(LAKE, SWAMP, 0, 0);
        dominoes[47]=Domino(PASTURE, PASTURE, 2, 0);
    }
    shuffle();
    //draw();
}

void Deck::shuffle()
{
    cardsDrawn=0;
    std::srand ( unsigned ( std::time(nullptr) ) );
    std::random_shuffle ( dominoes.begin(), dominoes.end() );
    std::cout << "a kevert pakli:";
    for(int i = 0; i < dominoes.size(); i++)
    {
        std::cout << dominoes[i].GetColors().first << dominoes[i].GetColors().second;

    }
    std::cout << std::endl;
}

int Deck::cardsLeftNum()
{
    return deckSize-cardsDrawn;
}

void Deck::draw()
{
    current=newOnes;
    if(cardsLeftNum()<=0)
    {
        for(int i = 0; i < deckSize/12; i++)
        {
            newOnes[i]=Domino(EMPTY, EMPTY, 0,0);
            cardsDrawn++;
        }

    }
    else
    {
        for(int i = 0; i < deckSize/12; i++)
        {
            newOnes[i]=dominoes[cardsDrawn];
            cardsDrawn++;
        }
        for(int i=0; i < taken.size(); i++)
        {
            taken[i]=false;
        }
        std::cout << "Lapok vissza: " << cardsLeftNum() << std::endl;

    }
}


#endif
