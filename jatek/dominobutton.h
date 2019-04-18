#ifndef DOMINOBUTTON_H
#define DOMINOBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "common.h"
#include "color.h"

using namespace common;

class DominoButton: public QPushButton, ColorConverter{
    Q_OBJECT
public:
    int _row;
    DominoButton(int row, QWidget* parent = nullptr){
        _row = row;
    }
    ~DominoButton(){

    }

    void drawCrown(PLAYERCOLOR color);
};

#endif // DOMINOBUTTON_H
