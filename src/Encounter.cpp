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

EncounterList::EncounterList()
{
	setupEncounters();
}

void EncounterList::setupEncounters()
{
	Encounter puppy = Encounter(
			"You encounter a mean dog. Do you shoot it?",
			"1. Shoot Dog\n2. Keep dog as pet.",
			supplies,
			10,
			-10,
			25
	);
	encounters.push_back( puppy );
}

void EncounterList::doEncounter( Character * player )
{

	try
	{
		Encounter encounter = randomEnc( encounters.size() );
		encounter.doEncounter( player );
	}
	catch( int & e )
	{
		//No Encounter FOUND!
		cout << "Somehow the list of encounters became empty. FATAL ERROR" << endl;
	}

}

Encounter EncounterList::randomEnc( unsigned int n )
{

	unsigned int f = ( rand() % n );
	return encounters[f];

	throw -1;

}

