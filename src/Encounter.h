/*
 * Encounter.h
 *
 *  Created on: Nov 13, 2017
 *      Author: abshi
 */
#include <map>
#include "Character.h"
using namespace std;

#ifndef ENCOUNTER_H_
#define ENCOUNTER_H_

enum ResultType { health, supplies, readstory };

class Encounter
{
	private:
		string story;
		string choice;
		string passStory;
		string failStory;
		ResultType type;
		int passValue;
		int failValue;
		int odds;
		unsigned int rightChoice;

		void endEncounter( int value, Character * player );
		int validChoice( string choiceStr ) throw ( int );

	public:
		Encounter( string _story, string _choice, ResultType _type, int _passValue, int _failValue, string _passStory, string _failStory, int _odds, unsigned int rightChoice );
		void doEncounter( Character * player );
		virtual ~Encounter();
};

class EncounterList
{
private:
	vector <Encounter> encounters;
	void setupEncounters();
	void deleteEncounter();
	int randomEnc( unsigned int );
public:
	void doEncounter( Character * player );
	EncounterList();
};

#endif /* ENCOUNTER_H_ */
