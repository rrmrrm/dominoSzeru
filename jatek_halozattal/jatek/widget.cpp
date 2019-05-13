
#include "ui_playerwidget.h"
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
    qmb(this),
    players()
{
    isFirstTurn = true;
    dominoSideSize = 50;

    activePlayer = 0;
    playerNum =4;
    int playerWidgetHeight = 500;
    int playerTableSize = 280;

    int playerWidgetWidth = playerTableSize + 2*dominoSideSize;

    ui->setupUi(this);
    ui->dominosRow1Layout->setHorizontalSpacing(0);

    setMinimumWidth(playerNum * (playerWidgetWidth) + 50);
    setMinimumHeight(playerNum * dominoSideSize + playerWidgetHeight+20);

    m = new model();

    for(int i = 0; i<playerNum ; ++i){
        players.push_back(new PlayerWidget(PLAYERCOLOR(i),playerTableSize,playerWidgetWidth, playerWidgetWidth,this));
        ui->playerLayout->addWidget( players[i],1 );
        connect( players[i]->table, SIGNAL(tableClicked(int,int)), m, SLOT(AddDominoAttempt(int,int)) );

        ///hozzáadom a jatekosok kivalasztott dominojat abrazolo DominoButton-t
        ///the second parameter of the constructor represent the owning player.
        players[i]->dominoButton = new DominoButton(dominoSideSize, i, this);
        players[i]->ui->horizontalLayout->addWidget(players[i]->dominoButton);
        connect( players[i]->dominoButton, SIGNAL(clicked()), this, SLOT(playerDominoClicked()) );
        players[i]->setEnabled(false);

    }

    for(int i = 0 ; i < playerNum ; ++i ){

        ///domino sort abrazolo gombok hozzadasa:
        DominoButton* d = new DominoButton(dominoSideSize,i,this);

        dominoRow1.push_back(d);
        ui->dominosRow1Layout->addWidget(d,i,0);
        connect(d, SIGNAL(clicked()), this, SLOT(dominoRow1Clicked()) );
    }
    connect(m, SIGNAL(notTheFirstTurn()), this, SLOT(notTheFirstTurn()) );
    connect(m, SIGNAL(newDominos(vector<Domino>) ), this, SLOT(showNewDominos(vector<Domino>)) );
    connect(m, SIGNAL(updateActivePlayer(int)), this, SLOT(activePlayerUpdated(int)) );
    connect(m, SIGNAL(PutKingConfirm(bool,int,int)), this, SLOT(putKingConfirmed(bool,int,int)) );
    connect(m, SIGNAL(AddDominoConfirm(QVector<QVector<COLOR>>)), this, SLOT(addDominoConfirmed(QVector< QVector<COLOR> >)) );
    connect(m, SIGNAL(rotateDominoConfirm(int,DIR)), this, SLOT(rotateDominoConfirmed(int,DIR)) );

    connect(m, SIGNAL(updateTurnsleft(int)), ui->turnsLeft, SLOT(display(int)) );
    connect(m, SIGNAL(updateDeckSize(int)), ui->deckSize, SLOT(display(int)) );

    connect(m, SIGNAL(showChosenDomino(Domino)), this, SLOT(showChosenDomino(Domino)));

    connect(m, SIGNAL(gameOver(vector<int>)), this, SLOT(show_winner(vector<int>)) );
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(ConnectButtonClicked()));
    connect(ui->startServerButton, SIGNAL(clicked()), this, SLOT(startServerButtonClicked()));
    connect(ui->setPlayerNumButton, SIGNAL(clicked()), this, SLOT(setPlayerNumButtonClicked()));
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
    m->PutKingAttempt(true,actual->_row);
    int row = actual->_row;
    update();
}
void Widget::dominoRow2Clicked(){
    cout << "dominoRow2Clicked-nincs rendesen megirva" << endl;
    DominoButton* actual = qobject_cast<DominoButton*>( sender() );
    cout << "index:"<< actual->_row << endl;
    m->PutKingAttempt(false, actual->_row);
    int row = actual->_row;
    update();
}
void Widget::activePlayerUpdated(int newPlayer){
    cout << "DEaktivalva: " << activePlayer << endl;
    players[activePlayer]->setEnabled(false);

    players[activePlayer]->isActive = false;
    activePlayer = newPlayer;
    players[newPlayer]->isActive=true;

    cout << "aktivalva: " << newPlayer << endl;
    players[newPlayer]->setEnabled(true);
    update();
}
void Widget::showNewDominos(vector<Domino> v){
    cout << "Widget::showNewDominos(vector<Domino> v)" << endl;

    cout << "isfirstturn: " << isFirstTurn << endl;
    if(isFirstTurn){
        for(int i = 0 ; i < dominoRow1.size(); ++ i){
            dominoRow1[i]->setDomino(v[i]);
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
                dominoRow1[i]->setDomino(dominoRow2[i]->d);
            }
        }

        ///frissitem a masodik dominosor kepeit v alapján
        for(int i = 0 ; i < dominoRow2.size(); ++ i){
            dominoRow2[i]->setDomino(v[i]);
        }
    }
    update();
}

void Widget::putKingConfirmed(bool firstDominoRow, int pos, int player){

    cout << "putKingConfirmed(int pos, int player)" << endl;
    if(pos!=-1)
    {
        if(firstDominoRow)
            dominoRow1[pos]->d.setOwner(player);
        else
            dominoRow2[pos]->d.setOwner(player);
        update();

    }
}

void Widget::rotateDominoConfirmed(int player, DIR newDir){
    cout << "rotateDominoConfirmed" << endl;
    players[player]->dominoButton->d.Rotate(newDir);
     players[player]->dominoButton->update();
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
    players[activePlayer]->setEnabled(false);
}



///winners contains the winners' indexes in the players array
void Widget::show_winner( vector<int> winners){
    QString winnersStr("");
    for(int i = 0 ; i < winners.size(); ++i){
        winnersStr += (" ");
        winnersStr += QString::number(winners[i]+1);
    }
    qmb.information(
        this,
        tr("játék vége, nyertesek:"),
        winnersStr) ;

    ui->connectButton->setEnabled(true);
    ui->startServerButton->setEnabled(true);
    ui->setPlayerNumButton->setEnabled(true);

    update();

}

void Widget::playerDominoClicked(){
    DominoButton* source = static_cast<DominoButton*>(sender());
    DIR currentDir = source->d.GetDirection();

    ///newDir lesz a currentDir 1el jobbra forgatottja
    DIR newDir = UP;
    switch (currentDir) {
    case LEFT: {newDir=UP;break;}
    case UP: {newDir=RIGHT;break;}
    case RIGHT: {newDir=DOWN;break;}
    case DOWN: {newDir=LEFT;break;}
    }
    m->rotateDominoAttempt(source->_row, newDir);

}

void Widget::showChosenDomino(Domino d){
    players[activePlayer]->dominoButton->setDomino(d);
}

void Widget::ConnectButtonClicked(){
    m->connect();
}
void Widget::startServerButtonClicked(){
    m->startServer();
}
void Widget::setPlayerNumButtonClicked(){
    m->playerNumChanged();
}

void Widget::ConnectConfirmed(){
    ui->connectButton->setEnabled(false);
}
void Widget::startServerConfirmed(){
    ui->startServerButton->setEnabled(true);
}
void Widget::setPlayerNumChangeConfirmed(){
    ui->setPlayerNumButton->setEnabled(true);
}
