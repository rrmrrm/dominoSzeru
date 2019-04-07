#ifndef DOMINO_H
#define DOMINO_H

#include <QString>
#include "common.h"

using namespace std;
using namespace common;
///a dominot a bal mezoje korul lehet majd forgatni

class Domino{
    QString color1;
    QString color2;
    DIR direction;

    int owner;
public:
    void Rotate( DIR);

    pair<QString, QString> GetColors();
    pair<int, int> GetPos();
};

#endif //DOMINO_H
