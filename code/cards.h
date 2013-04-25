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

class Shoe;
class Player;
class Table;

class Shoe {
private:
	vector<int> cards;
public:
	char dealCard(Player player); // Add a new card to the deck
	int addDeck(int numDecks); // Adds 52 cards
};

class Player {
private:
	string name;
	vector<char> hand;
	int hand_value;
	bool AI;
	int wins;
	int loses;
public:
	vector<char> getHand();
	bool busted();
};


class Table {
private:
	int num_players;
	int round;
public:
	void begin_round();
	void turn();
	void end_round();
};

#endif /* CARDS_H_ */
