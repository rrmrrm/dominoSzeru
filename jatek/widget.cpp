
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
    ui->setupUi(this);
    ui->dominosRow1Layout->setHorizontalSpacing(0);

    dominoSideSize = 30;

    playerNum = 4;

    m = new model();
    connect( m, SIGNAL(ConnectConfirm()), this, SLOT(ConnectConfirmed()) );
    connect( m, SIGNAL(startServerConfirm()), this, SLOT(startServerConfirmed()) );
    connect( m, SIGNAL(setPlayerNumChangeConfirm()), this, SLOT(setPlayerNumChangeConfirmed()) );

    connect( m, SIGNAL(muteOthers(int)), this, SLOT(muteOthers(int)) );
    connect( m, SIGNAL(muteAllPlayers()), this, SLOT(muteAllPlayers()) );
    initialize(playerNum);

}
void Widget::initialize(int playerNum){
    isFirstTurn = true;
    int playerWidgetHeight = 300;
    int playerTableSize = 160;

    activePlayer = 0;
    int playerWidgetWidth = playerTableSize + 2*dominoSideSize;
    setMinimumWidth(playerNum * (playerWidgetWidth) + 50);
    setMinimumHeight(playerNum * dominoSideSize + playerWidgetHeight+20);

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
    connect(m, SIGNAL(sendPlayerNum(int)), this, SLOT(updatePlayerNum(int)) );

    connect(m, SIGNAL(indicatePlayer(int)), this, SLOT(indicatePlayer(int)) );
    connect(m, SIGNAL(yourTurn()), this, SLOT(yourTurn()));
    connect(m, SIGNAL(error()), this, SLOT(error()));
    m->setPlayernum(playerNum);
    m->startGame();
}
Widget::~Widget(){
    delete ui;
}

void Widget::addSecondDominoRow(){

    for(int i = 0 ; i < dominoRow1.size() ; ++i){
        dominoRow1[i]->setEnabled(false);
    }

    for(int i = 0 ; i < playerNum ; ++i ){
        DominoButton* d = new DominoButton(dominoSideSize,i/*,this*/);
        dominoRow2.push_back(d);
        ui->dominosRow2Layout->addWidget(d,i,0);
        connect(d, SIGNAL(clicked()), this, SLOT(dominoRow2Clicked()) );
    }
}
void Widget::removeSecondDominoRow(){
    for(int i = 0 ; i < dominoRow2.size(); ++i ){
        disconnect(dominoRow2[i], SIGNAL(clicked()), this, SLOT(dominoRow2Clicked()) );
        ui->dominosRow2Layout->removeWidget(dominoRow2[i]);
        delete dominoRow2[i];

    }
    dominoRow2.resize(0);
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
    //ekkor csak kiralyokat helyezhetik le
    if(isFirstTurn)
        return;
    cout << "DEaktivalva: " << activePlayer << endl;
    players[activePlayer]->setEnabled(false);

    players[activePlayer]->isActive = false;
    activePlayer = newPlayer;
    players[newPlayer]->isActive=true;

    cout << "aktivalva: " << newPlayer << endl;
    players[newPlayer]->setEnabled(true);
    players[newPlayer]->dominoButton->update();
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

    cout << "putKingConfirmed(" << pos << ", "<<  player<< ")" << endl;
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
    ui->startServerButton->setEnabled(false);
    ui->setPlayerNumButton->setEnabled(false);
}
void Widget::startServerConfirmed(){
    ui->startServerButton->setEnabled(false);
    ui->setPlayerNumButton->setEnabled(false);
    ui->connectButton->setEnabled(false);
}
void Widget::setPlayerNumChangeConfirmed(){
    //ui->setPlayerNumButton->setEnabled(false);
}

void Widget::updatePlayerNum(int n){
    clear();
    playerNum = n;
    initialize(n);
}


