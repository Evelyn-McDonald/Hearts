#include <iostream>
#include "Trick.h"

using namespace std;

Trick::Trick() : lead(0),trump(0),trumpPlayer(0),CardPile::CardPile(){}

void Trick::setLead(Card* card){
  lead=card;
}
void Trick::setTrump(Card* card){
  trump=card;
}
Card * Trick::getLead(){
  return lead;
}
Card * Trick::getTrump(){
  return trump;
}
