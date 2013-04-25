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

Table table1;
Shoe shoe;
int status = -1;

int main(int argc, char* argv[]) {
	srand(unsigned(time(0)));
	table1.begin_round();
	if (status == 0) {
		for (int i = 0; i < table1.get_players(); i++) {
			table1.player_turn(table1.players[i]);
		}
	}
	table1.end_round();
}
void Table::begin_round() {
	int players;
	status = 0;
	// ROUND GREETING & SETUP
	if (this->round == 0) {
		cout << "WELCOME TO CS2270 BLACKJACK EDITION" << endl;
		cout << "How Many Players: " << endl;
		cin >> players;
		this->set_players(players);
		cout << "ROUND 1!" << endl;
	} else {
		cout << " ROUND " << this->round << endl;
	}
	// DEAL HANDS
	for (int i = 0; i < this->num_players; i++) {
		cout << "Player " << i << endl;
		shoe.dealCard(this->players[i]);
		shoe.dealCard(this->players[i]);
	}
}
void Table::player_turn(Player player) {
	// DEAL HANDS
	char decision;
	cout << player.get_name() << endl;
	while (decision != "S") {
		cout << "You are at " << player.getValue() << endl;
		cout << "Would you like to Hit (H) or Stay (S)?" << endl;
		cin >> decision;
		if (player.getValue() > 21) {
			cout << "You Busted!";
			player.busted() = true;
			break;
		}
	}
}
void Table::end_round() {
	Player winner;
	char decision;
	for (int i = 0; i < table1.get_players(); i++) {
		Player player = table1.players[i];
		cout << player.get_name() << endl;
		if (player.busted()) {
			cout << "BUSTED" << endl;
		} else {
			//  NEED TO HANDLE A TIE
			if (winner == NULL) {
				winner = player;
			} else if (winner.getValue() < player.getValue) {
				winner = player;
			}
			cout << player.getValue() << endl;
		}
	}
	cout << "The Winner is: " << winner.get_name() << endl;
	winner.addWin();
	cout << "This Player has " << winner.getWins() << " wins!" << endl;

//	cout << endl;
//	cout << "Would you like to play another round? Y/N" << endl;
//	cin >> decision;
}
int Table::get_players() {
	return this->num_players;
}
void Table::set_players(int players) {
	this->num_players = players;
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
	for (int k = 0; k < numDecks; k++) {
		for (int i = 0; i < cardsToAdd.size(); i++) {
			for (int j = 0; j < 4; j++) {
				cards.push_back(cardsToAdd[i]);
			}
		}
	}
	// Now we just need to shuffle the values.

	std::random_shuffle(cards.begin(), cards.end());
	cout << "DEBUG, first two cards care: " << cards[1] << " " << cards[2]
			<< endl; // --
}

// Deals a card to a player
void Shoe::dealCard(Player player) {
	cout << "Giving a player card " << cards[cards.size() - 1];
	player.addcard(cards[cards.size()] - 1);
	cards.pop_back();
	if (cards.size() < 2) {
		cout << "DEBUG: Adding a new deck.\n"
		// --
		addDeck(1);
	}
}

