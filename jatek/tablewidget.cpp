#include <QWidget>
#include <QGridLayout>
#include <QPainter>

#include <vector>

#include "tablewidget.h"
#include "widget.h"
#include "common.h"
#include "color.h"

using namespace std;

TableWidget::TableWidget(int _playerIndex, bool& isActive, QWidget *parent, int _tableSize) :
    QWidget(parent),
	ownershipIndicatorHeight(40),
	tableSize(_tableSize),
	playerIndex(_playerIndex),
    _isActive(isActive),
    dominoHighlight(nullptr),
    dominos(static_cast<PlayerWidget*>(parent)->dominos),
    underlined(false)
{
    QGridLayout *layout = new QGridLayout;
	connect(this, 
			SIGNAL(dominoHighlightMoved(int,int,int)), 
			this,
			SLOT(innerDominoHighlightMoved(int,int,int))
	);
    //szin beallitasa:
    switch( PLAYERCOLOR(playerIndex)){
    case RED:{qColor = QColor(255,0,0);break;}
    case GREEN:{qColor = QColor(0,255,0);break;}
    case BLUE:{qColor = QColor(0,0,255);break;}
    case YELLOW:{qColor = QColor(200,200,0);break;}
    default: {}
    }
	int botPadding = 20;
    setLayout(layout);
    setFixedWidth(tableSize);
	setFixedHeight(tableSize + ownershipIndicatorHeight);

    setMouseTracking(true);

}

TableWidget::~TableWidget(){

}

void TableWidget::underline(bool b){
    underlined = b;
}
void TableWidget::innerDominoHighlightMoved(int playerInd, int sor,int oszlop){
	
}

QRect TableWidget::getRect(Domino* d){
	int n = 5;
	int wMult = tableSize / n;
	int hMult = tableSize / n;
	std::pair<Ind2D,Ind2D> sides = d->getSidesCoords();
	int top = sides.first.row < sides.second.row ? sides.first.row : sides.second.row;
	top *= hMult;
	int left = sides.first.col < sides.second.col ? sides.first.col : sides.second.col;
	left *= wMult;
	
	int h = hMult;
	int w = wMult;
	if(d->GetDirection() == UP || d->GetDirection() == DOWN ){
		h *= 2;
	}
	else{
		w *= 2;
	}
	return QRect(left, top, w, h);
}
void TableWidget::paintEvent(QPaintEvent* e){
    QPainter p(this);
    int n = 5;

    int dw = tableSize / n;
    int dh = tableSize / n;



    //elso mezo kozepe
    int x0 = 0;
    int y0 = 0;

    for(auto row = dominos.begin(); row != dominos.end() ; ++row){
        x0 = 0;
        for(auto it = row->begin(); it != row->end() ; ++it){

            QRect r(x0,y0, dw, dh);

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

            x0 += dw;
        }
        y0 += dh;
    }


    //tabla keretét vastagítjuk ha az aktív játékosé:
    if(_isActive){
		int activePlayerHighlightThickness = 12;
		p.setPen( QPen( QBrush( qColor ), activePlayerHighlightThickness ) );
        p.drawRect(0,0, tableSize, tableSize);
    }
    //p.setPen(qColor);
    //p.drawRect(0,0, dw-1, dh-1);
    //ha underline igaz, akkor alahuzassal megjeloljuk hogy a tabla melyik jatekoshoz tartozik
    if(1 || underlined){
		int x0 = 0;
		int thickness = 20;
		int y0 = tableSize;
        QRect r(x0, y0, width() - x0, height() - y0);
        p.fillRect(r, QBrush(qColor));


        p.setPen(QColor(0,0,0,175));
        p.setFont({"Arial", thickness});
		p.drawText(r, Qt::AlignTop, "Ez a te táblád", &r);
        //QRect r2(0,height()-thickness-5, width(), height());
    }
	
	int thickness = 5;
	if(dominoHighlight != nullptr){
		//leteendo domino helyenek korvaonalanak megjelolese a tablan:
		p.setPen( QPen( QBrush( QColor( Qt::red ) ), thickness ) );
		p.drawRect(getRect(dominoHighlight));
	}
}
void TableWidget::mouseMoveEvent(QMouseEvent *event){
    // cout << "mouse_x: " << event->x() << ", y: " << event->y() << endl;
    int tableSpan= 5;
    int row = event->y() / (double)(tableSize/(double)tableSpan);
    int col = event->x() / (double)(tableSize/(double)tableSpan);


    if(row<0 || col < 0 || row >= tableSize || col >= tableSize)
        return ;

	if(_isActive){
		emit dominoHighlightMoved(playerIndex, row, col);
	}

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
