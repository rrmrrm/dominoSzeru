
#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <algorithm>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    uint tSize = 5;
    dominos = vector< vector<QString> >(tSize);

    for(int i = 0 ; i < tSize ; ++i){
        vector<QString> v(tSize);
        dominos[i] = v;

        for(auto y = dominos[i].begin(); y != dominos[i].end(); ++y){
            *y = "";
        }
    }

    dominos[tSize/2][tSize/2] = "Kastély";

    ui->setupUi(this);


}

Widget::~Widget()
{
    delete ui;
}

///public slots:
void Widget::setPlayernum(){

}

void Widget::showNewDominos(){

}


void Widget::putKingConfirmed(int pos, int player){

}



///show domino placed,and
///show next player's domino over his/her table's center
void Widget::addDominoConfirmed(Domino& d){

}



///winners contains the winners' indexes in the players array
void Widget::show_winner( vector<int> winners){

}

