#ifndef DOMINO_CPP
#define DOMINO_CPP

#include "domino.h"

Domino::Domino(COLOR color_1, COLOR color_2, int crown_1, int crown_2)
{
    color1=color_1;
    color2=color_2;
    crown1=crown_1;
    crown2=crown_2;
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
    if(newDIR==UP && pos1<8)
    {
        pos1++;
    }
    if(newDIR==DOWN && pos1>0)
    {
        pos1--;
    }
    if(newDIR==LEFT && pos2>0)
    {
        pos2--;
    }
    if(newDIR==RIGHT && pos2<8)
    {
        pos2++;
    }
}



#endif
