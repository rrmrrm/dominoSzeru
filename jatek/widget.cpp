#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <QString>
#include <algorithm>
#include <QPushButton>
#include <QPainter>
#include "model.h"
using namespace std;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    players()
{
    int playerNum =3;
    int playerWidgetWidth = 500;
    int playerWidgetHeight = 500;
    int playerTableSize = 400;
    assert(playerTableSize<=playerWidgetHeight &&
           playerTableSize<=playerWidgetWidth);

    ui->setupUi(this);
    setMinimumWidth(playerNum * playerWidgetWidth + 50);
    setMinimumHeight(playerWidgetHeight+100);

    for(int i = 0; i<playerNum ; ++i){
        players.push_back(new PlayerWidget(PLAYERCOLOR(i),playerTableSize,playerWidgetWidth, playerWidgetWidth,this));
        ui->playerLayout->addWidget( players[i],1 );
    }

    m = new model();
    m->setPlayernum(playerNum);
    m->startGame();
    ///domino sort abrazolo gombok hozzadasa:
    for(int i = 0 ; i < playerNum ; ++i ){
        QPushButton* d = new QPushButton(this);
        dominoRow1.push_back(d);
        ui->dominoRowLayout->addWidget(d);
    }


    connect(m, SIGNAL(updateTurnsleft(int)), ui->turnsLeft, SLOT(ui->turnsLeft->display(int)) );
    connect(m, SIGNAL(newDominos(vector<Domino>) ), this, SLOT(showNewDominos(vector<Domino>)) );


}

Widget::~Widget(){
    delete ui;
}


void Widget::showNewDominos(vector<Domino> v){
    int dominoSideSize = 50;
    for(int i = 0 ; i < dominoRow1.size(); ++ i){
        switch(v[i].GetColors().first){
            case MOUNTAIN: {
                QPixmap pm(":/testSprite.png");
                dominoRow1[i]->setIcon(pm);
                dominoRow1[i]->setIconSize( QSize(dominoSideSize,dominoSideSize) );
                break;
            }

        default: {break;}
        }

    }
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

