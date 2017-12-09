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
void newGame(Character **, Character **, int * );
void playGame(Character *, Character *, int * , EncounterList *, int, unsigned int = 0);
void displayInstructions();
void saveGame( int turn, int save, Character * player1, Character *player2 ) throw ( fileNotOpened );
void loadGame( unsigned int * turn, int * save, Character ** player1, Character ** player2 ) throw ( fileNotOpened );
void deleGame( int save );

string Choice(string &choiceString) throw ( bad_input );


/*
 * setupCharacters
 * 		ARGS: Character **, Character **
 * 		RTRN: void
 * 		DESC: This function is designed simply to take in the two double-pointers to Character objects. It will creae an instance of the character
 * 		list, which will generate a all 6 Character objects. Then the chooseCharacter method will be called, returning the point to each character
 * 		selected
 */
void setupCharacters(Character ** player1, Character ** player2)
{
	CharacterList * charList = new CharacterList();					// This needs a delete() still

	cout << endl << "<PLAYER 1>";
	Character * NewPlayer1 =  charList->chooseCharacter();

	cout << endl << "<PLAYER 2>";
	Character * NewPlayer2 =  charList->chooseCharacter();

	*player1 = NewPlayer1;
	*player2 = NewPlayer2;

	delete charList;
}

/*
 * runGame
 * 		ARGS: none
 * 		RTRN: void
 * 		DESC: This is the function that is essentially designed to run the main menu and call the other functions/methods. It's the controller.
 * 		It has the following structure. The outer section is checking the gamestate, there are 4, a gamestate for the menu, a gamestate for playing the game,
 * 		a gamestate for the game ending, and a gamestate for winning/losing the game.
 * 		Within the gamestate there are other menus that will operate and other methods that will be called
 */
void runGame()
{
	string choiceString = "0";
	int gameState = 0;
	int menuChoice = 0;
	int saveSel = 0;
	unsigned int resTurn = 0;

	//Create pointers for the two character objects
	Character * player1 = NULL, *player2 = NULL;

	//At the start of every game a fresh list of encounters will be generated
	EncounterList * encounters = new EncounterList();

	//If the gamestate is not in ending mode, run the application
	while ( gameState != -1 )
	{
		//Main menu state
		if( gameState == 0 )
		{
			//Validate that a proper choice has been made
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

			/*
			 * The menu options:
			 * 1. Start a new game
			 * 2. Load a game (this also runs the first turn with playGame
			 * 3. Display instructions/backstory
			 * 4. Exit the game
			 */
			switch( menuChoice )
			{
				case 1:
					gameState = 1;
					newGame( &player1, &player2, &saveSel );
					break;
				case 2:
					try
					{
						//Load the save file, this method will put data in each pointer's value
						loadGame( &resTurn, &saveSel, &player1, &player2 );

						//Run the first turn of the game from here, as the game will not begin until there is another loop.
						playGame( player1, player2, &gameState, encounters, saveSel, resTurn );

						//Set the gamestate to the playing game state
						gameState = 1;
					}
					catch( ... )
					{
						gameState = 3;
					}
					break;
				case 3:
					//Call the method to show instructions
					displayInstructions();
					break;
				case 4:
					//End the game
					gameState = 3;
					break;
			}

		}
		//This is the playing game state of the game
		else if ( gameState == 1 )
		{
			//This is where all the gameplay actually takes place
			playGame( player1, player2, &gameState, encounters, saveSel );

			//End of turn
			cout << endl << "Another Turn Completed" << endl <<
					"Press <ENTER> to continue or type (Q)UIT to save and exit." << endl;

			//Get String for Next Turn. IF it's quit, then save and quit, otherwise go to next turn.
			string nextTurn;
			cout << ">> ";
			getline(cin, nextTurn);
			cout << endl;

			//If they choose to quit, set the gamemode ot shutdown
			if( (nextTurn == "QUIT") || (nextTurn == "Q") || (nextTurn == "quit") || (nextTurn == "q") )
			{
				gameState = 2;
			}

		}
		//Player Died Gamestate
		else if ( gameState == 2 )
		{
			gameState = -1;
		}
		//WIN GAME state
		else if ( gameState == 3 )
		{

			//Delete the save
			deleGame( saveSel );

			//Say Goodbye!
			cout << endl << "Thanks for playing Project Zombie!" << endl;
			//TODO: Add cake. There will be cake.
			gameState = -1;

		}
	}

	//When all is lost...
	delete( player1 );
	delete( player2 );
	delete( encounters );

}

/*
 * saveGame
 * 		ARGS: int, int, Character *, Character *
 * 		RTRN: void
 * 		DESC: This function takes in most of the runtime data specific to each game (except for encounters) and writes them to a file
 * 		that is associated with the slot selected when playing the game.
 */
