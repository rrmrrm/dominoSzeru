#include "playerwidget.h"
#include "ui_playerwidget.h"
#include "tablewidget.h"
#include "common.h"
#include <iostream>

using namespace std;

PlayerWidget::PlayerWidget(PLAYERCOLOR color, int ts, int w, int h, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget),
    table(nullptr)
{
    uint tSize = 5;

    dominos = vector< vector<QString> >(tSize);
    cout << dominos.size() << endl;
    for(int i = 0 ; i < tSize ; ++i){
        vector<QString> v(tSize);
        dominos[i] = v;

        for(auto y = dominos[i].begin(); y != dominos[i].end(); ++y){
            *y = "";
        }
    }

    dominos[tSize/2][tSize/2] = "Kastély";

    table = new TableWidget(this, ts, color);
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(table,1);
    setFixedWidth(w);
    setFixedHeight(h);


}

PlayerWidget::~PlayerWidget()
{

    delete ui;
}
