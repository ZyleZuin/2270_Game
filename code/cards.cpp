/*
 * cards.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: Kyle Bruin, Cameron Bigelow, Matt Getty
 */
#include "cards.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

int main (int argc, char* argv[])
{
  srand(unsigned(time(0)));
  // More stuff goes here. 
}

// Adds cards to a deck.
void Shoe::addDeck(int numDecks) {
  vector<char> cardsToAdd; // Add the cards.
  cardsToAdd.push_back('1');
  cardsToAdd.push_back('2');
  cardsToAdd.push_back('3');
  cardsToAdd.push_back('4');
  cardsToAdd.push_back('5');
  cardsToAdd.push_back('6');
  cardsToAdd.push_back('7');
  cardsToAdd.push_back('8');
  cardsToAdd.push_back('9');
  cardsToAdd.push_back('J');
  cardsToAdd.push_back('Q');
  cardsToAdd.push_back('K');
  cardsToAdd.push_back('A');
  for ( int k = 0; k < numDecks; k++ ) {
    for ( int i = 0; i < cardsToAdd.size(); i++) {
      for ( int j = 0; j < 4 ; j++ ) {
	cards.push_back(cardsToAdd[i]);
      }
    }
  }
  // Now we just need to shuffle the values.

  std::random_shuffle ( cards.begin(), cards.end() );
  cout << "DEBUG, first two cards care: " << cards[1] << " " << cards[2] << endl; // --
}

// Deals a card to a player
void Shoe::dealCard(Player player) {
  cout << "Giving a player card " << cards[cards.size() - 1];
  player.addcard(cards[cards.size()] - 1);
  cards.pop_back();
  if ( cards.size() < 2 ) { 
    cout << "DEBUG: Adding a new deck.\n" // --
    addDeck(1);
  }
}




