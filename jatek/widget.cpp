#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <algorithm>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    players()
{
    playerNum =3;
    int playerWidgetWidth = 500;
    int playerWidgetHeight = 500;
    int playerTableSize = 400;
    assert(playerTableSize<=playerWidgetHeight &&
           playerTableSize<=playerWidgetWidth);

    ui->setupUi(this);
    setMinimumWidth(playerNum * playerWidgetWidth + 50);
    setMinimumHeight(playerWidgetHeight+100);

    for(int i = 0; i<playerNum ; ++i){
        players.push_back(new PlayerWidget(COLOR(i),playerTableSize,playerWidgetWidth, playerWidgetWidth,this));
        ui->playerLayout->addWidget( players[i],1 );
    }
}

Widget::~Widget()
{
    for(int i = 0; i<playerNum ; ++i){
        delete players[i];
    }
    delete ui;
}

///public slots:
void Widget::setPlayernum(){

}

void Widget::showNewDominos(){

}


void Widget::putKingConfirmed(int pos, int player){

}



///show domino placed,and
///show next player's domino over his/her table's center
void Widget::addDominoConfirmed(Domino& d){

}



///winners contains the winners' indexes in the players array
void Widget::show_winner( vector<int> winners){

}