void saveGame( int turn, int save, Character * player1, Character *player2 ) throw ( fileNotOpened )
{
	//Build the file name
	string fileName = "slot" + to_string(save) + ".zom";
	//cout << "Saving " << fileName << endl;

	//Create new file input stream
	ofstream write;
	write.exceptions ( ofstream::failbit | ofstream::badbit );

	try
	{
		write.open( fileName );

		//Write the turn number to the file
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

/*
 * deleGame
 * 		ARGS: int
 * 		RTRN: void
 * 		DESC: This function simply deletes the file with the given number associated. This is called when the players finish the game
 */
void deleGame( int save )
{

	string fileName = "slot" + to_string( save ) + ".zom";
	remove( fileName.c_str() );

}

/*
 * saveExist
 * 		ARGS: string
 * 		RTRN: bool
 * 		DESC: This is a simply yes/no, utility function to check whether a file with the given name exists. It's used when checking save slots
 */
bool saveExist( string name )
{
	if ( ifstream( name ) )
	{
	     return true;
	}
	return false;
}

/*
 * loadGame
 * 		ARGS: unsigned int *, int *, Character **, Charcater **
 * 		RTRN: void
 * 		DESC: Very similar to the save function, this function takes in pointers to most of the game data, and instead of saving them to a file
 * 		with the associated slot number, it loads the data from that, if it exists.
 */
void loadGame( unsigned int * turn, int * save, Character ** player1, Character ** player2 ) throw ( fileNotOpened )
{

	//This is nice to know :)
	cout << endl << "Loading Game..." << endl;

	//Choose a save slot
	cout << "Which game would you like to load?\n" << endl;

	//For each save slot, check if there is a save that exists, and let the user know
	for( int i = 1; i <= 3; i++ )
	{
		string file = "slot" + to_string(i) + ".zom";
		if( saveExist( file ) )
		{
			cout <<  to_string(i) + ". Slot " + to_string(i) + " - SAVE EXISTS\n";
		}
		else
		{
			cout << to_string(i) +  ". Slot " + to_string(i) + " - EMPTY\n";
		}
	}

	//This next block of code is just recieving input from the user and putting that value in the saveSlot variable.
	string choiceString = "0";
	cout << ">> ";
	getline(cin, choiceString);

	//There are only three slots allowed. Make sure they picked one of those
	while( (choiceString != "1") && (choiceString != "2") && (choiceString != "3") )
	{
		cout << "Not a valid save slot. Try again: " << endl;
		getline(cin, choiceString);
	}

	//Change the saveslot for the current game
	*save = stoi( choiceString );
	string fileName = "slot" + to_string( *save ) + ".zom";


	//Create new file input stream
	ifstream read;
	read.exceptions ( ifstream::failbit | ifstream::badbit );

	//Try opening the file for reading
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

/*
 * newGame
 * 		ARGS: Character **, Character **, int *
 * 		RTRN: void
 * 		DESC: As the name would suggest, this function is called whenever the player starts a new game. At first it asks the player which save
 * 		slot they will be using. Then it continues to call the setupCharcters function so that each player can select their desired characters.
 * 		Lastly, and most importantly, it prints out one heck of a zombie!!!!
 */
void newGame(Character ** player1, Character ** player2, int * save )
{
	string buffer = "";
	cout << endl << "Creating a new game..." << endl;

	//Choose a save slot
	cout << "Which file would you like to save to?\n";

	//For each save slot, check if there is a save that exists, and let the user know
	for( int i = 1; i <= 3; i++ )
	{
		string file = "slot" + to_string(i) + ".zom";
		if( saveExist( file ) )
		{
			cout <<  to_string(i) + ". Slot " + to_string(i) + " - SAVE EXISTS\n";
		}
		else
		{
			cout << to_string(i) +  ". Slot " + to_string(i) + " - EMPTY\n";
		}
	}

	string choiceString = "0";
	cout << ">> ";
	getline(cin, choiceString);
	while( (choiceString != "1") && (choiceString != "2") && (choiceString != "3") )
	{
		cout << "Not a valid save slot. Try again: " << endl;
		getline(cin, choiceString);
	}

	*save = stoi( choiceString );

	cout << "Slot " << *save << " selected!" << endl;


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

/*
 * playGame
 * 		ARGS: Charcter *, Character *, int *, EncounterList *, int, unsigned int
 * 		RTRN: void
 * 		DESC: Once again, as the naem might suggest, this function is where the main game happens. All of the action of encounters and turns
 * 		and making decisions is called from right here. At the start of each turn it will attempt to display the story for each player on this turn
 * 		and then try to give each player their encounter for this turn, from the list of encounters.
 * 		If, after the encounters, either players are dead (or both), the endgame gamestate will be triggered and the game will end
 * 		If the players reach turn 10, the game will output their last stories, and then end.
 * 		At the end of each turn, the game will save.
 */
void playGame( Character * player1, Character * player2, int * gameState, EncounterList * encounters, int save, unsigned int resTurn )
{

	static unsigned int gameTurn = resTurn;

	//Start Turn Message
	cout << "You've survived to turn: " << gameTurn + 1 << "\n\n" << endl;

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
		return;
	}
	else if( ( player2->getHealth() == 0 ) || ( player2->getSupplies() == 0 ) )
	{
		cout << "Player 2 has died. Player 1 wins!" << endl;
		*gameState = 3;
		return;
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
	else
	{

		saveGame( gameTurn, save, player1, player2 );

	}

	cout << endl << endl;

}

/*
 * displayInstructions
 * 		ARGS: none
 * 		RTRN: void
 * 		DESC: This is a simple function to display some instructions for the game and some backstory.
 */
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

/*
 * Choice
 * 		ARGS: string
 * 		RTRN string
 * 		DESC: This is the function that runs the main menu of the game. It outputs the options and then does error checking until the user
 * 		selects a proper option.
 */
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

/*
 * main
 * 		DESC: The all important main function!! This function calls runGame() and then asks the user to hit enter once the game ends...
 */
int main(void)
{
	string buffer = "";

	srand(time(NULL));
	cout << "PROJECT ZOMBIE" << endl << endl << "Welcome to Project Zombie";

	//LAUNCH PROJECT ZOMBIE!!!!!
	runGame();

	//Pressing enter says goodbye forever!!!
	cout << endl << "Press <ENTER> to exit.";
	getline(cin, buffer);

	cout << endl << endl << "EXITING PROJECT ZOMBIE" << endl;

	return EXIT_SUCCESS;
}
