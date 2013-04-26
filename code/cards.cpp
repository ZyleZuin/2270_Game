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
#include <map>

using namespace std;

Table table1;
Shoe shoe;
int status = -1;

int main(int argc, char* argv[]) {
	srand(unsigned(time(0)));
	shoe.addDeck(1);
	// Reset our Table
	table1.setPlayers(0);
	table1.setRound(0);
	status = 0;
	while (status == 0) {
		table1.setRound(table1.getRound() + 1);
		// Start the round
		table1.begin_round();
		// Cycle Through Players
		for (int i = 0; i < table1.getPlayers(); i++) {
			table1.player_turn(*table1.players[i]);
		}
		//End the round
		table1.end_round();
	}
}
void Table::begin_round() {
	int players;
	vector<std::string> player_names;
	status = 0;
	// ROUND GREETING & SETUP
	if (this->getRound() == 1) {
		cout << "WELCOME TO CS2270 BLACKJACK EDITION" << endl;
		cout << "How Many Players: " << endl;
		cin >> players;
		this->setPlayers(players);
		
		// Theoretically get some player names. 
		for ( int j = 0; j < players; j++ ) {
		  std::string player_name = "";
		  cout << "PLAYER #" << j + 1 << " NAME: ";
		  cin >> player_name;
		  player_names.push_back(player_name);
		  cout << endl;
		}
		  
		cout << "ROUND 1!" << endl;
	} else {
		cout << " ROUND " << this->getRound() << endl;
	}
	// Create Players
	for (int i = 0; i < this->getPlayers(); i++) {
		Player* newPlayer = new Player;
		newPlayer->setBusted(false);
		newPlayer->setHandValue(0);
		newPlayer->setHuman(true);
		newPlayer->setName(player_names[i]);
		newPlayer->setWins(0);
		newPlayer->setLoses(0);
		table1.players.push_back(newPlayer);
	}
	// DEAL HANDS

	for (int i = 0; i < this->numPlayers; i++) {
		table1.players[i]->addToHand();
		table1.players[i]->addToHand();
	}
}
void Table::player_turn(Player player) {
	// DEAL HANDS
	bool done = false;
	char decision;
	cout << player.getName() << endl;
	while (decision != 'S') {
		cout << "You are at " << player.getHandValue() << endl;
		while (!done) {
			cout << "Would you like to Hit (H) or Stay (S)?" << endl;
			cin >> decision;
			if (decision == 'H' || decision == 'S') {
				done = true;
			} else {
				cout << "Invalid Input.  H or S" << endl;
			}
		}
		done = false;
		if (decision == 'H') {
			player.addToHand();
		}
		if (player.getHandValue() > 21) {
			cout << "You Busted!" << endl;
			player.setBusted(true);
			break;
		}
	}
}
void Table::end_round() {
	Player winner;
	winner.setName("NULL");
	char decision;
	bool done = false;
	for (int i = 0; i < table1.getPlayers(); i++) {
		Player* player = table1.players[i];
		cout << player->getName() << endl;
		if (player->getBusted()) {
			cout << "BUSTED" << endl;
		} else {
			//  NEED TO HANDLE A TIE
//			if (winner == NULL) {
//				winner = player;
//			} else if (winner.getValue() < player.getValue) {
//				winner = player;
//			}
			cout << player->getHandValue() << endl;
		}
	}
	if (winner.getName() == "NULL") {
		cout << "No Winner.  Everyone Busted!" << endl;
	} else {
		cout << "The Winner is: " << winner.getName() << endl;
		winner.setWins(winner.getWins() + 1);
		cout << "This Player has " << winner.getWins() << " wins!" << endl;
		cout << endl;
	}
	while (!done) {
		cout << "Would you like to play another round? Y/N" << endl;
		cin >> decision;
		if (decision == 'N' || decision == 'Y') {
			done = true;
		} else {
			cout << "Invalid Input.  Y or N" << endl;
		}
	}
	if (decision == 'N') {
		status = 1;
	}
}
int Table::getPlayers() {
	return this->numPlayers;
}
void Table::setPlayers(int players) {
	this->numPlayers = players;
}
int Table::getRound() {
	return this->round;
}
void Table::setRound(int round) {
	this->round = round;
}
void Shoe::addDeck(int numDecks) {
	vector<char> cardsToAdd;
	int size = 0;
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
	size = cardsToAdd.size();
	for (int i = 0; i < numDecks; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < 4; k++) {
				cards.push_back(cardsToAdd[k]);
			}
		}
	}
	random_shuffle(cards.begin(), cards.end());
}
char Shoe::dealCard() {
	char card = cards[cards.size() - 1];
	cards.pop_back();
	return card;
}
void Player::addToHand() {
	char newCard = shoe.dealCard();
	this->hand.push_back(newCard);
	std::map<char, int> cardMap;
	cardMap['2'] = 2;
	cardMap['3'] = 2;
	cardMap['4'] = 4;
	cardMap['5'] = 5;
	cardMap['6'] = 6;
	cardMap['7'] = 7;
	cardMap['8'] = 8;
	cardMap['9'] = 9;
	cardMap['J'] = 10;
	cardMap['Q'] = 10;
	cardMap['K'] = 10;
	cardMap['A'] = 1;
	this->handValue += cardMap[newCard];
}
bool Player::getBusted() {
	return this->busted;
}
void Player::setBusted(bool busted) {
	this->busted = busted;
}
int Player::getHandValue() {
	return this->handValue;
}
void Player::setHandValue(int value) {
	this->handValue = value;
}
bool Player::getHuman() {
	return this->human;
}
void Player::setHuman(bool human) {
	this->human = human;
}
string Player::getName() {
	return this->name;
}
void Player::setName(string name) {
	this->name = name;
}
int Player::getWins() {
	return this->wins;
}
void Player::setWins(int wins) {
	this->wins = wins;
}
int Player::getLoses() {
	return this->loses;
}
void Player::setLoses(int loses) {
	this->loses = loses;
}

