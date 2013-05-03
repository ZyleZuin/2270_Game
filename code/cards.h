/*
 * cards.h
 *
 *  
 *      Author: Kyle Bruin & Cameron Bigelow & Matt Gettyo
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
	vector<char> hand;
	bool busted;
	int handValue;
	bool human;
	string name;
	int wins;
	int loses;
public:
	void addToHand();
	bool getBusted();
	void setBusted(bool busted);
	int getHandValue();
	void setHandValue(int value);
	bool isHuman();
	void setHuman(bool human);
	string getName();
	void setName(string name);
	int getWins();
	void setWins(int wins);
	int getLoses();
	void setLoses(int loses);
};

class Table {
private:
	int numPlayers;
	int round;
public:
	vector<Player*> players;
	void init_game();
	void final_tally();
	void create_player(string playerName, bool human);
	void clear_and_deal();
	void player_turn(Player* player);
	void ai_turn(Player* player);
	void human_turn(Player* player);
	void end_round();
	int getPlayers();
	void setPlayers(int players);
	int getRound();
	void setRound(int round);
};

#endif /* CARDS_H_ */
