#ifndef _CARDPILE_H_
#define _CARDPILE_H_

using namespace std;

#include <vector>
#include "Card.h"
#include "PRNG.h"

class CardPile : private vector<Card*> {
 public:
  // Constructors and destructor
  CardPile ();
  virtual ~CardPile ();

  void setRandomSeed(uint32_t randomSeed);
  // Other stuff needed
  void shuffle();
  virtual void print();
  int heartsValue(); // Returns sum of hearts values in pile

  // "Promoted" container methods and types
  using vector<Card*>::iterator;
  using vector<Card*>::const_iterator;
  using vector<Card*>::begin;
  using vector<Card*>::end;
  using vector<Card*>::size;
  using vector<Card*>::at;
  using vector<Card*>::push_back;
  using vector<Card*>::insert;
  using vector<Card*>::erase;
  using vector<Card*>::empty;

 private:
  PRNG prng;
  static const uint32_t DefaultRandomSeed;
};

#endif
