#ifndef DOMINOBUTTON_H
#define DOMINOBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "domino.h"
#include "common.h"
#include "color.h"

using namespace common;

class DominoButton: public QPushButton, ColorConverter{
    Q_OBJECT

public:
    int _row;
    int sideSize;
    PLAYERCOLOR ownerColor;
    Domino d;

    DominoButton(int sideSize, int row, QWidget* parent = nullptr){
        this->sideSize = sideSize;
        _row = row;
        ownerColor = PLAYERCOLOR::_last;

        d = Domino(EMPTY,EMPTY,0,0);
    }
    ~DominoButton(){

    }

    void setDomino(Domino domino);

public slots:
    void paintEvent(QPaintEvent* e);
};

#endif // DOMINOBUTTON_H
