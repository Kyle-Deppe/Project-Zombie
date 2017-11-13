/*
 * Encounter.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: abshi
 */

#include "Encounter.h"

Encounter::~Encounter() {
	// TODO Auto-generated destructor stub
}

Encounter::Encounter( string _story, string _choice, ResultType _type, int _passValue, int _failValue, int _odds )
{
	story = _story;
	choice = _choice;
	type = _type;
	odds = _odds;
	passValue = _passValue;
	failValue = _failValue;
}


void Encounter::doEncounter( Character * player )
{

	//Show the story about this encounter
	cout << story << endl;

	//Show the options for the encounter
	cout << choice << endl;

	//Ask player for choice
	int choice;
	cin >> choice;

	//LOGIC
	if( player->getLuck() > odds )
	{
		//If they pass the encounter
		endEncounter( passValue, player );
	}
	else
	{
		//If they fail the encounter
		endEncounter( failValue, player );
	}

	cout << "\n\nPress ENTER to continue to next turn..." << endl;
	cin.ignore();

}

void Encounter::endEncounter( int value, Character * player )
{
	switch( type )
	{
		case health:
			player->addHealth( value );
			break;
		case supplies:
			player->addSupplies( value );
			break;
		case readstory:
			break;
	}
}
