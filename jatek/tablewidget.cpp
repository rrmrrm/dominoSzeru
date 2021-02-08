#include <QWidget>
#include <QGridLayout>
#include <QPainter>

#include <vector>

#include "tablewidget.h"
#include "widget.h"
#include "common.h"
#include "color.h"

using namespace std;

TableWidget::TableWidget(bool& isActive, QWidget *parent, int size, PLAYERCOLOR color) :
    QWidget(parent),
    _isActive(isActive),
    dominoHighlight(nullptr),
    dominos(  static_cast<PlayerWidget*>(parent)->dominos ),
    underlined(false)
{
    QGridLayout *layout = new QGridLayout;

    //szin beallitasa:
    switch(color){
    case RED:{qColor = QColor(255,0,0);break;};
    case GREEN:{qColor = QColor(0,255,0);break;};
    case BLUE:{qColor = QColor(0,0,255);break;};
    case YELLOW:{qColor = QColor(200,200,0);break;};
    default: {};
    }

    setLayout(layout);
    setFixedWidth(size);
    setFixedHeight(size);

    setMouseTracking(true);

}

TableWidget::~TableWidget(){

}

void TableWidget::underline(bool b){
    int thickness = 20;
    underlined = b;
    if(b)
        this->setFixedHeight(height()+thickness);

}

///public slots:
void TableWidget::paintEvent(QPaintEvent* e){
    QPainter p(this);
    int n = 5;

    int w = width() / n;
    int h = height() / n;



    //elso mezo kozepe
    int x0 = 0;
    int y0 = 0;

    for(auto row = dominos.begin(); row != dominos.end() ; ++row){
        x0 = 0;
        for(auto it = row->begin(); it != row->end() ; ++it){

            QRect r(x0,y0, w, h);

            //mezo letakaritasa:
            p.fillRect(r, QBrush(QColor(255,255,255)));
            p.drawImage(r, colorToImage(*it));
            //mezok kerete:
            p.setPen(qColor);
            p.drawRect(r);

            //ha tul szeles lenne a szoveg, akkor leszoritjuk a magassagat, hogy beeferjen w/n pixelbe
            //int textHeight = h/n;
            ///TODO: ezt a ket sort visszairni:
            //if(it->size() != 0 && h != 0 && w/h/it->size()*1.4 < 1)//kb 1.4 a karakterek magassaganak és szelessegenek az aranya
             //   textHeight = w/n/it->size()*1.4;//ezt a sort majd normalisan meg kell irni...

            //kirajzoljuk a szoveget egy kicsit feljebb tolva, hogy jo helyen jelenjen meg
            //int y0CorrectorForText = -textHeight /4 ; // '/4' al talan jo lesz
            //QRect rCorrected(x0,y0, w, h);
            //p.setFont({"Arial", textHeight});
            //p.drawText(rCorrected, Qt::AlignJustify, *it + "");

            x0 += w;
        }
        y0 += h;
    }


    //tabla kerete:
    if(_isActive){
        p.setPen(qColor);
        p.drawRect(0,0, width()-1, height()-1);
        p.drawRect(1,1, width()-3, height()-3);
        p.drawRect(2,2, width()-4, height()-4);
        p.drawRect(2,2, width()-5, height()-5);
        p.drawRect(2,2, width()-6, height()-6);
        p.drawRect(3,3, width()-7, height()-7);
        p.drawRect(3,3, width()-8, height()-8);
    }
    p.setPen(qColor);
    p.drawRect(0,0, w-1, h-1);

    //ha underline igaz, akkor alahuzassal megjeloljuk hogy a tabla melyik jatekoshoz tartozik
    if(underlined){
        int thickness = 20;
        QRect r(0,height()-thickness, width(), height());
        p.fillRect(r, QBrush(qColor));


        p.setPen(QColor(0,0,0));
        p.setFont({"Arial", thickness});
        QRect r2(0,height()-thickness-5, width(), height()-5);
        p.drawText(r2, Qt::AlignJustify, "Ez a te táblád");
    }
}
void TableWidget::mouseMoveEvent(QMouseEvent *event){
    // cout << "mouse_x: " << event->x() << ", y: " << event->y() << endl;
    int tableSize= 5;
    int row = event->y() / (height()/tableSize);
    int col =  event->x() / (width()/tableSize);


    if(row<0 || col < 0 || row >= tableSize || col >= tableSize)
        return ;

    if(dominoHighlight == nullptr)
        return;

    dominoHighlight->SetPosition(row, col);

}
void TableWidget::mousePressEvent(QMouseEvent *event){
    ///todo: tableSize-t mashol definialni
    int tableSize= 5;
    cout << "mouse_x: " << event->x() << ", y: " << event->y() << endl;

    int row = event->y() / (height()/tableSize);
    int col =  event->x() / (width()/tableSize);
    //hibas koordinatak eseten nem kuldunk esemenyt:
    if(row<0 || col < 0 || row >= tableSize || col >= tableSize)
        return ;
    cout<< "emitting tableClicked with row: " << row <<", col: " <<col << endl;
    emit tableClicked(row, col);
}
