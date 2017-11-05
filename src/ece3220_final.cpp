//============================================================================
// Name        : ECE 3220: Final Project
// Author      : Joel Abshier, Kyle Depp, Tsiania Hughes
// Version     : 0.0.1
//============================================================================

#include <iostream>
#include "Characters/Character.h"
using namespace std;

/*
 * In this method we can build the characters.
 * 		Build as follows: Character name( STRING Name, INT Health (0-100), INT Supplies (0-10), INT Luck (0-100) )
 * Add story elements to appear on turns.
 * 		Build as follows: .addStory( INT turnNum, STRING story )l
 */
void setupCharacters( Character ** player1, Character ** player2 )
{

	cout << "Setting up Characters" << endl;

	/*
	 * Setup the Doctor Rivera Character
	 * 		Build as follows: Name, Health, Supplies, Luck
	 * Add story elements to appear on turns.
	 * 		Build as follows: .addStory( INT turnNum, STRING story )l
	 */
	Character * DoctorRivera = new Character( "Dr. Rivera", 75, 10, 25 );
		DoctorRivera->addStory( 0, "After escaping the University of Missouri, you hopped into your trusty Corvette and head on your journey towards safety" );
		DoctorRivera->addStory( 5, "Story Arc #2 on turn 5." );
	Character * lilPupper = new Character( "Lil' Pupper", 100, 0, 100 );


	/*
	 * TODO: Do the selection of characters in here
	 */

	//THIS IS TEMPORARY
	*player1 = DoctorRivera;
	*player2 = lilPupper;

}


int main()
{

	cout << "The Ultimate Final Project" << endl;

	//Setup Characters
	Character * p1 = NULL;
	Character * p2 = NULL;

	setupCharacters( &p1, &p2 );

	cout << "Print Character Data" << endl;
	p1->printPlayerData();
	p2->printPlayerData();

	cout << "\nDeconstructors" << endl;
	delete( p1 );

	return 0;
}
