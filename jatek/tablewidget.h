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
	int ownershipIndicatorHeight;
	int tableSize;
	const int playerIndex;
    bool& _isActive;
    QColor qColor;

public:
    ///referencia a nezet-beli domino tombre
    Domino* dominoHighlight;
    const vector< vector<COLOR> >& dominos;
    bool underlined;

    explicit TableWidget(int _playerIndex, bool& isActive, QWidget *parent = nullptr, int _tableSize = 400);

    ~TableWidget();
	void underline(bool);
	QRect getRect(Domino* d);
private slots:
	void innerDominoHighlightMoved(int playerIndUnusedHere, int sor, int oszlop);
public slots:
    void paintEvent(QPaintEvent* e);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void tableClicked(int,int);
	void dominoHighlightMoved(int playerInd, int row, int col);
};

#endif // TABLEWIDGET_H
