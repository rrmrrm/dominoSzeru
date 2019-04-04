
#include <QWidget>
#include <QGridLayout>
#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout;

    //layout->addWidget(button1);

    setLayout(layout);

    setMouseTracking(true);

}

TableWidget::~TableWidget(){

}
