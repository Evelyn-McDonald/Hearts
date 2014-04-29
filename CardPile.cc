#include <vector>
#include <algorithm>
#include <iostream>
#include "CardPile.h"
#include "Card.h"

const uint32_t CardPile::DefaultRandomSeed = 37;

CardPile::CardPile() : prng(DefaultRandomSeed) {}
CardPile::~CardPile() {
  //  for(int i = 0; i < this->size(); i++) {
  // delete this->at(i);
  //}
}

void CardPile::setRandomSeed(uint32_t randomSeed) {
  prng.seed(randomSeed);
}

// Print cards in cardpile
void CardPile::print(){
  for (int i=0; i < size(); i++){
    cout << *(at(i));
    }
}

// Value of hearts in cardpile
int CardPile::heartsValue(){
  int heartsValue=0;
  for (int i=0; i<size(); i++){
    heartsValue = heartsValue + at(i)->getHeartsValue();
  }
  return heartsValue;
}

// Shuffle deck
void CardPile::shuffle() {
  for (int i = size() - 1; i > 0; i--) {
    const int j = prng(i);
    Card* tmp = at(j);
    at(j) = at(i);
    at(i) = tmp;
  }
}
