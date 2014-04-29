#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include "CardPile.h"
#include "Trick.h"
#include "Card.h"

using namespace std;

class Trick;

class Player {
 public:
  virtual void setRandomSeed(uint32_t seed);
  Player(string name,int ID);
  string getName();
  int getID();
  int getScore();
  void setScore(int score);
  CardPile hand;
  CardPile tricklist;
  void playCard(Trick& trick);
  bool haveSuit(Card::Suit suit);
  int findPosition( Card * c);
 private:
  PRNG prng;
  int score;
  int ID;
  string name;
  virtual Card * followSuit(Card::Rank rank, Card::Suit suit) = 0;
  virtual Card * lead() = 0;
  virtual Card * throwOff() = 0;
};


#endif
