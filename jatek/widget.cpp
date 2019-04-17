#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <QString>
#include <algorithm>
#include <QPushButton>
#include <QPainter>
#include <QVector>

#include "model.h"
#include "color.h"

using namespace std;



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    players()
{
    isFirstTurn = true;
    dominoSideSize = 50;
    activePlayer = 0;
    int playerNum =3;
    int playerWidgetWidth = 500;
    int playerWidgetHeight = 500;
    int playerTableSize = 400;

    ui->setupUi(this);
    ui->dominosRow1Layout->setHorizontalSpacing(0);

    setMinimumWidth(playerNum * playerWidgetWidth + 50);
    setMinimumHeight(playerNum * dominoSideSize + playerWidgetHeight+20);

    m = new model();

    for(int i = 0; i<playerNum ; ++i){
        players.push_back(new PlayerWidget(PLAYERCOLOR(i),playerTableSize,playerWidgetWidth, playerWidgetWidth,this));
        ui->playerLayout->addWidget( players[i],1 );
        connect( players[i]->table, SIGNAL(tableClicked(int,int)), m, SLOT(AddDominoAttempt(int,int)) );
    }
    ///domino sort abrazolo gombok hozzadasa:
    for(int i = 0 ; i < playerNum ; ++i ){
        DominoButton* left = new DominoButton(i,this);
        left->setFixedWidth(dominoSideSize);
        left->setFixedHeight(dominoSideSize);
        DominoButton* right = new DominoButton(i,this);
        right->setFixedWidth(dominoSideSize);
        right->setFixedHeight(dominoSideSize);

        dominoRow1.push_back(pair<DominoButton*,DominoButton*>(left,right) );
        ui->dominosRow1Layout->addWidget(left,i,0);
        ui->dominosRow1Layout->addWidget(right,i,1);
        connect(left, SIGNAL(clicked()), this, SLOT(dominoRow1Clicked()) );
        connect(right, SIGNAL(clicked()), this, SLOT(dominoRow1Clicked()) );
    }

    connect(m, SIGNAL(newDominos(vector<Domino>) ), this, SLOT(showNewDominos(vector<Domino>)) );
    connect(m, SIGNAL(updateActivePlayer(int)), this, SLOT(activePlayerUpdated(int)) );
    connect(m, SIGNAL(PutKingConfirm(int,int)), this, SLOT(putKingConfirmed(int,int)) );
    connect(m, SIGNAL(AddDominoConfirm(QVector<QVector<COLOR>>)), this, SLOT(addDominoConfirmed(QVector< QVector<COLOR> >)) );
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
    update();
}
void Widget::activePlayerUpdated(int newPlayer){
    players[activePlayer]->isActive = false;
    activePlayer = newPlayer;
    players[newPlayer]->isActive=true;
    update();
}
void Widget::showNewDominos(vector<Domino> v){
    cout << "Widget::showNewDominos(vector<Domino> v)" << endl;

    for(int i = 0 ; i < dominoRow1.size(); ++ i){
        dominoRow1[i].first->setIcon( colorToPixmap(v[i].GetColors().first) );
        dominoRow1[i].first->setIconSize( QSize(dominoSideSize,dominoSideSize) );
        dominoRow1[i].second->setIcon( colorToPixmap(v[i].GetColors().second) );
        dominoRow1[i].second->setIconSize( QSize(dominoSideSize,dominoSideSize) );
    }
    update();
}

void Widget::putKingConfirmed(int pos, int player){
    switch( PLAYERCOLOR(player) ){
    case RED: {}
    case GREEN: {}
    case BLUE: {}
    case YELLOW: {}
    }
    update();
}



///show domino placed,and
///show next player's domino over his/her table's center?
void Widget::addDominoConfirmed(QVector< QVector<COLOR> > newDominos){
    vector< vector<COLOR> >& dominos = players[activePlayer]->dominos;

    for(int i = 0 ; i < dominos.size(); ++i){
        for(int j = 0 ; j < dominos[i].size(); ++j){
            dominos[i][j] = newDominos[i][j];
        }
    }
    update();
}



///winners contains the winners' indexes in the players array
void Widget::show_winner( vector<int> winners){
    update();

}

