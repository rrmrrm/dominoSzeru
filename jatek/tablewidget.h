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

using namespace std;


class TableWidget : public QWidget {
    Q_OBJECT


public:
    ///referencia a nezet-beli domino tombre
    const vector< vector<QString> >& dominos;

    explicit TableWidget(QWidget *parent = nullptr);
    ~TableWidget();
public slots:
    void paintEvent(QPaintEvent* e);
    void mouseMoveEvent(QMouseEvent *event);

signals:



};

#endif // TABLEWIDGET_H
