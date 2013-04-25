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
	vector<char> cards;
public:
	char dealCard(); // Add a new card to the deck
	void addDeck(int numDecks); // Adds 52 cards
};

class Player {
private:
	string name;
	vector<char> hand;
	int hand_value;
	bool human;
	int wins;
	int loses;
public:
	vector<char> getHand();
	bool isbusted();
	void setBusted();
	int getValue();
	bool isHuman();
	void set_name();
	string get_name();
	int getWins();
	void addWin();
	void addcard();
};

class Table {
private:
	int num_players;
	int round;
public:
	vector<Player*> players;
	void begin_round();
	void player_turn(Player player);
	void end_round();
	int get_players();
	void set_players(int players);
};

#endif /* CARDS_H_ */
