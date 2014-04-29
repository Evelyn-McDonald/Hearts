#include <iostream>
#include "Player.h"
#include "RandomPlayer.h"

using namespace std;

RandomPlayer::RandomPlayer(string name, int ID) : Player::Player(name,ID) {}

void RandomPlayer::setRandomSeed(uint32_t randomSeed) {
  prng.seed(randomSeed);
}

Card * RandomPlayer::lead(){
  int random;
  int size = hand.size();
  random=prng(0,size-1);
  return hand.at(random);
}

Card * RandomPlayer::throwOff(){
  int random;
  int size = hand.size();
  random=prng(0,size-1);
  return hand.at(random);
}

Card * RandomPlayer::followSuit(Card::Rank rank, Card::Suit suit){
  int random;
  int numofSuit=0;
  Card * cardsofSuit[13];
  for (int i=0; i<hand.size(); i++){
    if (hand.at(i)->getSuit()==suit){
       cardsofSuit[numofSuit]=hand.at(i);
       numofSuit++;
    }
  }
  random=prng(0,numofSuit-1);
  return cardsofSuit[random];
}
