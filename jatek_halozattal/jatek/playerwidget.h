#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "tablewidget.h"
#include "dominobutton.h"
#include "common.h"
#include <QWidget>
#include <vector>

using namespace std;

namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget{
    Q_OBJECT

public:
    Ui::PlayerWidget *ui;
    TableWidget* table;
    DominoButton* dominoButton;
    PLAYERCOLOR color;


    bool isActive;
    vector< vector<COLOR> > dominos;

    explicit PlayerWidget(PLAYERCOLOR color, int ts, int w, int h, QWidget *parent = nullptr);
    ~PlayerWidget();


};

#endif // PLAYERWIDGET_H