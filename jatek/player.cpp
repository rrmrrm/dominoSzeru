#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.h"
#include "deck.h"

Player::Player()
{

}

void Player::placeKing(int place)
{
    king.move(place);

}

void Player::placeDomino(Deck * deck = new Deck)
{
    board.placeDomino(deck->getCurrent().at(king.getPlace()), std::pair<int,int>(0,0));
}

#endif
