
#ifndef _TRICK_H__
#define _TRICK_H__

#include <iostream>
#include "CardPile.h"
#include "Player.h"

using namespace std;

class Player;

class Trick : public CardPile {
 private:
  // private members
  Card* lead;
  Card* trump;
 public:
  // public members
  Trick();
  // Setters
  void setLead(Card* card);
  void setTrump(Card* card);
  Card * getLead();
  Card * getTrump();
  Player * trumpPlayer;
};

#endif // _TRICK_H__