void Widget::clear(){

    removeSecondDominoRow();

    disconnect(m, SIGNAL(sendPlayerNum(int)), this, SLOT(updatePlayerNum(int)) );
    disconnect(ui->setPlayerNumButton, SIGNAL(clicked()), this, SLOT(setPlayerNumButtonClicked()));
    disconnect(ui->startServerButton, SIGNAL(clicked()), this, SLOT(startServerButtonClicked()));
    disconnect(ui->connectButton, SIGNAL(clicked()), this, SLOT(ConnectButtonClicked()));
    disconnect(m, SIGNAL(gameOver(vector<int>)), this, SLOT(show_winner(vector<int>)) );
    disconnect(m, SIGNAL(showChosenDomino(Domino)), this, SLOT(showChosenDomino(Domino)));
    disconnect(m, SIGNAL(updateDeckSize(int)), ui->deckSize, SLOT(display(int)) );
    disconnect(m, SIGNAL(updateTurnsleft(int)), ui->turnsLeft, SLOT(display(int)) );
    disconnect(m, SIGNAL(rotateDominoConfirm(int,DIR)), this, SLOT(rotateDominoConfirmed(int,DIR)) );
    disconnect(m, SIGNAL(AddDominoConfirm(QVector<QVector<COLOR>>)), this, SLOT(addDominoConfirmed(QVector< QVector<COLOR> >)) );
    disconnect(m, SIGNAL(updateActivePlayer(int)), this, SLOT(activePlayerUpdated(int)) );
    disconnect(m, SIGNAL(PutKingConfirm(bool,int,int)), this, SLOT(putKingConfirmed(bool,int,int)) );
    disconnect(m, SIGNAL(newDominos(vector<Domino>) ), this, SLOT(showNewDominos(vector<Domino>)) );
    disconnect(m, SIGNAL(notTheFirstTurn()), this, SLOT(notTheFirstTurn()) );

    for(int i = 0 ; i < dominoRow1.size() ; ++i ){
        disconnect(dominoRow1[i], SIGNAL(clicked()), this, SLOT(dominoRow1Clicked()) );
        ui->dominosRow1Layout->removeWidget(dominoRow1[i]);
        delete dominoRow1[i];
    }

    for(int i = 0; i<players.size() ; ++i){
        disconnect( players[i]->dominoButton, SIGNAL(clicked()), this, SLOT(playerDominoClicked()) );
        players[i]->ui->horizontalLayout->removeWidget(players[i]->dominoButton);
        delete players[i]->dominoButton;
        disconnect( players[i]->table, SIGNAL(tableClicked(int,int)), m, SLOT(AddDominoAttempt(int,int)) );
        ui->playerLayout->removeWidget( players[i] );
        delete players[i];
    }

    dominoRow1.resize(0);
    players.resize(0);
}

void Widget::muteOthers(int unMuted){
    cout << "Widget::muteOthers( " << unMuted << ")" << endl;
    /*
    for(int i = 0 ; i < players.size() ; ++i){
        if(isFirstTurn){
            players[i]->dominoButton->setEnabled(false);
        }
        else if( i == unMuted){
            players[i]->dominoButton->setEnabled(false);
        }
    }
*/
    for(int i = 0 ; i < dominoRow1.size() ; ++i){
        if(isFirstTurn){
            dominoRow1[i]->setEnabled(true);
        }
        else
            dominoRow1[i]->setEnabled(false);
    }
    for(int i = 0 ; i < dominoRow2.size() ; ++i){
        dominoRow2[i]->setEnabled(true);
    }

    for(int i = 0 ; i < playerNum ; ++i ){
        if(isFirstTurn || i != unMuted){
            players[i]->setEnabled(false);
        }
        else{
            players[i]->setEnabled(true);
        }
    }
}
void Widget::muteAllPlayers(){
    cout << "Widget::muteAllPlayers" << endl;
    ui->yourTurnLabel->setFont({"Arial", 10});
    ui->yourTurnLabel->setText("");

    for(int i = 0 ; i < dominoRow1.size() ; ++i){
        dominoRow1[i]->setEnabled(false);
    }
    for(int i = 0 ; i < dominoRow2.size() ; ++i){
        dominoRow2[i]->setEnabled(false);
    }

    for(int i = 0 ; i < playerNum ; ++i ){
        players[i]->setEnabled(false);
    }
}

///a megadott jatekosWidgetet kiszinezi, hogy a jatekos tudja, hogy melyik az o tablaja
void Widget::indicatePlayer(int player){
    for(int i = 0 ; i < playerNum ; ++i){
        if(i == player)
            players[i]->table->underline(true);
        else
            players[i]->table->underline(false);
    }
}

///a jatekablak korvonalat fogja kiszinezni ilyen szinure, hogy a jatekos tudja, hogy mi a szine
void Widget::yourTurn(){
    cout << "Widget::yourTurn" << endl;
    ui->yourTurnLabel->setAlignment(Qt::AlignCenter);

    ui->yourTurnLabel->setFont({"Arial", 20});
    ui->yourTurnLabel->setText("Te Jössz!");
}

void Widget::error(){
    ui->connectButton->setEnabled(true);
    ui->startServerButton->setEnabled(true);
    ui->setPlayerNumButton->setEnabled(true);

    qmb.information(
        this,
    "rossz módban próbált csatlakozni! (váltson játékosszámot)",
    "");


}
