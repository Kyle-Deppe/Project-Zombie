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
		string endStory;
		ResultType type;
		int passValue;
		int failValue;
		int odds;

		void endEncounter( int value, Character * player );

	public:
		Encounter( string _story, string _choice, ResultType _type, int _passValue, int _failValue, int _odds );
		void doEncounter( Character * player );
		virtual ~Encounter();
};

class EncounterList
{
private:
	map <int, Encounter> encounters;
	void deleteEncounter();
public:
	void doEncounter();
};

#endif /* ENCOUNTER_H_ */
