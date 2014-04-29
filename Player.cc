#include <iostream>
#include "Player.h"
#include "CardPile.h"
#include "Trick.h"

using namespace std;

extern int maxScore;
extern Player * player[4];
extern int leadPlayer;

// Constructor
Player::Player(string name, int ID): name(name), ID(ID), score(0) {};


// Setters and getters
string Player::getName(){
  return name;
}
int Player::getID() {
  return ID;
}
void Player::setScore(int score) {
  this->score = score;
}
int Player::getScore() {
  return score;
}

void Player::setRandomSeed(uint32_t randomSeed) {
  prng.seed(randomSeed);
}

void Player::playCard(Trick &trick){
  if (trick.size()==0) { // Lead Card
    Card *leadCard = this->lead();
    int leadPosition = findPosition(leadCard);
    // Update trick
    //trick.insert(trick.begin(), leadCard);
    trick.push_back(leadCard);
    trick.setLead(leadCard);
    trick.setTrump(leadCard);
    trick.trumpPlayer = this;
    cout << "  " << this->name << " led " << *leadCard << endl;
    // Remove card from player's cardpile
    this->hand.erase(this->hand.begin()+leadPosition);
  }
  else if (this->haveSuit(trick.getLead()->getSuit())) { // Follow Card
    Card * followCard =  this->followSuit(trick.getTrump()->getRank(), trick.getTrump()->getSuit());
    int followPosition = findPosition(followCard);
    // Update trick
    //trick.insert(trick.begin(), followCard);
    trick.push_back(followCard);
    if (!(*followCard < *(trick.getTrump()))) {
      trick.setTrump(followCard);
      trick.trumpPlayer = this;
    }
    cout << "  " << this->name << " followed suit with " << *followCard << endl;
    this->hand.erase(this->hand.begin()+followPosition);
  }
  else { // Throw Off
    Card *throwCard = this->throwOff();
        int throwPosition = findPosition(throwCard);
    // Update trick
    //trick.insert(trick.begin(), throwCard);
    trick.push_back(throwCard);
    cout << "  " << this->name << " threw off " << *throwCard << endl;
    this->hand.erase(this->hand.begin()+throwPosition);
  }
}

bool Player::haveSuit(Card::Suit suit) {
  for (int i = 0; i < this->hand.size(); i++) {
    if ((this->hand.at(i)->getSuit()) == suit) return true;
  }
  return false;
}

int Player::findPosition(Card * c) {
  for(int i = 0; i < this->hand.size(); i++) {
    if (*c == *(this->hand.at(i))) return i;
  }
}
