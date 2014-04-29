#include <string>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include "Card.h"

using namespace std;

const string Card::RankName = "23456789TJQKA";
const string Card::SuitName = "SDCH";
const int Card::numRanks = RankName.length();
const int Card::numSuits = SuitName.length();
const int Card::numCards = Card::numRanks * Card::numSuits;
const Card Card::TwoOfClubs (Card::Two, Card::Clubs);
const Card Card::QueenOfSpades (Card::Queen, Card::Spades);

// Constructors/  Destructors
Card::Card() : rank(Ace), suit(Spades) {}

Card::Card(Rank r, Suit s) : rank(r) , suit(s) {}

Card::Card (string sCard) : rank((Rank)Card::RankName.find(sCard[0])) , suit((Suit)Card::SuitName.find(sCard[1])) {}

Card::~Card () {}

// Accessor fcns
Card::Rank Card::getRank () const{
  return rank;
}
Card::Suit Card::getSuit () const{
  return suit;
}
int Card::getHeartsValue () const{
  if (this->getSuit() == Hearts) return 1;
  else if (this->getSuit() == Spades && this->getRank() == Queen) return 13;
  else return 0;
}
// Static utility function to check if a two char string
// represents a legal card value
bool Card::stringIsALegalCard (string s){
  bool validRank=false, validSuit=false, lengthTwo=false;
  // Test LEngth
  if (s.length()==2) lengthTwo=true;
  // Test Rank
  if (Card::RankName.find(s[0])!=string::npos) validRank=true;
  // Test Suit
  if (Card::SuitName.find(s[1])!=string::npos) validSuit=true;
  return validRank && validSuit && lengthTwo;
}

bool operator== (const Card& c1, const Card& c2) {
  return (c1.getRank() == c2.getRank()) && (c1.getSuit() == c2.getSuit());
}
bool operator< (const Card& c1, const Card& c2) {
  if (c1.getRank() < c2.getRank()) return true;
  else if (c1.getRank() == c2.getRank()) return c1.getSuit() < c2.getSuit();
  else return false;
}
ostream& operator<< (ostream &out, const Card &c) {
  out << Card::RankName[c.getRank()] << Card::SuitName[c.getSuit()] << " ";
  return out;
}
istream& operator>> (istream& in, Card& c) {
  string card;
  in >> card;
  if (!c.stringIsALegalCard(card)){
    cerr << "Invalid Card" << endl;
    exit(1);
  }
  c = Card(card);
  return in;
}
