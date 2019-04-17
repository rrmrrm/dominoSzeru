#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>

#include <iostream>
#include <vector>
#include <QString>

#include "color.h"
#include "domino.h"
#include "common.h"

using namespace std;

class TableWidget : public QWidget, ColorConverter {
    Q_OBJECT

    bool& _isActive;
    QColor qColor;
public:
    ///referencia a nezet-beli domino tombre
    const vector< vector<COLOR> >& dominos;

    explicit TableWidget(bool& isActive, QWidget *parent = nullptr, int size = 400, PLAYERCOLOR color=RED);
    ~TableWidget();


public slots:
    void paintEvent(QPaintEvent* e);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void tableClicked(int,int);


};

#endif // TABLEWIDGET_H
