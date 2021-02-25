#include "playerwidget.h"
#include "ui_playerwidget.h"
#include "tablewidget.h"
#include "dominobutton.h"
#include "common.h"
#include <iostream>

using namespace std;

PlayerWidget::PlayerWidget(int playerIndex, int ts, int w, int h, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget),
    table(nullptr)
{
    uint tSize = 5;
    isActive = false;
    dominos = vector< vector<COLOR> >(tSize);

    for(int i = 0 ; i < tSize ; ++i){
        vector<COLOR> v(tSize);
        dominos[i] = v;

        for(auto y = dominos[i].begin(); y != dominos[i].end(); ++y){
            *y = EMPTY;
        }
    }

    dominos[tSize/2][tSize/2] = CASTLE;

    table = new TableWidget(playerIndex, isActive, this, ts);
	connect(table, SIGNAL(dominoHighlightMoved(int,int,int)), this, SLOT(dominoHighlightMoved(int,int,int)));
	
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(table,1);
    setFixedWidth(w);
    setFixedHeight(h);


}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void PlayerWidget::dominoHighlightMoved(int playerIndNotUsedHere, int sor,int oszlop){
	dominoButton->d.SetPosition(sor, oszlop);
	table->dominoHighlight = &dominoButton->d;
	table->repaint();
}
