#ifndef _SMARTPLAYER_H_
#define _SMARTPLAYER_H_

#include <iostream>
#include "CardPile.h"
#include "Player.h"
#include "Card.h"

using namespace std;

class SmartPlayer : public Player {
 public:
  // public members
  SmartPlayer(string name,int ID);
  Card * lead();
  Card * throwOff();
  Card * followSuit(Card::Rank rank, Card::Suit suit);
 private:
  // private members
};


#endif
