//============================================================================
// Assignment		: ECE 3220: Final Project
// Authors			: Joel Abshier, Kyle Deppe, Tsiania Hughes
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Encounter.h"
#include "Exceptions.h"

using namespace std;

void setupCharacters(Character **, Character **);
void runGame();
void newGame(Character **, Character **);
void playGame(Character *, Character *, int * , EncounterList *, unsigned int = 0 );
void displayInstructions();
void saveGame( int turn, Character * player1, Character *player2 ) throw ( fileNotOpened );
void loadGame( unsigned int * turn, Character ** player1, Character ** player2 ) throw ( fileNotOpened );

string Choice(string &choiceString) throw ( bad_input );


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
	unsigned int resTurn = 0;

	Character * player1 = NULL, *player2 = NULL;
	EncounterList * encounters = new EncounterList();

	while ( gameState != -1 )
	{
		//Main menu state
		if( gameState == 0 )
		{
			try
			{
				choiceString = Choice(choiceString);
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
					try
					{
						loadGame( &resTurn, &player1, &player2 );
						playGame( player1, player2, &gameState, encounters, resTurn );
						gameState = 1;
					}
					catch( ... )
					{
						gameState = 3;
					}
					break;
				case 3:
					displayInstructions();
					break;
				case 4:
					gameState = 3;
					break;
			}

		}
		//This is the playing game state of the game
		else if ( gameState == 1 )
		{
			//This is where all the gameplay actually takes place
			playGame( player1, player2, &gameState, encounters );

			//End of turn
			cout << endl << "Another Turn Completed" << endl <<
					"Press <ENTER> to continue or type (Q)UIT to save and exit." << endl;

			//Get String for Next Turn. IF it's quit, then save and quit, otherwise go to next turn.
			string nextTurn;
			cout << ">> ";
			getline(cin, nextTurn);
			cout << endl;

			if( (nextTurn == "QUIT") || (nextTurn == "Q") || (nextTurn == "quit") || (nextTurn == "q") )
			{
				gameState = 2;
			}

		}
		//Player Died Gamestate
		else if ( gameState == 2 )
		{
			if( ( player1->getHealth() == 0 ) || ( player1->getSupplies() == 0 ) )
			{
				cout << "Player 2 won!" << endl;
			}
			else if( ( player2->getHealth() == 0 ) || ( player2->getSupplies() == 0 ) )
			{
				cout << "Player 1 won!" << endl;
			}
			gameState = -1;
		}
		//WIN GAME state
		else if ( gameState == 3 )
		{

			cout << endl << "Thanks for playing Project Zombie!" << endl;
			//TODO: Add cake. There will be cake.
			gameState = -1;
		}
	}

	//When all is lost...
	delete( player1 );
	delete( player2 );
}

void saveGame( int turn, Character * player1, Character *player2 ) throw ( fileNotOpened )
{
	string fileName = "save.dat";

	//Create new file input stream
	ofstream write;
	write.exceptions ( ofstream::failbit | ofstream::badbit );

	try
	{
		write.open( fileName );

		//Write the turn number to the filw
		write << turn << endl;

		//Create references os that we can use an operator
		Character &p1 = *player1;
		Character &p2 = *player2;

		//Write the data for each player to the file
		write << p1;
		write << p2;

		write.close();
	}
	catch ( ifstream::failure & e ) {
		//The file could not be read
		std::cerr << "Exception opening/reading/closing file\n";
		cout << e.what() << endl;
	}
	catch(...)
	{
		std::cerr << "File Could Not Be Opened!\n";
	}

}

void loadGame( unsigned int * turn, Character ** player1, Character ** player2 ) throw ( fileNotOpened )
{

	cout << endl << "Loading Game." << endl;

	string fileName = "save.dat";

	//Create new file input stream
	ifstream read;
	read.exceptions ( ifstream::failbit | ifstream::badbit );

	try
	{
		read.open( fileName );

		read >> *turn;

		//Create a new Player 1 and populate data
		Character * save1 = new Character();
		Character * save2 = new Character();

		read >> *save1;
		read >> *save2;

		read.close();

		cout << "Loaded Players" << endl;
		//save1->printPlayerData();
		//save2->printPlayerData();

		*player1 = save1;
		*player2 = save2;

	}
	catch ( ifstream::failure & e ) {
		//The file could not be read
		std::cerr << "Exception opening/reading/closing file\n";
		cout << e.what() << endl;
		throw fileNotOpened();
	}
	catch(...)
	{
		std::cerr << "File Could Not Be Read!\n";
		throw fileNotOpened();
	}

	cout << "Game Loaded!\n" << endl;

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

	cout << endl  << endl << endl << endl;;
}

void playGame( Character * player1, Character * player2, int * gameState, EncounterList * encounters, unsigned int resTurn )
{


	static unsigned int gameTurn = resTurn;

	//Start Turn Message
	cout << "You've survived to turn: " << gameTurn + 1 << endl << endl << endl << endl << endl;

	//Player 1 Turn
	cout << "<PLAYER 1>" << endl;
	player1->showStory( gameTurn );
	//Player 1's Random Encounter
	encounters->doEncounter( player1 );

	//Player 2 Turn
	cout << "<PLAYER 2>" << endl;
	player2->showStory( gameTurn );
	encounters->doEncounter( player2 );

	//IF PLAYERS ARE DEAD
	if( ( player1->getHealth() == 0 ) || ( player1->getSupplies() == 0 ) )
	{
		cout << "Player 1 has died. Player 2 wins!" << endl;
		*gameState = 3;
	}
	if( ( player2->getHealth() == 0 ) || ( player2->getSupplies() == 0 ) )
	{
		cout << "Player 2 has died. Player 1 wins!" << endl;
		*gameState = 3;
	}

	++gameTurn;

	if( gameTurn == 10 )
	{
		//Player 1 Final Story
		cout << "<PLAYER 1>" << endl;
		player1->showStory( gameTurn );

		//Player 2 Final Story
		cout << "<PLAYER 2>" << endl;
		player2->showStory( gameTurn );

		//Set gamestate to the ending state!
		*gameState = 3;
	}

	cout << endl << endl;

	saveGame( gameTurn, player1, player2 );

}

void displayInstructions()
{
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

string Choice(string &choiceString) throw (bad_input)
{
	cout << endl << "Please select an option: "
		<< endl << "1. Play Game"
		<< endl << "2. Load Game"
		<< endl << "3. See Instructions"
		<< endl << "4. Exit"
		<< endl << ">> ";

	getline(cin, choiceString);

	if( (choiceString != "1") && (choiceString != "2") && (choiceString != "3") && (choiceString != "4") )
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

	cout << endl << "Press <ENTER> to exit.";
	getline(cin, buffer);

	cout << endl << endl << "EXITING PROJECT ZOMBIE" << endl;

	return EXIT_SUCCESS;
}
