//============================================================================
// Assignment		: ECE 3220: Final Project
// Authors			: Joel Abshier, Kyle Deppe, Tsiania Hughes
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Characters/Character.h"

using namespace std;

void setupCharacters(Player **, Player **);
void runGame();
void newGame(Player **, Player **);
void playGame(Player **, Player **);
void displayInstructions();

int choice();
string mainMenuChoice(string &choiceString);
string player1CharacterChoice(string &choiceString);
string player2CharacterChoice(string &choiceString, int characterPlayer1);


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

	cout << endl << endl << endl << "                  ////////////////////////////////////////////////////////";
	cout << endl << "                  /////   Press <ENTER> to initiate Project Zombie   /////";
	cout << endl << "                  ////////////////////////////////////////////////////////";
	getline(cin, buffer);

	cout << endl << endl << "                	              .~#########%%;~.";
	cout << endl << "                                     /############%%;`\\";
	cout << endl << "                                    /############%%;,;,\\";
	cout << endl << "                                   |#############;;;;.,.|";
	cout << endl << "                                   |###########%;;;;;.,.|";
	cout << endl << "                          XX       |##/~~\\####%;;;/~~\\;,|       XX";
	cout << endl << "                        XX..X      |#|  o  \\##%;/  o  |.|      X..XX";
	cout << endl << "                      XX.....X     |##\\____/##%;\\____/.,|     X.....XX";
	cout << endl << "                 XXXXX.....XX      \\#########/\\;;;;;;,, /      XX.....XXXXX";
	cout << endl << "                X |......XX%,.@      \\######/%;\\;;;;, /      @#%,XX......| X";
	cout << endl << "                X |.....X  @#%,.@     |######%%;;;;,.|     @#%,.@     X.....| X";
	cout << endl << "                X  \...X     @#%,.@    |# # # % ; ; ;,|   @#%,.@       X.../  X";
	cout << endl << "                 X# \.X        @#%,.@                  @#%,.@           X./  #";
	cout << endl << "                  ##  X          @#%,.@              @#%,.@             X   #";
	cout << endl << "                , \"# #X            @#%, .@          @#%, .@            X ##";
	cout << endl << "                   `###X             @#%,.@      @#%,.@             ####'";
	cout << endl << "                  . ' ###              @#%.,@  @#%,.@              ###`";
	cout << "                    . "; "                @#%.@#%,.@                ;\"` ' .";
	cout << endl << "                      '                    @#%,.@                   ,.";
	cout << endl << "                          ` ,            @#%,.@  @@                `";
	cout << endl << "                                          @@@  @@@ ";

	cout << endl  << endl << endl<< "                                      TYPE <Q> TO QUIT." << endl;;
}

void playGame(Player **player1, Player **player2) {
	cout << endl << endl;

	cout << endl << "<PLAYER 1>";
	(**player1).turn1();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		// We need to write what happens when a player loses.
		// (**player1).displayEpilogue();
		// (**player2).displayEpilogue();
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn1();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn2();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn2();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn3();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn3();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn4();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn4();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn5();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn5();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn6();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn6();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn7();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn7();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn8();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn8();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn9();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn9();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}


	cout << endl << "<PLAYER 1>";
	(**player1).turn10();
	(**player1).addChoice(choice());
	if ((**player1).isLost() == 1) {
		return;
	}
	if ((**player1).getLastChoice() == 3) {
		return;
	}

	cout << endl << "<PLAYER 2>";
	(**player2).turn10();
	(**player2).addChoice(choice());
	if ((**player2).isLost() == 1) {
		return;
	}
	if ((**player2).getLastChoice() == 3) {
		return;
	}

	// Stories for when the character wins
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
		<< endl << "reached 0 or both players get to San Diego."
		<< endl;
}

