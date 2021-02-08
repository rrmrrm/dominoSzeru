#include "playerwidget.h"
#include "ui_playerwidget.h"
#include "tablewidget.h"
#include "dominobutton.h"
#include "common.h"
#include <iostream>

using namespace std;

PlayerWidget::PlayerWidget(PLAYERCOLOR color, int ts, int w, int h, QWidget *parent) :
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

    table = new TableWidget(isActive, this, ts, color);
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(table,1);
    setFixedWidth(w);
    setFixedHeight(h);


}

PlayerWidget::~PlayerWidget()
{

    delete ui;
}
