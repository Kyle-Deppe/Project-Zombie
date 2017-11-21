//============================================================================
// Assignment		: ECE 3220: Final Project
// Authors			: Joel Abshier, Kyle Deppe, Tsiania Hughes
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Encounter.h"
#include "Exceptions.h"

using namespace std;

void setupCharacters(Character **, Character **);
void runGame();
void newGame(Character **, Character **);
void playGame(Character *, Character *, int * , EncounterList *  );
void displayInstructions();

string mainMenuChoice(string &choiceString) throw ( bad_input );


void setupCharacters(Character ** player1, Character ** player2)
{
	CharacterList * charList = new CharacterList();

	cout << endl << "<PLAYER 1>";
	Character * NewPlayer1 =  charList->chooseCharacter();

	cout << endl << "<PLAYER 2>";
	Character * NewPlayer2 =  charList->chooseCharacter();

	*player1 = NewPlayer1;
	*player2 = NewPlayer2;

}

void runGame()
{
	string choiceString = "0";
	int gameState = 0;
	int menuChoice = 0;

	Character * player1 = NULL, *player2 = NULL;
	EncounterList * encounters = new EncounterList();

	while ( gameState != -1 )
	{
		//Main menu state
		if( gameState == 0 )
		{
			try
			{
				choiceString = mainMenuChoice(choiceString);
			}
			catch( bad_input & e )
			{
				cout << e.what() << endl;
				choiceString = "0";
			}
			menuChoice = stoi(choiceString);

			switch( menuChoice )
			{
				case 1:
					gameState = 1;
					newGame( &player1, &player2 );
					break;
				case 2:
					displayInstructions();
					break;
				case 3:
					gameState = -1;
					break;
			}

		}
		//This is the playing game state of the game
		else if ( gameState == 1 )
		{
			//This is where all the gameplay actually takes place
			playGame( player1, player2, &gameState, encounters );

			//End of turn
			cout << "Another Turn Completed" << endl <<
					"Press <ENTER> to Continue or type (Q)UIT to save and exit." << endl;

			//Get String for Next Turn. IF it's quit, then save and quit, otherwise go to next turn.
			string nextTurn;
			getline(cin, nextTurn);

			if( (nextTurn == "QUIT") || (nextTurn == "Q") || (nextTurn == "quit") || (nextTurn == "q") )
			{
				gameState = 2;
			}

		}
		//Quitting state
		else if ( gameState == 2 )
		{
			/*TODO: SAVE THE GAME!!!*/
			gameState = -1;
		}
		//WIN GAME state
		else if ( gameState == 3 )
		{
			cout << "You've reached the end (for now)!" << endl;
			//TODO: Add cake. There will be cake.
			gameState = -1;
		}
	}

	//When all is lost...
	delete( player1 );
	delete( player2 );
}

void newGame(Character ** player1, Character ** player2)
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
	cout << endl << "                X  \\...X     @#%,.@    |# # # % ; ; ;,|   @#%,.@       X.../  X";
	cout << endl << "                 X# \\.X        @#%,.@                  @#%,.@           X./  #";
	cout << endl << "                  ##  X          @#%,.@              @#%,.@             X   #";
	cout << endl << "                , \"# #X            @#%, .@          @#%, .@            X ##";
	cout << endl << "                   `###X             @#%,.@      @#%,.@             ####'";
	cout << endl << "                  . ' ###              @#%.,@  @#%,.@              ###`";
	cout << endl << "                    . \"; \"                @#%.@#%,.@                ;\"` ' ." ;
	cout << endl << "                      '                    @#%,.@                   ,.";
	cout << endl << "                          ` ,            @#%,.@  @@                `";
	cout << endl << "                                          @@@  @@@ ";

	cout << endl  << endl << endl<< "                                      TYPE <Q> TO QUIT." << endl;;
}
void playGame( Character * player1, Character * player2, int * gameState, EncounterList * encounters )
{
	static unsigned int gameTurn = 0;

	//Start Turn Message
	cout << "Starting Turn: " << gameTurn << endl;

	//Player 1 Turn
	cout << "<PLAYER 1>" << endl;
	player1->showStory( gameTurn );
	//Player 1's Random Encounter
	encounters->doEncounter( player1 );

	//Player 2 Turn
	cout << "<PLAYER 2>" << endl;
	player2->showStory( gameTurn );
	encounters->doEncounter( player2 );

	++gameTurn;

	if( gameTurn > 8 )
	{
		//Set gamestate to the ending state!
		*gameState = 3;
	}

	cout << endl << endl;
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

string mainMenuChoice(string &choiceString) throw (bad_input)
{
	cout << endl << "Please select an option: "
		<< endl << "1. Play Game"
		<< endl << "2. See Instructions"
		<< endl << "3. Exit"
		<< endl << ">> ";

	getline(cin, choiceString);

	if( (choiceString != "1") && (choiceString != "2") && (choiceString != "3") )
	{
		throw bad_input();
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
