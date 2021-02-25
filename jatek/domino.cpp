#ifndef DOMINO_CPP
#define DOMINO_CPP

#include "domino.h"
#include "common.h"

Domino::Domino(COLOR color_1, COLOR color_2, int crown_1, int crown_2, DIR dir)
{
    color1=color_1;
    color2=color_2;
    crown1=crown_1;
    crown2=crown_2;
    direction=dir;
    this->sor=0;
    this->oszlop=0;
    this->owner=-1;
}
Domino::Domino()
{
    color1=EMPTY;
    color2=EMPTY;
    crown1=0;
    crown2=0;

}

void Domino::move(DIR newDIR)
{
    if(newDIR==UP && sor<8)
    {
        sor++;
    }
    if(newDIR==DOWN && sor>0)
    {
        sor--;
    }
    if(newDIR==LEFT && oszlop>0)
    {
        oszlop--;
    }
    if(newDIR==RIGHT && oszlop<8)
    {
        oszlop++;
    }
}



#endif
