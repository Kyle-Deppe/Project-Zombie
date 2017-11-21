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

Encounter::Encounter( string _story, string _choice, ResultType _type, int _passValue, int _failValue, string _passStory, string _failStory, int _odds )
{
	story = _story;
	choice = _choice;
	type = _type;
	odds = _odds;
	passValue = _passValue;
	failValue = _failValue;
	passStory = _passStory;
	failStory = _failStory;
}


void Encounter::doEncounter( Character * player )
{

	//Show the story about this encounter
	cout << story << endl;

	//Show the options for the encounter
	cout << choice << endl;

	//Ask player for choice
	string choiceString;
	getline(cin, choiceString);
	unsigned int choiceNum = 0;

	while( choiceNum == 0 )
	{
		try
		{
			choiceNum = validChoice( choiceString );
		}
		catch( ... )
		{
			cout << "Invalid Choice. Try Again: " << endl;
			//Show the options for the encounter
			cout << choice << endl;
			getline(cin, choiceString);
		}
	}

	--choiceNum;

	//LOGIC
	if( player->getLuck() > odds )
	{
		//If they pass the encounter
		cout << passStory << endl;
		endEncounter( passValue, player );
	}
	else
	{
		//If they fail the encounter
		cout << failStory << endl;
		endEncounter( failValue, player );
	}

	cout << "\n\nPress ENTER to continue..." << endl;
	cin.ignore();


}

int Encounter::validChoice( string choiceStr ) throw ( int )
{
	if( choiceStr.empty() )
	{
		throw 1;
	}

	if( !isdigit(choiceStr[0]) )
	{
		throw 2;
	}

	unsigned int choice = stoi( choiceStr );

	if( choice < 1 )
	{
		throw 3;
	}

	if( choice > 2 )
	{
		throw 4;
	}

	return choice;
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
		"You're a monster.",
		"Good choice :)",
		25
	);

	Encounter bridge = Encounter(
		"You reach a bridge that gave out. About to turn around, you notice the side walls of the bridge are intact. Do you: ",
		"\n1. Go across the bridge anyways. It's going to be dark soon.\n2. Turn around and go the long way. The bridge might crumble.",
		health,
		0,
		-1,
		"Luckily, you got across the bridge safely.",
		"You barely make it across the bridge, but accidentally drop your water over the side.",
		75
	);

	Encounter woods = Encounter(
			"Looking back to where you came from, you see movement in the woods. You leave quickly! Once far enough away you're far away enough, you stop and take a rest. Do you eat a snack?",
			"\n1. Yes, I just biked for hours and need more energy!\n2. No. I need to conserve my food in case there's none in the next town over.",
			health,
			10,
			-5,
			"You eat some and heal up.",
			"Your stomach starts to growl and you feel sick from hunger.",
			80
	);

	encounters.push_back( puppy );
	encounters.push_back( bridge );
	encounters.push_back( woods );

}

void EncounterList::doEncounter( Character * player )
{

	try
	{
		int encNum = randomEnc( encounters.size() );
		Encounter encounter = encounters[encNum];
		encounter.doEncounter( player );
		encounters.erase( encounters.begin() + encNum );
	}
	catch( int & e )
	{
		//No Encounter FOUND!
		cout << "Somehow the list of encounters became empty. FATAL ERROR" << endl;
	}

}

int EncounterList::randomEnc( unsigned int n )
{

	if( n < 1 )
	{
		throw -1;
	}
	unsigned int f = ( rand() % n );
	return f;

}

