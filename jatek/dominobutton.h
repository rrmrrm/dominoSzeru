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
    Domino d;

    DominoButton(int sideSize, int row, QWidget* parent = nullptr){
        this->sideSize = sideSize;
        _row = row;
    }
    ~DominoButton(){

    }

    void drawCrown(PLAYERCOLOR color);
    void setDomino(Domino domino);

public slots:
    void paintEvent(QPaintEvent* e);
};

#endif // DOMINOBUTTON_H
