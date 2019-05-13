#ifndef TESTER_H
#define TESTER_H

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
    Widget* w;

private slots:
    void initTestCase() {
        int x;
        char* t[1];
        QApplication a(x, t);

        w = new Widget;

    }
    void test1(){
        QCOMPARE(1,0);
    }
    void cleanupTestCase() {

    }
};

#endif // TESTER_H
