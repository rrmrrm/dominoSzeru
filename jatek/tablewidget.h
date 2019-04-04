#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>


#include <iostream>

using namespace std;

class TableWidget : public QWidget {
    Q_OBJECT
///private fields:
private:


///private functions:
    void mouseMoveEvent(QMouseEvent *event){
        cout << "mouse_x: " << event->x() << ", y: " << event->y() << endl;
    }

public:
    explicit TableWidget(QWidget *parent = nullptr);
    ~TableWidget();

};

#endif // TABLEWIDGET_H
