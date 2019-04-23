
#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QRect>
#include <QSize>

#include <iostream>

#include "domino.h"
#include "dominobutton.h"
#include "common.h"
#include "color.h"

using namespace common;
using namespace std;
void DominoButton::drawCrown(PLAYERCOLOR color){
    cout << "DominoButton::drawCrown, color: " << color << endl;
    QPixmap background =icon().pixmap(QSize(width(),height() )  );
    QPainter p(&background);
    QPixmap crown = playerColorToPixmap(color);

    QRect rect(0,0, width(), height());
    p.drawImage(rect, crown.toImage());
    setIcon(background);
    //ico.addPixmap(crown);
    //setIcon(ico);
    //setIcon(crown);
}

void DominoButton::setDomino(Domino domino){
    this->d = domino;
}

void DominoButton::paintEvent(QPaintEvent* e){
    QPainter p(this);

    ///a domino 2 oldala:
    const QPixmap& ico1 = colorToPixmap(d.GetColors().first);
    const QPixmap& ico2 = colorToPixmap(d.GetColors().second);

    ///allitjuk vagy elfektetjuk a domniot
    switch(d.GetDirection()){
    case UP:
    case DOWN:{setFixedWidth(sideSize);setFixedHeight(2*sideSize);break;}
    case LEFT:
    case RIGHT:{setFixedWidth(2*sideSize);setFixedHeight(sideSize);break;}
    };

    QRect r(0,0, width(), height());
    p.fillRect(r, QBrush(QColor(0,255,255)));

    ///a domino képeit megjelenitjuk az iranya(GetDirection()) szerint
    switch(d.GetDirection()){
    case UP:{
        p.drawPixmap(0,0,sideSize,sideSize,ico2);
        p.drawPixmap(0,sideSize,sideSize,sideSize,ico1);
        break;}
    case DOWN:{
        p.drawPixmap(0,0,sideSize,sideSize,ico1);
        p.drawPixmap(0,sideSize,sideSize,sideSize,ico2);
        break;}
    case LEFT:{
        p.drawPixmap(0,0,sideSize,sideSize,ico2);
        p.drawPixmap(sideSize,0,sideSize,sideSize,ico1);
        break;}
    case RIGHT:{
        p.drawPixmap(0,0,sideSize,sideSize,ico1);
        p.drawPixmap(sideSize,0,sideSize,sideSize,ico2);
        break;}
    };

    ///ha az egyik jatekos birtokolja, akkor a megfelelo szinu jatekos-koronat is felrajzoljuk
    if(ownerColor < PLAYERCOLOR::_last){
        QPixmap crown = playerColorToPixmap(ownerColor);
        p.drawPixmap(sideSize/3,sideSize/3,sideSize*2/3,sideSize*2/3,crown);
    }
}
