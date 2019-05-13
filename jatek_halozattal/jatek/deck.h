#ifndef DECK_H
#define DECK_H

#include "domino.h"
#include<vector>
#include "board.h"

using namespace std;

class Deck
{
    vector<Domino> current;
    vector<Domino> newOnes;
    vector<int> order;
    int cardsDrawn;
    int deckSize;
public:
    vector<Domino> dominoes;
    vector<bool> taken;
    Deck(int playerNumber);
    Deck();
    ~Deck();
    void shuffle();
    void draw();
    int cardsLeftNum();
    vector<Domino> getCurrent() {return current;}

    ///setter szerűség.
    ///a rotateDominoAttempt-ben van erre szükség
    vector<Domino>& Current() {return current;}

    vector<Domino> getNewOnes() {return newOnes;}

};

#endif // DECK_H
