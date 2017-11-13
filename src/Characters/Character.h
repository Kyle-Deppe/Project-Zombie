/*
 * Character.h
 *
 *  Created on: Nov 4, 2017
 *      Author: abshi
 */
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
		int supplies;	//A number between 0-10
		int luck;		//A number between 0-100 that increases the likelyhood of passing checks
		std::map<int, string> mainStory;

	public:
		Character();
		Character(int choice);
		Character( string _name, int _health, int _supplies, int _luck );
		virtual ~Character();

		void printPlayerData();

		int getLuck();
		int getHealth();
		int getSupplies();
		int getTurn();

		void changeHealth( int damage );
		void changeSupplies( int supplies );
		void changeLuck( int luck );
		void nextTurn() { --turnNumber; }

		void addStory( int turn, string story );
};

#endif /* CHARACTERS_CHARACTER_H_ */
