#ifndef DOMINOBUTTON_H
#define DOMINOBUTTON_H

#include <QWidget>
#include <QPushButton>

class DominoButton: public QPushButton{
    Q_OBJECT
public:
    int _row;
    DominoButton(int row, QWidget* parent = nullptr){
        _row = row;
    }
    ~DominoButton(){

    }
};

#endif // DOMINOBUTTON_H
