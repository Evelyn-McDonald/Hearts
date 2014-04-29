#ifndef _RANDOMPLAYER_H_
#define _RANDOMPLAYER_H_

#include <iostream>
#include "CardPile.h"
#include "Player.h"

using namespace std;

class RandomPlayer : public Player {
 public:
  // public members
  RandomPlayer(string name, int ID);
  void setRandomSeed(uint32_t randomSeed);
  Card * lead();
  Card * throwOff();
  Card * followSuit(Card::Rank rank,Card::Suit suit);
 private:
  // private members
  PRNG prng;
};

#endif
