#include "Character.h"


Character::Character( string _name, int _health = 100, int _supplies = 10, int _luck = 50 ) {
	name = _name;
	health = _health;
	supplies = _supplies;
	luck = _luck;
}

Character::~Character()
{
}

void Character::printPlayerData()
{
	cout << endl << name << "'s Stats" << endl
			<< "Health: " << health << endl
			<< "Supplies: " << supplies << endl
			<< "Luck: " << luck << endl;
}

int Character::getLuck()
{
	return luck;
}

int Character::getHealth()
{
	return health;
}

int Character::getSupplies()
{
	return supplies;
}

string Character::getName()
{
	return name;
}

void Character::showStory( int turnNumber )
{
	std::map<int, string>::const_iterator iter;

	for ( iter = mainStory.begin(); iter != mainStory.end(); iter++ )
	{
		if( iter->first == turnNumber )
		{
			cout << "Story:" << iter->second << "\n" << endl;
			return;
		}
	}

}

void Character::addHealth(int number)
{
	if ((health + number) < 0)
	{
		health = 0;
	}
	else if ((health + number) > 100)
	{
		health = 100;
	}
	else
	{
		health = health + number;
	}
}
void Character::addSupplies(int number) {
	if ((supplies + number) < 0) {
		supplies = 0;
	}
	else if ((supplies + number) > 100) {
		supplies = 100;
	}
	else {
		supplies = supplies + number;
	}
}
void Character::addLuck(int number) {
	if ((luck + number) < 0) {
		luck = 0;
	}
	else if ((luck + number) > 100) {
		luck = 100;
	}
	else {
		luck = luck + number;
	}
}

void Character::addStory( int turn, string story )
{
	//Add story to map
	mainStory.emplace( turn, story );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


CharacterList::CharacterList()
{
	setupCharacters();
}

void CharacterList::setupCharacters()
{
	//Here is where we can write all of the charcter information, and we'll only have to do it once

	//Basic constructor calling. The one you setup is totally cool too.
	Character * arnoldCooper = new Character( "Arnold", 50 + (rand() % 41), 35 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( arnoldCooper );

	Character * clarkKent = new Character( "Clark", 50 + (rand() % 41), 35 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( clarkKent );

	Character * drRivera = new Character( "Luis Rivera", 50 + (rand() % 41), 35 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( drRivera );

	Character * lilPupper = new Character( "Lil' Pupper", 50 + (rand() % 41), 35 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( lilPupper );

	Character * abigailWillow = new Character( "Abigail", 50 + (rand() % 41), 35 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( abigailWillow );

	Character * darwinArnold = new Character( "Darwin", 50 + (rand() % 41), 35 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( darwinArnold );


	//Basically, right here we can add story elements into the game.
	/*
	 * FORMAT:
	 * (name).addStory( TURN_NUMBER, STORY );
	 *
	 * HERE'S THE IMPORTANT THIS:
	 * 	Not every turn needs a story. These are the unique story elements for each character, but each encounter also includes some story specific
	 * 	to that encounter.
	 */

	//ARNOLD'S STORIES!
	arnoldCooper->addStory(0, "You are Arnold Cooper, a member of the United States Marines. Sitting at your desk you listen to the Radio"
			"as it tells you about how San Diego is safe from the pandemic. That's all you need to hear. You pack your bags,"
			" keeing in mind that your truck is out of gas and you need to pack lightly."
	);
	arnoldCooper->addStory(10, "A story for turn 10");

	//CLARK KENT'S STORIES
	clarkKent->addStory(0, "You are Clark Kent, a lawyer in New York City. Everyone outside is scrambling to get indoors as the zombies "
			"spread throughout the city. You're just sipping on some coffee waiting for your private chopper to arrive."
	);

	//LUIS RIVERA'S STORIES
	drRivera->addStory(0, "You are Dr. Rivera, an ingenious professor in Missouri.");

	//LIL' PUPPER'S STORIES
	lilPupper->addStory( 0, "You are lil' pupper! You're the cutest 'lil guy in town <3, but underneath that fluffy coat of fur, you have vicious, survival skills.");
	lilPupper->addStory( 4, "The zombie apocolypse seems completely wonderful to you! As the jolly 'lil doggy you are, you trot along over the hills towards Sanctuary." );
	lilPupper->addStory( 10, "You've made it so far! You yelp and bark with so much joy and reward yourself by having a good 'ol time chasing your 'lil tail!" );
	lilPupper->addStory( 13, "Although the zombie growls and delicious smells are alluring to you, you point your 'lil nose forward and push ahead, determined to wag your 'lil tail in safety once again!" );
	lilPupper->addStory( 15, "The smell of good 'ol Purina Puppy Chow (not a sponsor) fills your nostrils as you approach the gate to Sanctuary. You're welcomed in and the humans there love you."
			"\nFor weeks they can't seem to keep their hands off of you, and you love it! You wag your tail and relax day and night. Then one day "
			"as you're reclining by the fire butcher Doug comes over to play with you. He throws your toy over into his shop and you chase it down "
			"to bring back and make him proud. But as you go into the shop and start sniffing around, you hear the door close and Butcher Doug picks you up "
			"to cuddle. You're loving it as he scractes your ears and puts your chubby, puppy body on his table."
	);

	//ABIGAIL WILLOW'S STORIES
	abigailWillow->addStory(0, "You are Abigail Willow, a student at Westhall Elementary.");

	//DARNWIN ARNOLD'S STORIES
	darwinArnold->addStory(0, "You are Darwin Arnold, some weird survivalist/conspiracy theorist guy that Tsiania sucked at describing.");

}

Character* CharacterList::chooseCharacter()
{
	string choiceString = "0";
	cout << endl << "Please select a character:" << endl;
	displayCharacters();

	getline(cin, choiceString);
	unsigned int charSelect = 0;

	while( charSelect == 0 )
	{
		try
		{
			charSelect = charChoice( choiceString );
		}
		catch( ... )
		{
			cout << "Invalid choice. Try agin." << endl;
			displayCharacters();
			getline(cin, choiceString);
		}
	}

	--charSelect;

	Character * rtn = list[charSelect];
	list.erase( list.begin() + ( charSelect ) );

	return rtn;

}

int CharacterList::charChoice( string choice ) throw( int )
{
	if( choice.empty() )
	{
		throw 1;
	}

	if( !isdigit(choice[0]) )
	{
		throw 2;
	}

	unsigned int charNum = stoi( choice );

	if( charNum < 1 )
	{
		throw 3;
	}

	if( charNum > list.size() )
	{
		throw 4;
	}

	return charNum;
}

void CharacterList::displayCharacters()
{
	for( unsigned int i = 0; i < list.size(); i++ )
	{
	    std::cout << (i + 1) << ". " << list[i]->getName() << endl;
	}
}
