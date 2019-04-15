#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>

#include <iostream>
#include <vector>
#include <QString>

#include "domino.h"
#include "common.h"

using namespace std;

class TableWidget : public QWidget {
    Q_OBJECT

    bool& _isActive;
    QColor qColor;
public:
    ///referencia a nezet-beli domino tombre
    const vector< vector<QString> >& dominos;

    explicit TableWidget(bool& isActive, QWidget *parent = nullptr, int size = 400, PLAYERCOLOR color=RED);
    ~TableWidget();


public slots:
    void paintEvent(QPaintEvent* e);
    void mouseMoveEvent(QMouseEvent *event);

signals:



};

#endif // TABLEWIDGET_H
