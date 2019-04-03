#ifndef DOMINO_H
#define DOMINO_H

#include <string>
#include "common.h"

using namespace std;
using namespace common;
///a dominot a bal mezoje korul lehet majd forgatni

class Domino{
    string color1;
    string color2;
    DIR direction;

    int owner;
public:
    void Rotate( DIR);

    pair<string, string> GetColors();
    pair<int, int> GetPos();
};

#endif //DOMINO_H
