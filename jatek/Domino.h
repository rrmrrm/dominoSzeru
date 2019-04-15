#ifndef DOMINO_H
#define DOMINO_H

#include <string>
#include "common.h"

using namespace std;
using namespace common;
///a dominot a bal mezoje korul lehet majd forgatni

class Domino{
    COLORS color1;
    COLORS color2;
    int crown1;
    int crown2;
    DIR direction;
    int pos1;
    int pos2;

    int owner;
public:
    Domino(COLORS color_1, COLORS color_2, int crown_1, int crown_2);
    Domino();
    void Rotate( DIR newDir) {direction=newDir;}
    void move(DIR newDIR);
    pair<COLORS, COLORS> GetColors() {return std::pair<COLORS,COLORS>(color1,color2); }
    pair<int, int> GetPosition() {return std::pair<int,int>(pos1,pos2); }
    DIR GetDirection() {return direction;}
};

#endif //DOMINO_H
