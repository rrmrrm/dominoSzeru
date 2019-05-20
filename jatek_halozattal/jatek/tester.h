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
    Widget* w;

private slots:
    void initTestCase() {
        int x = 1;
        char* t[]{"asd"};
        QApplication a(x, t);

        w = new Widget;
        w->show();

        //a.exec();

    }
    void putKingAndTurnOrderTest(){
        //az 0. jatekos a 3.dominot valasztja ki
        int p1 = w->m->sorrend[0];
        int p2 = w->m->sorrend[1];
        int p3 = w->m->sorrend[2];
        int p4 = w->m->sorrend[3];

        QCOMPARE(w->m->currentnumber,0);

        w->m->PutKingAttempt(true,3);
        usleep(1000*100);
        //a 3. dominot valasztotta ki
        QCOMPARE(w->m->players[p1].king.getPlace(), 3);
        QCOMPARE(w->m->currentnumber,1);

        //az 1. jatekos is a 3. dominot akarja kivalasztani
        w->m->PutKingAttempt(true,3);
        //de a 3. dominot mar kivalasztottak, ezert meg mindig az 1. jatekos jon
        QCOMPARE(w->m->currentnumber,1);
        //aztan kivalasztja az 1. dominot
        w->m->PutKingAttempt(true,1);
        //es sikerul neki:
        QCOMPARE(w->m->players[p2].king.getPlace(), 1);
        QCOMPARE(w->m->currentnumber,2);

        //az 2. jatekos a 0. dominot valasztja ki
        w->m->PutKingAttempt(true,0);
        QCOMPARE(w->m->players[p3].king.getPlace(), 0);
        QCOMPARE(w->m->currentnumber,3);

        //a 3. jatekos a 2. dominot valasztja ki
        //w->m->PutKingAttempt(true,2);
        //QCOMPARE(w->m->players[p4].king.getPlace(), 2);
        //QCOMPARE(w->m->currentnumber,0);
    }
    void cleanupTestCase() {

    }
};
/**/
#endif // TESTER_H
