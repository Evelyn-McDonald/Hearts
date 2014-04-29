#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include <iostream>
#include "CardPile.h"
#include "Player.h"
#include "Card.h"

using namespace std;

class HumanPlayer : public Player {
 public:
  // public members
  HumanPlayer(string name, int ID);
  Card * lead();
  Card * throwOff();
  Card * followSuit(Card::Rank rank, Card::Suit suit);
 private:
  // private members
};

#endif
