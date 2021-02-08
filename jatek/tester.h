#ifndef TESTER_H
#define TESTER_H
/**/
#include <QObject>
#include <QWidget>
#include <QString>
#include <QApplication>
#include <QtTest>
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
    void putKing_TurnOrder_AddDomino_RotateDomino_Test(){
        //az 0. jatekos a 3.dominot valasztja ki
        const int p0 = m->sorrend[0];
        const int p1= m->sorrend[1];
        const int p2 = m->sorrend[2];
        const int p3 = m->sorrend[3];

        QCOMPARE(m->currentnumber,0);

        m->PutKingAttempt(true,3);
        //a 0. jatekos a 3. dominot valasztotta ki
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

        //a 2es jatekos jon
        QCOMPARE(q0, p2);
        //felulirom a leteendo dominot, hogy determinisztikus legyen a teszteles:
        m->deck->Current().at(m->currentplayer->king.getPlace()) = Domino(WHEATFIELD,WHEATFIELD,0,0,RIGHT);

        //elforgatjuk lefele iranyba a dominot, es ellenorizzuk az eredmenyt:
        m->rotateDominoAttempt(q0, DOWN);
        QCOMPARE(m->deck->Current().at(m->currentplayer->king.getPlace()).GetDirection(), DOWN);

        //domino letevese
        m->AddDominoAttempt(3,2);

        //sikeresen hozzadta a tablajahoz a dominot:
        QCOMPARE(m->players[q0].board.getFields()[3][2], WHEATFIELD);
        QCOMPARE(m->players[q0].board.getFields()[4][2], WHEATFIELD);
        //attesszuk a kiralyt
        m->PutKingAttempt(false, m->currentplayer->king.getPlace());

        //a tobbiek dominojat es kirajat is letesszuk

        //az 1es jatekos jon, mert o kivalasztotta elobb az 1. dominot
        QCOMPARE(q1, p1);
        m->AddDominoAttempt(3,2);
        m->PutKingAttempt(false, m->currentplayer->king.getPlace());

        //a 3as jatekos jon, mert o kivalasztotta elobb a 2. dominot
        QCOMPARE(q2, p3);
        m->AddDominoAttempt(3,2);
        m->PutKingAttempt(false, m->currentplayer->king.getPlace());

        //az 0as jatekos jon, mert o valasztotta ki elobb a 3. dominot
        QCOMPARE(q3, p0);
        m->AddDominoAttempt(3,2);
        m->PutKingAttempt(false, m->currentplayer->king.getPlace());


        //most ujra vizsgaljuk  2es jatekos domino lehelyezeset

        //felulirom a leteendo dominot, hogy determinisztikus legyen a teszteles:
        m->deck->Current().at(m->currentplayer->king.getPlace()) = Domino(FOREST,WHEATFIELD,0,0,RIGHT);

        // a dominot az elozo domino melle probaljuk tenni
        m->AddDominoAttempt(3,3);

        //nem illeszkedett a domino a tablahoz:
        QCOMPARE(m->players[q0].board.getFields()[3][3], EMPTY);
        QCOMPARE(m->players[q0].board.getFields()[3][4], EMPTY);

        //, ezert elforgatjuk a dominot es ugy tesszuk a masik melle:
        m->rotateDominoAttempt(q0, LEFT);
        m->AddDominoAttempt(3,4);

        //most mar sikerult lerakni a dominot:
        QCOMPARE(m->players[q0].board.getFields()[3][3], WHEATFIELD);
        QCOMPARE(m->players[q0].board.getFields()[3][4], FOREST);

        //attesszuk a kiralyt es vege a tesztnek.
        m->PutKingAttempt(false, m->currentplayer->king.getPlace());
    }
    void cleanupTestCase() {
        delete m;
    }
};
/**/
#endif // TESTER_H
