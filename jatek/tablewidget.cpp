#include <QWidget>
#include <QGridLayout>
#include <QPainter>

#include <vector>

#include "tablewidget.h"
#include "widget.h"
#include "common.h"
using namespace std;

TableWidget::TableWidget(bool& isActive, QWidget *parent, int size, PLAYERCOLOR color) :
    QWidget(parent),
    _isActive(isActive),
    dominos(  static_cast<PlayerWidget*>(parent)->dominos )
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

///public slots:
void TableWidget::paintEvent(QPaintEvent* e){
    QPainter p(this);

    int w = width();
    int h = height();

    int n = 5;

    //elso mezo kozepe
    int x0 = 0;
    int y0 = 0;

    for(auto row = dominos.begin(); row != dominos.end() ; ++row){
        x0 = 0;
        for(auto it = row->begin(); it != row->end() ; ++it){

            QRect r(x0,y0, w, h);

            //mezo letakaritasa:
            p.fillRect(r, QBrush(QColor(255,255,255)));

            //mezok kerete:
            p.setPen(qColor);
            p.drawRect(r);

            //ha tul szeles lenne a szoveg, akkor leszoritjuk a magassagat, hogy beeferjen w/n pixelbe
            int textHeight = h/n;
            ///TODO: ezt a ket sort visszairni:
            //if(it->size() != 0 && h != 0 && w/h/it->size()*1.4 < 1)//kb 1.4 a karakterek magassaganak és szelessegenek az aranya
             //   textHeight = w/n/it->size()*1.4;//ezt a sort majd normalisan meg kell irni...

            //kirajzoljuk a szoveget egy kicsit feljebb tolva, hogy jo helyen jelenjen meg
            int y0CorrectorForText = -textHeight /4 ; // '/4' al talan jo lesz
            QRect rCorrected(x0,y0+y0CorrectorForText, w, h);
            p.setFont({"Arial", textHeight});
            p.drawText(rCorrected, Qt::AlignJustify, *it + "");
            x0 += w / n;
        }
        y0 += h / n;
    }

    //tabla kerete:
    if(_isActive){
        p.setPen(qColor);
        p.drawRect(0,0, w-1, h-1);
        p.drawRect(1,1, w-3, h-3);
        p.drawRect(2,2, w-4, h-4);
        p.drawRect(2,2, w-5, h-5);
        p.drawRect(2,2, w-6, h-6);
        p.drawRect(3,3, w-7, h-7);
        p.drawRect(3,3, w-8, h-8);
    }
    p.setPen(qColor);
    p.drawRect(0,0, w-1, h-1);
}
void TableWidget::mouseMoveEvent(QMouseEvent *event){
    cout << "mouse_x: " << event->x() << ", y: " << event->y() << endl;

}
void TableWidget::mousePressEvent(QMouseEvent *event){
    cout << "mouse_x: " << event->x() << ", y: " << event->y() << endl;

    ///todo: 0,0helyett a jo parameterekkel hivni:
    /// ///todo: hardcoded 5 helyett vmi
    int row = event->y() / (height()/5);
    int col =  event->x() / (width()/5);
    cout<< "emitting tableClicked with row: " << row <<", col: " <<col << endl;
    emit tableClicked(row, col);
}
