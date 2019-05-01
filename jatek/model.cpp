#include "model.h"
#include <iostream>

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
    //for(int i = 0; i < playernum; i++)
    //{
        currentplayer=&players[sorrend[0]];
        //AddDominoConfirm();
        emit updateActivePlayer(sorrend[0]);
        currentnumber=0;
    //}
    deck->draw();
    emit newDominos(deck->getNewOnes());
}

void model::PutKingAttempt(bool firstDominoRow, int place)
{
    if(!(deck->taken[place]))
    {
        currentplayer->placeKing(place);
        deck->taken[place]=true;
        PutKingConfirm(firstDominoRow, place, currentnumber);
        if(currentnumber==(playernum-1))
        {
            if(firstTurn)
            {
                firstTurn=false;
                emit notTheFirstTurn();
            }
            deck->draw();
            emit newDominos(deck->getNewOnes());
            currentnumber=-1;
            for(int i = 0; i < playernum; i++)
            {
                for(int j = 0; j < playernum; j++)
                {
                    if(players[j].getKingPlace()==i)
                    {
                        sorrend[i]=j;
                    }
                }
            }
        }
        currentnumber++;
        currentplayer=&players[sorrend[currentnumber]];
        std::cout << "JELENLEGI JATEKOS: " << currentnumber << std::endl;
    }
    emit updateActivePlayer(currentnumber);
}

void model::AddDominoAttempt(int x, int y)
{
    bool szabalyos=true;
    /*
        if(x<0 || y < 0 || x >= 5 || y >= 5)
            szabalyos = false;
        DIR dominoDir = deck->getCurrent().at(currentplayer->getKingPlace()).GetDirection();

        //próbálok összevonni lehetőségeket, hogy ne kelljen elágazás-tengert írnom
        //ehez bevezetek 4 változót

        //megállapítom hogy a dominó melyik oldala van balfentebb és melyik ballentebba másikhoz képest
        int upperLeftX;
        int upperLeftY;
        COLOR upperLeftColor;
        int lowerRigthX;
        int lowerRigthY;
        COLOR lowerRigthColor;
        switch(dominoDir){
        case UP:{
            upperLeftX=x-1; upperLeftY=y; break;
            lowerRigthX=x; lowerRigthY=y; break;
            upperLeftColor =
        }
        case DOWN:{
            upperLeftX=x; upperLeftY=y; break;
            lowerRigthX=x+1; lowerRigthY=y; break;
        }
        case LEFT:{
            upperLeftX=x; upperLeftY=y+1; break;
            lowerRigthX=x; lowerRigthY=y; break;
        }
        case RIGHT:{
            upperLeftX=x; upperLeftY=y; break;
            lowerRigthX=x; lowerRigthY=y-1; break;
        }
        }

        //megállapítom a balfelső és a jobbalsó dominó-oldal koorinátáit
        switch(dominoDir){
        case UP:{}
        case DOWN:{break;}
        case LEFT:{}
        case RIGHT:{break;}
        }

        if(x > 0){
            currentplayer->board.getFields()[x-1][y];
        }
        */

    if(szabalyos)
    {
        currentplayer->placeDomino(deck, x, y);
        AddDominoConfirm(currentplayer->getFields());
        if(deck->cardsLeftNum()==0)
        {
            PutKingConfirm(true,-1, currentnumber);
        }
    }
}

void model::rotateDominoAttempt(int player, DIR newDir){
    if( player == currentnumber){
        ///elforgatom a jatekos dominojat newDire fele
        deck->Current().at(currentplayer->getKingPlace()).Rotate(newDir);
        ///jelzem a nezetnek, hogy elforgattuk a dominot a modellben
        rotateDominoConfirm(player, newDir);
        showChosenDomino( deck->Current().at(currentplayer->getKingPlace()) );
    }
}


