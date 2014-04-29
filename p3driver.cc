#include <iostream>
#include <string>
#include <fstream>
#include "Card.h"
#include "CardPile.h"
#include "Deck.h"
#include "PRNG.h"
#include "Player.h"
#include "SmartPlayer.h"
#include "RandomPlayer.h"
#include "HumanPlayer.h"
#include <cstdlib>
#include "Trick.h"
using namespace std;

// Global Variables
Player* player[4] = {NULL};

int main (int argc, char* argv[]) {
  int maxScore = 40;
  Deck d;
  bool deckIn = false;

  // Parse command line options
  for (int i = 1; i < argc; i++) {
    if (string(argv[i]) == "-r") { // Set Seed
      if (deckIn == true) {
        cout << "Aborting; -r must occur before -d on command line if both flags are used." << endl;
        exit(1);
      }
      i++;
      d.setRandomSeed(atoi(argv[i]));
    }
    else if (string(argv[i]) == "-s") { // Set maxScore
      i++;
      maxScore = atoi(argv[i]);
    }
    else if (string(argv[i]) == "-d") { // Set Deck
      deckIn = true;
      i++;
      ifstream myDeck;
      myDeck.open(argv[i]);
      myDeck >> d;
      myDeck.close();
    }
    else if (string(argv[i]) == "-p") { // Set Players
      for (int j = 0; j < 4; j++) {
        i++;
        if (string(argv[i+1]) == "S") { // SmartPlayer
          player[j] = new SmartPlayer('s' + string(argv[i]), j);
          i++;
        }
        else if (string(argv[i+1]) == "R") { // RandomPlayer
          player[j] = new RandomPlayer('r' + string(argv[i]), j);
          i = i + 2;
          player[j]->setRandomSeed(atoi(argv[i]));
        }
        else if (string(argv[i+1]) == "H") { // HumanPlayer
          player[j] = new HumanPlayer('h' + string(argv[i]), j);
          i++;
        }
        else {
          cerr << "Invalid player type" << endl;
          return 0;
        }
      }
    }
  }
  if (player[0] == NULL) {
    player[0] = new SmartPlayer("sAlice", 0);
    player[1] = new SmartPlayer("sBob", 1);
    player[2] = new SmartPlayer("sCarole", 2);
    player[3] = new SmartPlayer("sTed", 3);
  }
  if (d.empty()) {
    d.generate();
  }

  // Loop through hands
  int hand = 1;
  int leadPlayer;
  int TwoClubsPosition;
  int dealer = 3;
  cout << "Starting a new game of Hearts. The MaxPoints is " << maxScore << "." << endl << endl;
  while ((player[0]->getScore() < maxScore) && (player[1]->getScore() < maxScore) && (player[2]->getScore() < maxScore) && (player[3]->getScore() < maxScore) ){
    if (hand > 1) d.generate();
    d.shuffle();
    // Deal Cards
    Card* TwoOfClubs = new Card(Card::Two,Card::Clubs);
    int handPosition = 12;
    for (int i = 0; i < 52; i = i+4){
      player[dealer]->hand.insert(player[dealer]->hand.begin(),d.at(i));
      player[(dealer+3)%4]->hand.insert(player[(dealer+3)%4]->hand.begin(),d.at(i+1));
      player[(dealer+2)%4]->hand.insert(player[(dealer+2)%4]->hand.begin(),d.at(i+2));
      player[(dealer+1)%4]->hand.insert(player[(dealer+1)%4]->hand.begin(),d.at(i+3));
      if (*(d.at(i)) == *TwoOfClubs){ leadPlayer = dealer; TwoClubsPosition=handPosition;}
      else if (*(d.at(i+1)) == *TwoOfClubs){ leadPlayer = (dealer+3)%4; TwoClubsPosition=handPosition;}
      else if (*(d.at(i+2)) == *TwoOfClubs){ leadPlayer = (dealer+2)%4; TwoClubsPosition=handPosition;}
      else if (*(d.at(i+3)) == *TwoOfClubs){ leadPlayer = (dealer+1)%4; TwoClubsPosition=handPosition;}
      handPosition--;
    }
    cout << "At the beginning of hand " << hand << ", here is the deck:" << endl;
    cout << "    " << flush;
    d.print();
    cout << endl << endl;
        cout << "Here are the hands for each player at the start of hand number " << hand << endl;
    for (int i = 0; i <= 3; i++) {
      cout << endl << player[i]->getName() << " has these cards:" << endl;
      cout << "    " << flush;
      player[i]->hand.print();
    }
    cout << endl;
 // Round
    Trick trick = Trick();
    for (int i=1; i<14; i++){
      cout << endl << "Now starting round " << i << " of hand " << hand << endl;
      if (i == 1){ // First round: player with 2C leads
        cout << "  " << player[leadPlayer]->getName() << " has 2C and leads with it" << endl;
        trick.setLead(TwoOfClubs);
        trick.setTrump(TwoOfClubs);
        //trick.insert(trick.begin(),TwoOfClubs);
        trick.push_back(TwoOfClubs);
        trick.trumpPlayer=player[leadPlayer];
        player[leadPlayer]->hand.erase(player[leadPlayer]->hand.begin()+TwoClubsPosition);
      }
      else {
        player[leadPlayer]->playCard(trick);
      }
      for (int j = 0; j < 3; j++) {
        leadPlayer = (leadPlayer + 1) % 4;
        player[leadPlayer]->playCard(trick);
      }
      cout << "  " << trick.trumpPlayer->getName() << " won the trick and added the following cards:" << endl;
      cout << "    "; trick.print();
      cout << endl;
      // Add trick to trump player
      for (int i = 0 ; i <= 3; i++) {
        player[trick.trumpPlayer->getID()]->tricklist.push_back(trick.at(i));
      }
      leadPlayer = trick.trumpPlayer->getID();
      trick.erase(trick.begin(),trick.end());
    }
    cout << endl << "At the end of hand " << hand << ", the score is:" << endl;
    for (int k=0; k<4; k++){
      //for (int i=0; i<player[k]->tricklist.size(); i++){
      int score = player[k]->getScore() + player[k]->tricklist.heartsValue();
      player[k]->setScore(score);
      cout << "  " << player[k]->getName() << "  " <<  player[k]->getScore() << endl;
      // Erase tricklist and hands
      player[k]->tricklist.erase(player[k]->tricklist.begin(), player[k]->tricklist.end());
      player[k]->hand.erase(player[k]->hand.begin(), player[k]->hand.end());
    }
    cout << endl;
    // Delete Deck
    for (int i = 0; i < 52; i++) {
      delete d.at(0);
      d.erase(d.begin());
    }
    hand++;
    dealer = (dealer + 1) % 4;
    delete TwoOfClubs;
  } // Hand while loop

  cout << "The game is over." << endl;
  Player* winner=player[0];
  Player* loser=player[0];
  for (int i=1; i<4; i++){
    if (player[i]->getScore() < winner->getScore())
      winner = player[i];
    else if (player[i]->getScore() > loser->getScore())
      loser=player[i];
  }
  cout << loser->getName() << " has exceeded " << maxScore << " points." << endl;
  cout << "The winner is " << winner->getName() << endl;;

  // Delete Players
}
