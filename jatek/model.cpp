#include "model.h"

model::model()
{
}


void model::setPlayernum(int number)
{
    playernum=number;
}

void model::startGame()
{
    firstTurn=true;
    deck= new Deck(playernum);
    currentnumber=0;
    sorrend.resize(playernum);
    players.resize(playernum);
    for(int i = 0; i < playernum;i++)
    {
        sorrend[i]=i;
    }
    for(int i = 0; i < 50; i++)
    {
        int a=rand()%playernum;
        int b=rand()%playernum;
        int temp;
        temp=sorrend[a];
        sorrend[a]=sorrend[b];
        sorrend [b]=temp;
    }
    for(int i = 0; i < playernum; i++)
    {
        currentplayer=&players[sorrend[i]];
        AddDominoConfirm();
        emit updateActivePlayer(sorrend[i]);
    }
    deck->draw();
    emit newDominos(deck->getNewOnes());
}

void model::PutKingAttempt(int place)
{
    if(!(deck->taken[place]))
    {
        currentplayer->placeKing(place);
        deck->taken[place]=true;
        PutKingConfirm(place, currentnumber);
        if(currentnumber==playernum)
        {
            deck->draw();
            emit newDominos(deck->getNewOnes());
            currentnumber=-1;
            if(firstTurn)
            {
                firstTurn=false;
                emit notTheFirstTurn();                
            }
        }
        currentnumber++;
        for(int i = 0; i < playernum; i++)
        {
            if(players[i].getKingPlace()==currentnumber)
            {
                currentplayer=&players[i];
            }
        }
    }
    emit updateActivePlayer(currentnumber);
}

void model::AddDominoAttempt()
{
    bool szabalyos=true;
    if(szabalyos)
    {
        currentplayer->placeDomino(deck);
        AddDominoConfirm();
        if(deck->cardsLeftNum()==0)
        {
            PutKingConfirm(-1);
        }
    }
}
