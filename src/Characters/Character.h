#pragma once

#ifndef CHARACTERS_CHARACTER_H_
#define CHARACTERS_CHARACTER_H_

#include <string>
#include <map>
#include <iostream>

using namespace std;

class Character {
protected:
	string name;
	int turnNumber = 20;
	int health;		//A number between 0-100
	int supplies;	//A number between 0-100
	int luck;		//A number between 0-100 that increases the likelyhood of passing checks
	std::map<int, string> mainStory;

public:
	// Character();
	Character(int choice);
	virtual ~Character();

	void printPlayerData();

	int getLuck();
	int getHealth();
	int getSupplies();
	int getTurn();

	void addHealth(int number);		// Enter a negative number for subtraction.
	void addSupplies(int number);
	void addLuck(int number);
	void nextTurn() { --turnNumber; }

	void addStory(int turn, string story);
};

class Player : public Character {
private:
	int characterNumber;
	bool loseGame = 0;
	int *prevChoices;
protected:
public:
	Player(int choice);
	bool isLost() { return loseGame; }

	void turn1();
	void turn2();
	void turn3();
	void turn4();
	void turn5();
	void turn6();
	void turn7();
	void turn8();
	void turn9();
	void turn10();

	void displayEpilogue();
};

#endif /* CHARACTERS_CHARACTER_H_ */
