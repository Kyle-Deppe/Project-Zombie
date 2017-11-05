/*
 * Character.cpp
 *
 *  Created on: Nov 4, 2017
 *      Author: abshi
 */

#include "Character.h"

Character::Character( string _name, int _health = 100, int _supplies = 10, int _luck = 50 ) {
	cout << _name << " constructor" << endl;
	name = _name;
	health = _health;
	supplies = _supplies;
	luck = _luck;
}

Character::~Character() {
	cout << name << " deconstructor" << endl;
}

void Character::printPlayerData()
{
	cout << "\n" << name << "'s Data" << endl
			<< "Health: " << health << endl
			<< "Supplies: " << supplies << endl
			<< "Luck: " << luck << endl;
}

int Character::getLuck()
{
	return luck;
}

int Character::getHealth()
{
	return health;
}

int Character::getSupplies()
{
	return supplies;
}

int Character::getTurn()
{
	return turnNumber;
}

void Character::addStory( int turn, string story )
{
	cout << "Adding Story to " << name << endl;
	mainStory.emplace( turn, story );
}
