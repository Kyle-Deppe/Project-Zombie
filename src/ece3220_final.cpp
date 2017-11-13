//============================================================================
// Name        : ECE 3220: Final Project
// Author      : Joel Abshier, Kyle Depp, Tsiania Hughes
// Version     : 0.0.1
//============================================================================

#include <iostream>
#include "Characters/Character.h"
using namespace std;

//Some Prototypes
void setupCharacters(Character **, Character **);
void runGame();
void newGame();
string mainMenuChoice(string &choiceString);


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

void runGame()
{

	int state = 0;
	int choice = 0;
	string choiceString = "-1";

	/*
	 * Game States
	 * -1. Exit Game
	 * 0. Main Menu
	 * 1. Playing the Game
	 */

	//MAIN GAME LOOP!
	while( state !=  -1 )
	{
		if( state == 0)
		{

			cout << endl << "Welcome to Project Zombie" << endl;
			cout << "Please select an option: " << endl;
			cout << "1. New Game" << endl;
			cout << "2. Load Game" << endl;
			cout << "3. Help" << endl;
			cout << "4. Exit" << endl;
			cout << "> ";

			choiceString = mainMenuChoice(choiceString);
			choice = stoi(choiceString);

			switch( choice )
			{
				case 1:
					state = 1;
					newGame();
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					state = -1;
					break;
				default:
					cout << "That's not an option! Try again: " << endl;
					break;
			}
		}

		if( state == 1 )
		{
			cout << "TODO: Press Enter to exit..." << endl;
			cin.ignore();
			state = -1;
		}

	}

	cout << "Thanks for playing!" << endl;

}

void newGame()
{
	cout << "Creating a new game!" << endl;

	//Setup Characters
	Character * p1 = NULL;
	Character * p2 = NULL;

	setupCharacters( &p1, &p2 );

	cout << "Print Character Data" << endl;
	p1->printPlayerData();
	p2->printPlayerData();

	//Delete Characters
	cout << "\nDeconstructors" << endl;
	delete( p1 );
	delete( p2 );
}

string mainMenuChoice(string &choiceString) {
	getline(cin, choiceString);
	
	while (
		(!choiceString._Equal("1"))
		&& (!choiceString._Equal("2"))
		&& (!choiceString._Equal("3"))
		&& (!choiceString._Equal("4"))
		) {

		cerr << endl << "Invalid choice. Select a valid option:" << endl;
		cout << "1. New Game" << endl;
		cout << "2. Load Game" << endl;
		cout << "3. Help" << endl;
		cout << "4. Exit" << endl;
		cout << "> ";

		getline(cin, choiceString);
	}

	return choiceString;
}

int main()
{

	cout << "PROJECT ZOMBIE" << endl;

	runGame();

	return 0;
}
