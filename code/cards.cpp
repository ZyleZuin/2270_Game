/*
 * cards.cpp
 *
 *  Blackjack - Now with some AI!
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
  table1.setPlayers(0);
  table1.setRound(0);
  table1.init_game();  

  while (status == 0) {
    table1.setRound(table1.getRound() + 1);
    table1.clear_and_deal();
    for (int i = 0; i < table1.getPlayers(); i++) {
      table1.player_turn(table1.players[i]);
    }
    table1.end_round();
    
    cout << "Would you like to play another round? Y/N" << endl;
    char decision;
    cin >> decision;
    if (decision == 'N') {
      table1.final_tally();
      status == -1;
      break;
    } else { cout << "Onto another round!\n"; }
  }
}

void Table::init_game() {
  int humanPlayers;
  int aiPlayers;
  vector<std::string> player_names;
  status = 0;
  
  cout << "WELCOME TO CS2270 BLACKJACK EDITION\n";
  cout << "How many AI players: \n";
  cin >> aiPlayers;
  cout << "How Many Players: \n";
  cin >> humanPlayers;
  cout << "Starting a game of Blackjack with " << humanPlayers + aiPlayers << " players\n";
  this->setPlayers(humanPlayers + aiPlayers);
  
  // Theoretically get some player names. 
  cout << "Name your human players:\n";
  for ( int j = 0; j < humanPlayers; j++ ) {
    std::string player_name = "";
    cout << "HUMAN PLAYER #" << j + 1 << " NAME: ";
    cin >> player_name;
    create_player(player_name, true);
    cout << endl;
  }
  cout << "Name your AI players.\n";
  for ( int i = 0; i < aiPlayers; i++ ) {
    std::string player_name = "";
    cout << "AI PLAYER #" << i + 1 << " NAME: ";
    cin >> player_name;
    create_player(player_name, false);
    cout << endl;
    // Set them an AI player. 
  }
}

void Table::clear_and_deal() {
  for (int j = 0; j < this->numPlayers; j++) {
    table1.players[j]->setHandValue(0);
  }

  for (int i = 0; i < this->numPlayers; i++) {
    table1.players[i]->addToHand();
    table1.players[i]->addToHand();
  }
}

void Table::create_player(string playerName, bool human) {
  Player* newPlayer = new Player;
  newPlayer->setBusted(false);
  newPlayer->setHandValue(0);
  newPlayer->setHuman(human);
  newPlayer->setName(playerName);
  newPlayer->setWins(0);
  newPlayer->setLoses(0);
  table1.players.push_back(newPlayer);
}

void Table::player_turn(Player* player) {
  if (player->isHuman()) { human_turn(player); }
  else { ai_turn(player); }
}

void Table::ai_turn(Player* player) {
  bool done = false;
  while ( !done ) {
    cout << "AI Player " << player->getName() << " is at " << player->getHandValue() << endl;
    if ( player->getHandValue() < 18 ) {
      cout << "AI PLayer " << player->getName() << " has decided to hit.\n";
      player->addToHand();
    } else { done = true; }
  }
  if ( player->getHandValue() > 21 ) {
    player->setBusted(true);
    cout << "AI Player " << player->getName() << " busted!\n";
  }
}

void Table::human_turn(Player* player) {
  bool done = false;
  char decision;
  cout << player->getName() << endl;
  while (decision != 'S') {
    cout << "You are at " << player->getHandValue() << endl;
    while (!done) {
      cout << "Would you like to Hit (H) or Stay (S)?" << endl;
      cin >> decision;
      if (decision == 'H' || decision == 'S') {	done = true; } else {
	cout << "Invalid Input.  H or S" << endl; } }
    
    done = false;

    if (decision == 'H') { player->addToHand(); }
    if (player->getHandValue() > 21) {
      cout << "You Busted!" << endl;
      player->setBusted(true);
      break; } 
  }
}
void Table::end_round() {
   vector<Player*> winningPlayers;
  vector<Player*> losingPlayers;
  
  // First determine what the high card is in the game.
  int highCard = 0;
  for (int i = 0; i < table1.getPlayers(); i++) {
    Player* player = table1.players[i];
    if ( player->getHandValue() <= 21 && player->getHandValue() > highCard ) {
      highCard = player->getHandValue();
    }
  }

  // Add in who got a high card.
  for (int i = 0; i < table1.getPlayers(); i++) {
    Player* player = table1.players[i];
    if ( player->getHandValue() == highCard ) {
      winningPlayers.push_back(player);
    } else { 
      losingPlayers.push_back(player);
  }

  if (winningPlayers.size() > 1) { cout << "THERE WAS A TIE!\n"; }

  for ( int j = 0; j < winningPlayers.size() ; j++ ) {
    cout << winningPlayers[j]->getName() << " won with a hand of " << winningPlayers[j]->getHandValue() << endl;
    winningPlayers[j]->setWins( winningPlayers[j]->getWins() + 1 );
  }
  for ( int j = 0; j < losingPlayers.size() ; j++ ) {
    losingPlayers[j]->setLoses( losingPlayers[j]->getLoses() + 1 );
  }
  }
}

void Table::final_tally(){
  for (int i = 0; i < table1.getPlayers(); i++){
    Player* player = table1.players[i];
    cout << "Player: " << player->getName() << " ";
    cout << "won " << player->getWins() << " times and lost ";
    cout << player->getLoses() << " times.\n";
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
bool Player::isHuman() {
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

