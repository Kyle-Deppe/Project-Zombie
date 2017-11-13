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
string player1CharacterChoice(string &choiceString);
string player2CharacterChoice(string &choiceString, int characterPlayer1);


/*
 * In this method we can build the characters.
 * 		Build as follows: Character name( STRING Name, INT Health (0-100), INT Supplies (0-10), INT Luck (0-100) )
 * Add story elements to appear on turns.
 * 		Build as follows: .addStory( INT turnNum, STRING story )l
 */
void setupCharacters(Character ** player1, Character ** player2)
{
	string choiceString = "0";
	int characterPlayer1 = 0;
	int characterPlayer2 = 0;

	cout << endl << "<PLAYER 1>";
	choiceString = player1CharacterChoice(choiceString);
	characterPlayer1 = stoi(choiceString);

	cout << endl << "<PLAYER 2>";
	choiceString = player2CharacterChoice(choiceString, characterPlayer1);
	characterPlayer2 = stoi(choiceString);

	/*
	 * Setup the Doctor Rivera Character
	 * 		Build as follows: Name, Health, Supplies, Luck
	 * Add story elements to appear on turns.
	 * 		Build as follows: .addStory( INT turnNum, STRING story )l
	 */

	Character * DoctorRivera = new Character("Dr. Rivera", 75, 10, 25);
	DoctorRivera->addStory(0, "After escaping the University of Missouri, you hopped into your trusty Corvette and head on your journey towards safety");
	DoctorRivera->addStory(5, "Story Arc #2 on turn 5.");

	Character * lilPupper = new Character("Lil' Pupper", 100, 0, 100);


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
	int menuChoice = 0;
	string choiceString = "0";

	/*
	 * Game States
	 * -1. Exit Game
	 * 0. Main Menu
	 * 1. Playing the Game
	 */

	 //MAIN GAME LOOP!
	while (state != -1)
	{
		if (state == 0)
		{
			choiceString = mainMenuChoice(choiceString);
			menuChoice = stoi(choiceString);

			switch (menuChoice)
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

		if (state == 1)
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
	cout << endl << "Creating a new game!" << endl;

	//Setup Characters
	Character * p1 = NULL;
	Character * p2 = NULL;

	setupCharacters(&p1, &p2);

	cout << "Print Character Data" << endl;
	p1->printPlayerData();
	p2->printPlayerData();

	//Delete Characters
	cout << "\nDeconstructors" << endl;
	delete(p1);
	delete(p2);
}

string mainMenuChoice(string &choiceString) {
	cout << endl << "Welcome to Project Zombie"
	<< endl << "Please select an option: "
	<< endl << "1. New Game"
	<< endl << "2. Load Game"
	<< endl << "3. Help"
	<< endl << "4. Exit"
	<< endl << ">> ";

	getline(cin, choiceString);

	while (
		(!choiceString._Equal("1"))
		&& (!choiceString._Equal("2"))
		&& (!choiceString._Equal("3"))
		&& (!choiceString._Equal("4"))
		) {

		cout << endl << "Invalid choice. Select a valid option:"
		<< endl << "1. New Game"
		<< endl << "2. Load Game"
		<< endl << "3. Help"
		<< endl << "4. Exit"
		<< endl << ">> ";

		getline(cin, choiceString);
	}

	return choiceString;
}

string player1CharacterChoice(string &choiceString) {
	cout << endl << "Please select a character:"
		<< endl << "1. Dr. Rivera - Ingenious Professor"
		<< endl << "2. Clark Kent - Lawyer"
		<< endl << "3. Smith Cooper - Military"
		<< endl << ">> ";

	getline(cin, choiceString);

	while (
		(!choiceString._Equal("1"))
		&& (!choiceString._Equal("2"))
		&& (!choiceString._Equal("3"))
		) {

		cout << endl << "Invalid choice. Select a valid option:"
			<< endl << "1. Dr. Rivera - Ingenious Professor"
			<< endl << "2. Clark Kent - Lawyer"
			<< endl << "3. Smith Cooper - Military"
			<< endl << ">> ";

		getline(cin, choiceString);
	}

	return choiceString;
}

string player2CharacterChoice(string &choiceString, int characterPlayer1) {
	cout << endl << "Please select a character:"
		<< endl << "1. Dr. Rivera - Ingenious Professor"
		<< endl << "2. Clark Kent - Lawyer"
		<< endl << "3. Smith Cooper - Military"
		<< endl << ">> ";

	getline(cin, choiceString);

	while (
		((!choiceString._Equal("1"))
		&& (!choiceString._Equal("2"))
		&& (!choiceString._Equal("3")))
		|
		(stoi(choiceString) == characterPlayer1)
		) {

		cout << endl << "Invalid choice. Select a valid option (You can't be the same character as Player 1):"
			<< endl << "1. Dr. Rivera - Ingenious Professor"
			<< endl << "2. Clark Kent - Lawyer"
			<< endl << "3. Smith Cooper - Military"
			<< endl << ">> ";

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
