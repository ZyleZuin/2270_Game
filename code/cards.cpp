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
		table1.players[i].addcard();
		table1.players[i].addcard();
	}
}
void Table::player_turn(Player player) {
	// DEAL HANDS
	char decision;
	cout << player.get_name() << endl;
	while (decision != 'S') {
		cout << "You are at " << player.getValue() << endl;
		cout << "Would you like to Hit (H) or Stay (S)?" << endl;
		cin >> decision;
		if (player.getValue() > 21) {
			cout << "You Busted!";
			player.isbusted();
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
		if (player.isbusted()) {
			cout << "BUSTED" << endl;
		} else {
			//  NEED TO HANDLE A TIE
//			if (winner == NULL) {
//				winner = player;
//			} else if (winner.getValue() < player.getValue) {
//				winner = player;
//			}
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
char Shoe::dealCard() {
	if (cards.size() < 2) {
		cout << "DEBUG: Adding a new deck.\n";
		// --
		addDeck(1);
	}
	cout << "Giving a player card " << cards[cards.size() - 1];
	char card = cards[cards.size() - 1];
	cards.pop_back();
	return card;
}
void Player::addcard() {
	// Player.hand.push_back(shoe.dealCard());
	//Player.hand.push_back(shoe.dealCard());
	this->hand.push_back(shoe.dealCard());
}
vector<char> Player::getHand() {
	// for (int i = Shoe->cards.begin(); i != 3; i++) {
	//   hand.push_back(i);
	// }
	cout << "Your cards are: " << hand.at(0) << " " << hand.at(1) << endl;
	return hand;
}
int Player::getValue() {
	return this->hand_value;
}
bool Player::isbusted() {
	if (hand_value > 21) {
		return true;
	} else {
		return false;
	}
}
string Player::get_name() {
	return this->name;
}
void Player::addWin() {
	this->wins++;
}

int Player::getWins() {
	return this->wins;
}
