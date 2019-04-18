
#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QRect>
#include <QSize>

#include <iostream>

#include "dominobutton.h"
#include "common.h"

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
