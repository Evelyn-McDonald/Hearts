#include <cstdlib>
#include "Deck.h"
#include "Card.h"
#include "CardPile.h"
#include <iostream>
using namespace std;


Deck::Deck() : CardPile::CardPile() {}
Deck::~Deck(){}

// Generate deck
void Deck::generate(){
  for (int i=0; i<4; i++){
    for (int j=0; j<13; j++){
      this->push_back(new Card((Card::Rank)j, (Card::Suit)i));
    }
  }
}

// Test if deck represents a full deck
bool Deck::playingWithAFullDeck () const {
  const Deck* d=this;
  Card c;
  for (int i=0; i<4; i++){
    for (int j=0; j<13; j++){
      c = Card((Card::Rank)j, (Card::Suit)i);
      for (int k=0; k<52; k++){
        if (*(d->at(k)) == c) break;
        else if (k + 1 == 52){ /*delete c;*/  return false;}
      }
    }
  }
  return true;
}

// Output overloaded function
istream& operator>> (istream& in, Deck& deck){
  for (int i = 0; i < 52; i++){
    Card* card= new Card();
    in >> *card;
    //deck.insert(deck.begin(), card);
    deck.push_back(card);
  }
  if (!deck.playingWithAFullDeck()) {
    cerr << "Not Full Deck" << endl;
    exit(1);
  }
  return in;
}
