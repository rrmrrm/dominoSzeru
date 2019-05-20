#ifndef TESTER_H
#define TESTER_H
/**/
#include <QObject>
#include <QWidget>
#include <QString>
#include <QApplication>
#include <QtTest>
#include <unistd.h>
#include "color.h"
#include "model.h"
#include "widget.h"

class Tester : public QObject{
    Q_OBJECT
public:
    model* m;
public slots:
    void ConnectConfirmed(){}
    void startServerConfirmed(){}
    void setPlayerNumChangeConfirmed(){}
    void muteOthers(int){}
    void muteAllPlayers(){}
    void notTheFirstTurn(){}
    void showNewDominos(vector<Domino>){}
    void activePlayerUpdated(int){}
    void putKingConfirmed(bool,int,int){}
    void addDominoConfirmed(QVector< QVector<COLOR> >){}
    void rotateDominoConfirmed(int,DIR){}
    void showChosenDomino(Domino){}
    void show_winner(vector<int>){}
    void updatePlayerNum(int){}
private slots:
    void initTestCase() {
        int playerNum =4;

        m = new model();
        connect( m, SIGNAL(ConnectConfirm()), this, SLOT(ConnectConfirmed()) );
        connect( m, SIGNAL(startServerConfirm()), this, SLOT(startServerConfirmed()) );
        connect( m, SIGNAL(setPlayerNumChangeConfirm()), this, SLOT(setPlayerNumChangeConfirmed()) );

        connect( m, SIGNAL(muteOthers(int)), this, SLOT(muteOthers(int)) );
        connect( m, SIGNAL(muteAllPlayers()), this, SLOT(muteAllPlayers()) );

        connect(m, SIGNAL(notTheFirstTurn()), this, SLOT(notTheFirstTurn()) );
        connect(m, SIGNAL(newDominos(vector<Domino>) ), this, SLOT(showNewDominos(vector<Domino>)) );
        connect(m, SIGNAL(updateActivePlayer(int)), this, SLOT(activePlayerUpdated(int)) );
        connect(m, SIGNAL(PutKingConfirm(bool,int,int)), this, SLOT(putKingConfirmed(bool,int,int)) );
        connect(m, SIGNAL(AddDominoConfirm(QVector<QVector<COLOR>>)), this, SLOT(addDominoConfirmed(QVector< QVector<COLOR> >)) );
        connect(m, SIGNAL(rotateDominoConfirm(int,DIR)), this, SLOT(rotateDominoConfirmed(int,DIR)) );


        connect(m, SIGNAL(showChosenDomino(Domino)), this, SLOT(showChosenDomino(Domino)));

        connect(m, SIGNAL(gameOver(vector<int>)), this, SLOT(show_winner(vector<int>)) );
        connect(m, SIGNAL(sendPlayerNum(int)), this, SLOT(updatePlayerNum(int)) );

        m->setPlayernum(playerNum);
        m->startGame();

    }
    void putKingAndTurnOrderTest(){
        //az 0. jatekos a 3.dominot valasztja ki
        const int p0 = m->sorrend[0];
        const int p1= m->sorrend[1];
        const int p2 = m->sorrend[2];
        const int p3 = m->sorrend[3];

        QCOMPARE(m->currentnumber,0);

        m->PutKingAttempt(true,3);
        usleep(1000*100);
        //a 3. dominot valasztotta ki
        QCOMPARE(m->players[p0].king.getPlace(), 3);
        QCOMPARE(m->currentnumber,1);

        //az 1. jatekos is a 3. dominot akarja kivalasztani
        m->PutKingAttempt(true,3);
        //de a 3. dominot mar kivalasztottak, ezert meg mindig az 1. jatekos jon
        QCOMPARE(m->currentnumber,1);
        //aztan kivalasztja az 1. dominot
        m->PutKingAttempt(true,1);
        //es sikerul neki:
        QCOMPARE(m->players[p1].king.getPlace(), 1);
        QCOMPARE(m->currentnumber,2);

        //az 2. jatekos a 0. dominot valasztja ki
        m->PutKingAttempt(true,0);
        QCOMPARE(m->players[p2].king.getPlace(), 0);
        QCOMPARE(m->currentnumber,3);

        //a 3. jatekos a 2. dominot valasztja ki
        m->PutKingAttempt(true,2);
        QCOMPARE(m->players[p3].king.getPlace(), 2);
        QCOMPARE(m->currentnumber,0);

        ///az uj sorrendet elmentem:
        const int q0 = m->sorrend[0];
        const int q1 = m->sorrend[1];
        const int q2 = m->sorrend[2];
        const int q3 = m->sorrend[3];

        //a 2es indexu jatekos jon
        QCOMPARE(q0, p2);
        m->AddDominoAttempt(3,2);
        //sikeresen hozzadta a tablajahoz a dominot:
        Q_ASSERT(m->players[q0].board.getFields()[3][2] != EMPTY);
        Q_ASSERT(m->players[q0].board.getFields()[3][3] != EMPTY);


    }
    void cleanupTestCase() {
        delete m;
    }
};
/**/
#endif // TESTER_H
