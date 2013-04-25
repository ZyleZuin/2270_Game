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
	table1.begin_round();
	if (status == 0) {
		for (int i = 0; i < table1.getPlayers(); i++) {
			table1.player_turn(*table1.players[i]);
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
		this->setPlayers(players);
		cout << "ROUND 1!" << endl;
	} else {
		cout << " ROUND " << this->round << endl;
	}
	// Create Players
	for (int i = 0; i < this->num_players; i++) {
		Player* newPlayer = new Player;
		newPlayer->setBusted(false);
		newPlayer->setName("Jim");
		table1.players.push_back(newPlayer);
	}
	// DEAL HANDS

	for (int i = 0; i < this->num_players; i++) {
		cout << "Player " << i << endl;
		table1.players[i]->addToHand();
		table1.players[i]->addToHand();
	}
}
void Table::player_turn(Player player) {
	// DEAL HANDS
	char decision;
	cout << player.getName() << endl;
	while (decision != 'S') {
		cout << "You are at " << player.getHandValue() << endl;
		cout << "Would you like to Hit (H) or Stay (S)?" << endl;
		cin >> decision;
		if (player.getHandValue() > 21) {
			cout << "You Busted!";
			player.setBusted(true);
			break;
		}
	}
}
void Table::end_round() {
	Player winner;
	char decision;
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
	cout << "The Winner is: " << winner.getName() << endl;
	winner.setWins(winner.getWins() + 1);
	cout << "This Player has " << winner.getWins() << " wins!" << endl;

//	cout << endl;
//	cout << "Would you like to play another round? Y/N" << endl;
//	cin >> decision;
}
int Table::getPlayers() {
	return this->num_players;
}
void Table::setPlayers(int players) {
	this->num_players = players;
}
int Table::getRound() {
	return this->round;
}
void Table::setRound(int round) {
	this->round = round;
}
// Adds cards to a deck.
void Shoe::addDeck(int numDecks) {
	vector<char> cardsToAdd; // Add the cards.
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

		addDeck(1);
	}
	cout << "Giving a player card " << cards[cards.size() - 1] << " " << endl;
	char card = cards[cards.size() - 1];
	cards.pop_back();
	return card;
}
void Player::addToHand() {
	cout << "DEBUG: Trying to add card.\n";
	// Player.hand.push_back(shoe.dealCard());
	//Player.hand.push_back(shoe.dealCard());
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

	cout << " DEBUG: added a card \n";
}
vector<char> Player::getHand() {
	// for (int i = Shoe->cards.begin(); i != 3; i++) {
	//   hand.push_back(i);
	// }
	cout << "Your cards are: " << hand.at(0) << " " << hand.at(1) << endl;
	return hand;
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

