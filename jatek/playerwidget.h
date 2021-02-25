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


    bool isActive;
    vector< vector<COLOR> > dominos;

    explicit PlayerWidget(int playerIndex, int ts, int w, int h, QWidget *parent = nullptr);
    ~PlayerWidget();
};

#endif // PLAYERWIDGET_H
