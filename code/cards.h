/*
 * cards.h
 *
 *  Created on: Apr 24, 2013
 *      Author: Kyle Bruin & Cameron Bigelow
 */

#ifndef CARDS_H_
#define CARDS_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Card;
class Deck;

class Deck {
private:
	vector<Card> cards; // Index is position in the deck
public:
	int addCard(char index, string suit); // Add a new card to the deck
	int removeCard();
	int getSize(); // Returns size of deck
	int moveCard(); // Send card to another deck
};

class Card {
private:
	char index;
	string suit;
	string color;
public:
};


#endif /* CARDS_H_ */
