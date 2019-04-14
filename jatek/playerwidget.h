#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "tablewidget.h"
#include "common.h"
#include <QWidget>
#include <vector>

using namespace std;

namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget{
    Q_OBJECT

    Ui::PlayerWidget *ui;
    TableWidget* table;
    COLOR color;
public:
    vector< vector<QString> > dominos;

    explicit PlayerWidget(COLOR color, int ts, int w, int h, QWidget *parent = nullptr);
    ~PlayerWidget();

};

#endif // PLAYERWIDGET_H
