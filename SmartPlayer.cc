#include <iostream>
#include "Player.h"
#include "SmartPlayer.h"

using namespace std;

SmartPlayer::SmartPlayer(string name,int ID) : Player::Player(name,ID) {}

Card * SmartPlayer::lead(){
  Card * lowestcard=hand.at(0);
  for (int i=1; i<hand.size(); i++){
    if (*(hand.at(i)) < *lowestcard){
      lowestcard=hand.at(i);
    }
  }
  return lowestcard;
}

Card * SmartPlayer::throwOff(){
  Card * highestheart= NULL;
  Card * highestnonheart=NULL;
  Card qs = Card(Card::Queen, Card::Spades);
  for (int i=0; i<hand.size(); i++){
    if (*(hand.at(i)) == qs){
      return hand.at(i);
    }
    else if ((hand.at(i)->getSuit() == Card::Hearts)){
      if (highestheart==NULL || (!(*(hand.at(i)) < *highestheart))){
        highestheart=hand.at(i);
      }
    }
    else if (highestnonheart==NULL || (!(*(hand.at(i)) < *highestnonheart))){
      highestnonheart=hand.at(i);
    }
  }
  if (highestheart!=NULL)
    return highestheart;
  else {
    return highestnonheart;
  }
}
Card * SmartPlayer::followSuit(Card::Rank rank, Card::Suit suit){
    Card * cardsofSuit[13];
    int numofSuit=0;
    Card * highestlessthan = NULL;
    Card * lowesthigherthan = NULL;
    for (int i=0; i<hand.size(); i++){
      if (hand.at(i)->getSuit()==suit){
        cardsofSuit[numofSuit]=hand.at(i);
        numofSuit++;
      }
    }
    for (int j=0; j<numofSuit; j++){
      if (cardsofSuit[j]->getRank() < rank){
        if (highestlessthan == NULL) highestlessthan = cardsofSuit[j];
        else if (cardsofSuit[j]->getRank() > highestlessthan->getRank())        highestlessthan=cardsofSuit[j];
      }
      else {
        if (lowesthigherthan == NULL) lowesthigherthan = cardsofSuit[j];
        else if (cardsofSuit[j]->getRank() < lowesthigherthan->getRank()) lowesthigherthan=cardsofSuit[j];
      }
    }
    if (highestlessthan != NULL) return highestlessthan;
    else return lowesthigherthan;
}
