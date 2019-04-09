#ifndef DECK_H
#define DECK_H
#include "Domino.h"
#include<vector>

using namespace std;

class Deck
{
    vector<Domino> DOMINOES;
    vector<int> order;
    int drawnAmount;
public:
    Deck();
    ~Deck();
    void shuffle();
    Domino draw();
};

#endif // DECK_H
