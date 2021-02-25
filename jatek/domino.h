#ifndef DOMINO_H
#define DOMINO_H

#include "common.h"
#include <QPoint>
#include <QRect>
#include <string>
using namespace std;
using namespace common;
///a dominot a bal mezoje korul lehet majd forgatni
class Ind2D{
	Ind2D(){};
public:
	int row;
	int col;
	Ind2D(int _row, int _col):
		row(_row),
		col(_col)
	{}
};

class Domino{
    COLOR color1;
    COLOR color2;
    int crown1;
    int crown2;
    DIR direction;
    int sor;
    int oszlop;
	int owner;
public:
	std::pair<Ind2D, Ind2D> getSidesCoords(){
		switch(direction){
		case UP:	return std::pair<Ind2D, Ind2D>({sor,oszlop},{sor-1,oszlop});
		case DOWN:	return std::pair<Ind2D, Ind2D>({sor,oszlop},{sor+1,oszlop});
		case LEFT:	return std::pair<Ind2D, Ind2D>({sor,oszlop},{sor,oszlop-1});
		case RIGHT:	return std::pair<Ind2D, Ind2D>({sor,oszlop},{sor,oszlop+1});
		}
	}
    Domino(COLOR color_1, COLOR color_2, int crown_1, int crown_2, DIR dir=RIGHT);
    Domino();
    void Rotate( DIR newDir) {direction=newDir;}
    void move(DIR newDIR);
    pair<COLOR, COLOR> GetColors() const {return std::pair<COLOR,COLOR>(color1,color2); }
    pair<int, int> GetPosition() const {return std::pair<int,int>(sor,oszlop); }
    DIR GetDirection() const {return direction;}
    void setOwner(int newOwner){ owner=newOwner;}
    void SetPosition(int sor, int oszlop){
        this->sor = sor;
        this->oszlop = oszlop;
    }
    int getOwner(){return owner;}
};

#endif //DOMINO_H
