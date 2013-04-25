/*
 * cards.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: Kyle Bruin & Cameron Bigelow
 */
#include "cards.h"
#include <string>
#include <iostream>

using namespace std;

Table table1;
Shoe shoe;
int status = -1;

int main(int argc, char* argv[]) {
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
