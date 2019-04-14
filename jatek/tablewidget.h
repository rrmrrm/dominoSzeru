#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>

#include <iostream>
#include <vector>
#include <QString>

#include "Domino.h"
#include "common.h"

using namespace std;

class TableWidget : public QWidget {
    Q_OBJECT

    QColor qColor;
public:
    ///referencia a nezet-beli domino tombre
    const vector< vector<QString> >& dominos;

    explicit TableWidget(QWidget *parent = nullptr, int size = 400, COLOR color=RED);
    ~TableWidget();


public slots:
    void paintEvent(QPaintEvent* e);
    void mouseMoveEvent(QMouseEvent *event);

signals:



};

#endif // TABLEWIDGET_H
