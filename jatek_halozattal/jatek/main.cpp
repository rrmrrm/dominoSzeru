//#define TEST
#include "common.h"
#include "domino.h"

#include "widget.h"
#include <QApplication>
//#include <QtTest>
#ifdef TEST

#include "tester.h"
QTEST_APPLESS_MAIN(Tester);

#else
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
#endif