int choice() {
	string choiceString = "";
	int choice = 0;

	while (1) {
		cout << endl << ">> ";
		getline(cin, choiceString);

		while (
			(!choiceString._Equal("1"))
			&& (!choiceString._Equal("2"))
			&& (!choiceString._Equal("Q"))
			&& (!choiceString._Equal("q"))
			&& (!choiceString._Equal("Quit"))
			&& (!choiceString._Equal("quit"))
			) {
			cout << "Invalid choice. Select a choice by entering <1> or <2>" << endl << ">> ";
			getline(cin, choiceString);
		}

		if (choiceString._Equal("Q") | choiceString._Equal("q") | choiceString._Equal("Quit") | choiceString._Equal("quit")) {
			cout << endl << "Are you sure that you want to quit?"
				<< endl << "Type <Y> or <N>" << endl << ">> ";
			getline(cin, choiceString);
			while (
				(!choiceString._Equal("Y"))
				&& (!choiceString._Equal("y"))
				&& (!choiceString._Equal("Yes"))
				&& (!choiceString._Equal("yes"))
				&& (!choiceString._Equal("N"))
				&& (!choiceString._Equal("n"))
				&& (!choiceString._Equal("No"))
				&& (!choiceString._Equal("no"))
				) {
				cout << "Invalid choice. Select a choice by entering <Y> or <N>" << endl << ">> ";
				getline(cin, choiceString);
			}

			if (
				(choiceString._Equal("Y"))
				| (choiceString._Equal("y"))
				| (choiceString._Equal("Yes"))
				| (choiceString._Equal("yes"))
				) {
				return 3;
			}
			else {
				continue;
			}

		}
		else {
			break;
		}
	}
	choice = stoi(choiceString);

	cout << endl;
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
		// << endl << "3. Dr. Rivera - Ingenious Professor"
		// << endl << "4. Lil Pupper - Am Pupper"
		// << endl << "5. Abigail Willow - Elementary Student"
		// << endl << "6. Darwin Arnold - Survivalist"
		<< endl << ">> ";

	getline(cin, choiceString);

	while (
		(!choiceString._Equal("1"))
		&& (!choiceString._Equal("2"))
		// && (!choiceString._Equal("3"))
		// && (!choiceString._Equal("4"))
		// && (!choiceString._Equal("5"))
		// && (!choiceString._Equal("6"))
		) {

		cout << endl << "Invalid choice. Select a valid option:"
			<< endl << "1. Arnold Cooper - Military"
			<< endl << "2. Clark Kent - Lawyer"
			// << endl << "3. Dr. Rivera - Ingenious Professor"
			// << endl << "4. Lil Pupper - Am Pupper"
			// << endl << "5. Abigail Willow - Elementary Student"
			// << endl << "6. Darwin Arnold - Survivalist"
			<< endl << ">> ";

		getline(cin, choiceString);
	}

	return choiceString;
}

string player2CharacterChoice(string &choiceString, int characterPlayer1) {
	cout << endl << "Please select a character:"
		<< endl << "1. Arnold Cooper - Military"
		<< endl << "2. Clark Kent - Lawyer"
		// << endl << "3. Dr. Rivera - Ingenious Professor"
		// << endl << "4. Lil Pupper - Am Pupper"
		// << endl << "5. Abigail Willow - Elementary Student"
		// << endl << "6. Darwin Arnold - Survivalist"
		<< endl << ">> ";

	getline(cin, choiceString);

	while (
		(
		(!choiceString._Equal("1"))
			&& (!choiceString._Equal("2"))
			// && (!choiceString._Equal("3"))
			// && (!choiceString._Equal("4"))
			// && (!choiceString._Equal("5"))
			// && (!choiceString._Equal("6"))
			)
		|
		(choiceString._Equal(to_string(characterPlayer1)))
		) {

		cout << endl << "Invalid choice. Select a valid option (You can't be the same character as Player 1):"
			<< endl << "1. Arnold Cooper - Military"
			<< endl << "2. Clark Kent - Lawyer"
			// << endl << "3. Dr. Rivera - Ingenious Professor"
			// << endl << "4. Lil Pupper - Am Pupper"
			// << endl << "5. Abigail Willow - Elementary Student"
			// << endl << "6. Darwin Arnold - Survivalist"
			<< endl << ">> ";

		getline(cin, choiceString);
	}

	return choiceString;
}

int main(void)
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
