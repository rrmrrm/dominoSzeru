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
    isFirstTurn = true;
    activePlayer = 0;
    int playerNum =3;
    int playerWidgetWidth = 500;
    int playerWidgetHeight = 500;
    int playerTableSize = 400;
    assert(playerTableSize<=playerWidgetHeight &&
           playerTableSize<=playerWidgetWidth);

    ui->setupUi(this);

    setMinimumWidth(playerNum * playerWidgetWidth + 50);
    setMinimumHeight(playerWidgetHeight+100);

    m = new model();

    for(int i = 0; i<playerNum ; ++i){
        players.push_back(new PlayerWidget(PLAYERCOLOR(i),playerTableSize,playerWidgetWidth, playerWidgetWidth,this));
        ui->playerLayout->addWidget( players[i],1 );
        connect( players[i]->table, SIGNAL(tableClicked(int,int)), m, SLOT(AddDominoAttempt(int,int)) );
    }
    ///domino sort abrazolo gombok hozzadasa:
    for(int i = 0 ; i < playerNum ; ++i ){
        DominoButton* left = new DominoButton(i,this);
        DominoButton* right = new DominoButton(i,this);
        dominoRow1.push_back(pair<DominoButton*,DominoButton*>(left,right) );
        ui->dominosRow1Layout->addWidget(left,i,0);
        ui->dominosRow1Layout->addWidget(right,i,1);
        connect(left, SIGNAL(clicked()), this, SLOT(dominoRow1Clicked()) );
        connect(right, SIGNAL(clicked()), this, SLOT(dominoRow1Clicked()) );
    }

    connect(m, SIGNAL(newDominos(vector<Domino>) ), this, SLOT(showNewDominos(vector<Domino>)) );
    connect(m, SIGNAL(updateActivePlayer(int)), this, SLOT(activePlayerUpdated(int)) );
    connect(m, SIGNAL(PutKingConfirm(int,int)), this, SLOT(putKingConfirmed(int,int)) );
    void putKingConfirmed(int pos, int player);

    connect(m, SIGNAL(updateTurnsleft(int)), ui->turnsLeft, SLOT(display(int)) );
    connect(m, SIGNAL(updateDeckSize(int)), ui->deckSize, SLOT(display(int)) );

    m->setPlayernum(playerNum);
    m->startGame();
}

Widget::~Widget(){
    delete ui;
}
void Widget::notTheFirstTurn(){
    isFirstTurn = false;
}
void Widget::dominoRow1Clicked(){
    cout << "dominoRow1Clicked" << endl;
    DominoButton* actual = qobject_cast<DominoButton*>( sender() );
    cout << "index:"<< actual->_row << endl;
    m->PutKingAttempt(actual->_row);
    int row = actual->_row;
}
void Widget::activePlayerUpdated(int newPlayer){
    players[activePlayer]->isActive = false;
    activePlayer = newPlayer;
    players[newPlayer]->isActive=true;
}
void Widget::showNewDominos(vector<Domino> v){
    cout << "Widget::showNewDominos(vector<Domino> v)" << endl;

    int dominoSideSize = 100;
    for(int i = 0 ; i < dominoRow1.size(); ++ i){
        QPixmap pm("resources/testSprite.png");
        //dominoRow1[i].first->setMinimumHeight(200);
        //dominoRow1[i].first->setMinimumWidth(200);
        dominoRow1[i].first->setIcon(pm);
        dominoRow1[i].first->setIconSize( QSize(dominoSideSize,dominoSideSize) );



        switch(v[i].GetColors().first){
            case MOUNTAIN: {
                QPixmap pm(":/testSprite.png");
                dominoRow1[i].first->setIcon(pm);
                dominoRow1[i].first->setIconSize( QSize(dominoSideSize,dominoSideSize) );
                break;
            }

        default: {break;}
        }

        switch(v[i].GetColors().second){
            case MOUNTAIN: {
                QPixmap pm(":/testSprite.png");
                dominoRow1[i].second->setIcon(pm);
                dominoRow1[i].second->setIconSize( QSize(dominoSideSize,dominoSideSize) );
                break;
            }

        default: {break;}
        }

    }
}

void Widget::putKingConfirmed(int pos, int player){
    switch( PLAYERCOLOR(player) ){
    case RED: {}
    case GREEN: {}
    case BLUE: {}
    case YELLOW: {}
    }
}



///show domino placed,and
///show next player's domino over his/her table's center
void Widget::addDominoConfirmed(Domino& d){

}



///winners contains the winners' indexes in the players array
void Widget::show_winner( vector<int> winners){

}

