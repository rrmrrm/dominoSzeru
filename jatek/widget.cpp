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
    playerNum =3;
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
        DominoButton* d = new DominoButton(dominoSideSize,i,this);

        dominoRow1.push_back(d);
        ui->dominosRow1Layout->addWidget(d,i,0);
        connect(d, SIGNAL(clicked()), this, SLOT(dominoRow1Clicked()) );
    }
    connect(m, SIGNAL(notTheFirstTurn()), this, SLOT(notTheFirstTurn()) );
    connect(m, SIGNAL(newDominos(vector<Domino>) ), this, SLOT(showNewDominos(vector<Domino>)) );
    connect(m, SIGNAL(updateActivePlayer(int)), this, SLOT(activePlayerUpdated(int)) );
    connect(m, SIGNAL(PutKingConfirm(int,int)), this, SLOT(putKingConfirmed(int,int)) );
    connect(m, SIGNAL(AddDominoConfirm(QVector<QVector<COLOR>>)), this, SLOT(addDominoConfirmed(QVector< QVector<COLOR> >)) );

    connect(m, SIGNAL(updateTurnsleft(int)), ui->turnsLeft, SLOT(display(int)) );
    connect(m, SIGNAL(updateDeckSize(int)), ui->deckSize, SLOT(display(int)) );

    m->setPlayernum(playerNum);
    m->startGame();
}

Widget::~Widget(){
    delete ui;
}

void Widget::addSecondDominoRow(){
    for(int i = 0 ; i < playerNum ; ++i ){
        DominoButton* d = new DominoButton(dominoSideSize,i,this);

        dominoRow2.push_back(d);
        ui->dominosRow2Layout->addWidget(d,i,0);
        connect(d, SIGNAL(clicked()), this, SLOT(dominoRow2Clicked()) );
    }
}

void Widget::notTheFirstTurn(){
    cout << "notTheFirstTurn() " << endl;
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
void Widget::dominoRow2Clicked(){
    cout << "dominoRow2Clicked-nincs rendesen megirva" << endl;
    DominoButton* actual = qobject_cast<DominoButton*>( sender() );
    cout << "index:"<< actual->_row << endl;

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

    cout << "isfirstturn: " << isFirstTurn << endl;
    if(isFirstTurn){
        for(int i = 0 ; i < dominoRow1.size(); ++ i){
            dominoRow1[i]->setDomino(v[i]);
            //dominoRow1[i].first-> setIcon( colorToPixmap(v[i].GetColors().first) );
            //dominoRow1[i].first->setIconSize( QSize(dominoSideSize,dominoSideSize) );
            //dominoRow1[i].second->setIcon( colorToPixmap(v[i].GetColors().second) );
            //dominoRow1[i].second->setIconSize( QSize(dominoSideSize,dominoSideSize) );
        }
    }
    else{
        if(dominoRow2.size() == 0){
            ///a masodik sor domino meg nincs felhelyezve
            addSecondDominoRow();
        }
        else{
            ///a masodik sor domino mar fel van helyezve

            ///atmasolom a masodik domino sor ábráit az elsőbe:
            for(int i = 0 ; i < dominoRow1.size(); ++ i){
                //dominoRow1[i].first->setIcon( dominoRow2[i].first->icon() );
                //dominoRow1[i].second->setIcon( dominoRow2[i].second->icon() );
                dominoRow1[i]->setDomino(dominoRow1[i]->d);
            }
        }

        ///frissitem a masodik dominosor kepeit v alapján
        for(int i = 0 ; i < dominoRow2.size(); ++ i){
            //dominoRow2[i].first->setIcon( colorToPixmap(v[i].GetColors().first) );
            //dominoRow2[i].first->setIconSize( QSize(dominoSideSize,dominoSideSize) );
            //dominoRow2[i].second->setIcon( colorToPixmap(v[i].GetColors().second) );
            //dominoRow2[i].second->setIconSize( QSize(dominoSideSize,dominoSideSize) );
            dominoRow2[i]->setDomino(v[i]);
        }
    }
    update();
}

void Widget::putKingConfirmed(int pos, int player){
    cout << "putKingConfirmed(int pos, int player)" << endl;
    dominoRow1[pos]->drawCrown( PLAYERCOLOR(player) );
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

