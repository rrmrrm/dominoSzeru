#ifndef DOMINO_H
#define DOMINO_H

#include <string>
#include "common.h"

using namespace std;
using namespace common;
///a dominot a bal mezoje korul lehet majd forgatni

class Domino{
    COLOR color1;
    COLOR color2;
    int crown1;
    int crown2;
    DIR direction;
    int pos1;
    int pos2;

    int owner;
public:
    Domino(COLOR color_1, COLOR color_2, int crown_1, int crown_2, DIR dir=RIGHT);
    Domino();
    void Rotate( DIR newDir) {direction=newDir;}
    void move(DIR newDIR);
    pair<COLOR, COLOR> GetColors() const {return std::pair<COLOR,COLOR>(color1,color2); }
    pair<int, int> GetPosition() const {return std::pair<int,int>(pos1,pos2); }
    DIR GetDirection() const {return direction;}
    void setOwner(int newOwner){ owner=newOwner;}
    void SetPosition(int pos1, int pos2){
        this->pos1 = pos1;
        this->pos2 = pos2;
    }
    int getOwner(){return owner;}
};

#endif //DOMINO_H