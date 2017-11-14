#pragma once

#ifndef CHARACTERS_CHARACTER_H_
#define CHARACTERS_CHARACTER_H_

#include <string>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

class Character {
protected:
	string name;
	int health;		//A number between 0-100
	int supplies;	//A number between 0-100
	int luck;		//A number between 0-100 that increases the likelyhood of passing checks
	std::map<int, string> mainStory;		// I didn't use this. It might be useful but it seems like we can just hard code our stories.
											// (See Character.cpp)
public:
	// Character();
	Character(int choice);
	Character( string _name, int _health, int _supplies, int _luck );
	virtual ~Character();

	void printPlayerData();

	int getLuck();
	int getHealth();
	int getSupplies();
	int getTurn();
	string getName();

	void addHealth(int number);				// Input a negative number for subtraction. Auto sets to 0 or 100 for extreme values.
	void addSupplies(int number);
	void addLuck(int number);
	void showStory( int turnNumber );

	void addStory(int turn, string story);
};



/*class Player : public Character {
private:
	int characterNumber;
	int currentChoice;
	int prevChoice;
	vector<int> prevChoices;
	bool loseGame = 0;
protected:
public:
	Player(int choice);

	bool isLost() { return loseGame; }
	int getLastChoice() { return prevChoices[prevChoices.size() - 1]; }
	void addChoice(int newChoice);

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
};*/

class CharacterList
{
	private:
		vector <Character*> list;
		void setupCharacters();
	protected:
	public:
		CharacterList();
		Character* chooseCharacter();
};

#endif /* CHARACTERS_CHARACTER_H_ */

