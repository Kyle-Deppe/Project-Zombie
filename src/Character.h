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

	//These are operator overloads for when this object is written to a file. This will make it so that the data for the character will be written
	friend std::ostream& operator<<(std::ostream & os, const Character & player )
	{
		os << player.name << '\n';
		os << player.health << '\n';
		os << player.luck << '\n';
		os << player.supplies << '\n';
		return os;
	}

	//These are operator overloads for when this object is loaded from a file. This willl load each line of the file into this object.
	friend std::istream& operator>>(std::istream & is, Character & player)
	{
		string readName;
		getline( is, readName );
		getline( is, player.name, '\n' );
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

