#include <QWidget>
#include <QGridLayout>
#include <QPainter>

#include "tablewidget.h"
#include "widget.h"

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    dominos(  static_cast<Widget*>(parent)->dominos )
{
    QGridLayout *layout = new QGridLayout;

    //layout->addWidget(button1);

    setLayout(layout);

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
    int y0 = 0  ;



    for(auto row = dominos.begin(); row != dominos.end() ; ++row){
        x0 = 0;
        for(auto it = row->begin(); it != row->end() ; ++it){

            QRect r(x0,y0, w, h);



            //mezo letakaritasa:
            p.fillRect(r, QBrush(QColor(255,255,255)));
            p.setPen({128, 0, 0, 255});

            //mezok kerete:
            p.setPen({0, 0, 0, 255});
            p.drawRect(r);

            //ha tul szeles lenne a szoveg, akkor leszoritjuk a magassagat, hogy beeferjen w/n pixelbe
            int textHeight = h/n;
            if(it->size() != 0 && h != 0 && w/h/it->size()*1.4 < 1)//kb 1.4 a karakterek magassaganak és szelessegenek az aranya
                textHeight = w/n/it->size()*1.4;//ezt a sort majd normalisan meg kell irni...

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
    p.setPen({0, 0, 0, 255});
    p.drawRect(0,0, w-1, h-1);
}
void TableWidget::mouseMoveEvent(QMouseEvent *event){
    cout << "mouse_x: " << event->x() << ", y: " << event->y() << endl;
}
