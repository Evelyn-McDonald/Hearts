#include <iostream>
#include "Player.h"
#include "HumanPlayer.h"

using namespace std;

// Interactive player
HumanPlayer::HumanPlayer(string name, int ID) : Player::Player(name, ID) {}
Card * HumanPlayer::lead(){
  cout << "Human player " << getName() << " has these cards:" << endl;
  hand.print();
  cout << endl << "What card would you like to play, " << getName() << "? " << flush;
  Card * c = new Card();
  cin >> *c;
  return c;
}

// Take user input
Card * HumanPlayer::throwOff(){
  cout << "Human player " << getName() << " has these cards:" << endl;
  hand.print();
  cout << endl << "What card would you like to play, " << getName() << "? " << flush;
  Card * c = new Card();
  cin >> *c;
  return c;
  }

// Take user input
Card * HumanPlayer::followSuit(Card::Rank rank, Card::Suit suit){
  cout << "Human player " << getName() << " has these cards:" << endl;
  hand.print();
  cout << endl << "What card would you like to play, " << getName() << "? " << flush;
  Card * c = new Card();
  cin >> *c;
  cout << "card read" << endl;
  return c;
}
