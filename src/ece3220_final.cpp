//============================================================================
// Assignment		: ECE 3220: Final Project
// Authors			: Joel Abshier, Kyle Deppe, Tsiania Hughes
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Characters/Character.h"

using namespace std;

//Some Prototypes
void setupCharacters(Player **, Player **);
void runGame();
void newGame(Player **, Player **);
void playGame(Player **, Player **);
void displayInstructions();

int choice();
string mainMenuChoice(string &choiceString);
string player1CharacterChoice(string &choiceString);
string player2CharacterChoice(string &choiceString, int characterPlayer1);


/*
 * In this method we can build the characters.
 * 		Build as follows: Character name( STRING Name, INT Health (0-100), INT Supplies (0-10), INT Luck (0-100) )
 * Add story elements to appear on turns.
 * 		Build as follows: .addStory( INT turnNum, STRING story )l
 */
void setupCharacters(Player ** player1, Player ** player2)
{
	string choiceString = "0";
	int characterPlayer1 = 0, characterPlayer2 = 0;

	cout << endl << "<PLAYER 1>";
	choiceString = player1CharacterChoice(choiceString);
	characterPlayer1 = stoi(choiceString);

	cout << endl << "<PLAYER 2>";
	choiceString = player2CharacterChoice(choiceString, characterPlayer1);
	characterPlayer2 = stoi(choiceString);

	Player *NewPlayer1 = new Player(characterPlayer1);
	Player *NewPlayer2 = new Player(characterPlayer2);

	*player1 = NewPlayer1;
	*player2 = NewPlayer2;

	/*
	Character * DoctorRivera = new Character("Dr. Rivera", 75, 10, 25);
	DoctorRivera->addStory(0, "After escaping the University of Missouri, you hopped into your trusty Corvette and head on your journey towards safety");
	DoctorRivera->addStory(5, "Story Arc #2 on turn 5.");

	Character * lilPupper = new Character("Lil' Pupper", 100, 0, 100);

	Add story elements to appear on turns.
	Build as follows: .addStory( INT turnNum, STRING story )
	*/
}

void runGame()
{
	string choiceString = "0";
	int state = 0, menuChoice = 0;
	Player *player1 = NULL, *player2 = NULL;

	while (1)
	{
		choiceString = mainMenuChoice(choiceString);
		menuChoice = stoi(choiceString);

		if (menuChoice == 1) {
			state = 1;
			newGame(&player1, &player2);
			playGame(&player1, &player2);
			break;
		}
		else if (menuChoice == 2) {
			displayInstructions();
		}
		else if (menuChoice == 3) {
			state = -1;
			break;
		}
		else {
			cout << endl << "Error. Try again." << endl;
		}
	}

	// Free the allocated memory.
	delete(player1);
	delete(player2);
}

void newGame(Player ** player1, Player ** player2)
{
	string buffer = "";
	cout << endl << "Creating a new game..." << endl;

	setupCharacters(player1, player2);

	cout << endl << endl << endl << "<PLAYER 1>";
	(**player1).printPlayerData();
	cout << endl << "<PLAYER 2>";
	(**player2).printPlayerData();

	cout << endl << "Press <ENTER> to initiate Project Zombie.";
	getline(cin, buffer);
}

void playGame(Player **player1, Player **player2) {
	cout << endl << endl;

	cout << endl << "<PLAYER 1>";
	(**player1).turn1();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn1();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn2();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn2();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn3();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn3();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn4();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn4();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn5();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn5();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn6();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn6();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn7();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn7();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn8();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn8();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn9();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn9();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn10();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	cout << endl << "<PLAYER 2>";
	(**player2).turn10();
	(**player1).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}

	(**player1).displayEpilogue();
	(**player2).displayEpilogue();
}

void displayInstructions() {
	cout << endl << "Instructions:"
		<< endl << "The world has been overrun by zombies. Last night a radio broadcast announced that"
		<< endl << "there's a safe haven in San Diego, California. Now, all of the survivors in America"
		<< endl << "are heading west. In the beginning the players will choose a character to be"
		<< endl << "assigned health, supplies, and luck. During the game the players' decisions"
		<< endl << "impact their stats, where decisions that match the character's personality"
		<< endl << "tend to favorably increase stats the most. The game ends when a player's health has"
		<< endl << "reached 0 or they both get to San Diego."
		<< endl;
}

int choice() {
	string choiceString = "";
	int choice = 0;

	cout << endl << ">> ";
	getline(cin, choiceString);

	while ((!choiceString._Equal("1")) && (!choiceString._Equal("2"))) {
		cout  << "Invalid choice. Select a choice by entering <1> or <2>" << endl << ">> ";
		getline(cin, choiceString);
	}

	choice = stoi(choiceString);

	return choice;
}

string mainMenuChoice(string &choiceString) {
	cout << endl << "Please select an option: "
		<< endl << "1. Play Game"
		<< endl << "2. See Instructions"
		<< endl << "3. Exit"
		<< endl << ">> ";

	getline(cin, choiceString);

	while (
		(!choiceString._Equal("1"))
		&& (!choiceString._Equal("2"))
		&& (!choiceString._Equal("3"))
		) {

		cout << endl << "Invalid choice. Select a valid option:"
			<< endl << "1. Play Game"
			<< endl << "2. See Instructions"
			<< endl << "3. Exit"
			<< endl << ">> ";

		getline(cin, choiceString);
	}

	return choiceString;
}

string player1CharacterChoice(string &choiceString) {
	cout << endl << "Please select a character:"
		<< endl << "1. Arnold Cooper - Military"
		<< endl << "2. Clark Kent - Lawyer"
		<< endl << ">> ";

	getline(cin, choiceString);

	while (
		(!choiceString._Equal("1"))
		&& (!choiceString._Equal("2"))
		) {

		cout << endl << "Invalid choice. Select a valid option:"
			<< endl << "1. Arnold Cooper - Military"
			<< endl << "2. Clark Kent - Lawyer"
			<< endl << ">> ";

		getline(cin, choiceString);
	}

	return choiceString;
}

string player2CharacterChoice(string &choiceString, int characterPlayer1) {
	cout << endl << "Please select a character:"
		<< endl << "1. Arnold Cooper - Military"
		<< endl << "2. Clark Kent - Lawyer"
		<< endl << ">> ";

	getline(cin, choiceString);

	while (
		(
		(!choiceString._Equal("1"))
			&& (!choiceString._Equal("2"))
			)
		|
		(stoi(choiceString) == characterPlayer1)
		) {

		cout << endl << "Invalid choice. Select a valid option (You can't be the same character as Player 1):"
			<< endl << "1. Arnold Cooper - Military"
			<< endl << "2. Clark Kent - Lawyer"
			<< endl << ">> ";

		getline(cin, choiceString);
	}

	return choiceString;
}

int main()
{
	string buffer = "";

	srand(time(NULL));
	cout << "PROJECT ZOMBIE" << endl << endl << "Welcome to Project Zombie";

	runGame();

	cout << endl << endl << "Press <ENTER> to exit.";
	getline(cin, buffer);

	cout << endl << endl << "EXITING PROJECT ZOMBIE" << endl;

	return EXIT_SUCCESS;
}
