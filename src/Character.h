#pragma once

#ifndef CHARACTERS_CHARACTER_H_
#define CHARACTERS_CHARACTER_H_

#include <string>
#include <map>
#include <iostream>
#include <fstream>
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
	Character() {}
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

	friend std::ostream& operator<<(std::ostream & os, const Character & player )
	{
		cout << "Saving" << endl;
		os << player.name << '\n';
		os << player.health << '\n';
		os << player.luck << '\n';
		os << player.supplies << '\n';
		return os;
	}

	friend std::istream& operator>>(std::istream & is, Character & player)
	{
		is >> player.name;
		is >> player.health;
		is >> player.luck;
		is >> player.supplies;
		return is;
	}

};

class CharacterList
{
	private:
		vector <Character*> list;
		void setupCharacters();
		int charChoice( string choice ) throw( int );
	protected:
	public:
		CharacterList();
		Character* chooseCharacter();
		void displayCharacters();
};

#endif /* CHARACTERS_CHARACTER_H_ */

