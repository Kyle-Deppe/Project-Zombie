/*
 * Encounter.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: abshi
 */

#include "Encounter.h"

Encounter::~Encounter() {
	// TODO Auto-generated destructor stub
}

Encounter::Encounter( string _story, string _choice, ResultType _type, int _passValue, int _failValue, string _passStory, string _failStory, int _odds, unsigned int _rightChoice = 0 )
{
	story = _story;
	choice = _choice;
	type = _type;
	odds = _odds;
	rightChoice = _rightChoice;
	passValue = _passValue;
	failValue = _failValue;
	passStory = _passStory;
	failStory = _failStory;
}


void Encounter::doEncounter( Character * player )
{

	//Show the story about this encounter
	cout << story << endl;

	//Show the options for the encounter
	cout << choice << endl;

	//Ask player for choice
	string choiceString;
	getline(cin, choiceString);
	unsigned int choiceNum = 0;

	while( choiceNum == 0 )
	{
		try
		{
			choiceNum = validChoice( choiceString );
		}
		catch( ... )
		{
			cout << "Invalid Choice. Try Again: " << endl;
			//Show the options for the encounter
			cout << choice << endl;
			getline(cin, choiceString);
		}
	}

	--choiceNum;

	/*
	 * This is the part of the application where a "die will be rolled" to determine whether or not the player will pass the check.
	 * To pass the check the player needs to have a die roll greater greater than the odds variable for each encounter
	 * This is the process:
	 * 1. Roll a die between 1-100
	 * 2. Add +10 if the player chose the best choice on the encounter
	 * 3. Add a modifier 1-15 if based on the players luck.
	 */

	//1. Roll a die between 1-100
	int dieRoll = ( rand() % 100 );

	//2. Add +10 if the player chose the best choice on the encounter
	if( choiceNum == rightChoice )
	{
		cout << "Good choice bonus!" << endl;
		dieRoll += 10;
	}

	//3. Add a modifier 1-15 if based on the players luck.
	dieRoll += ( player->getLuck() / 100 ) * 15;

	//Since the odds of passing are increased (between 1-100) for each encounter and we're using a minimum number for passing, we need to subtract the odds from 100
	int minRoll = 100 - odds;

	//FOR TESTING: Print the roll and minmum roll
	//cout << "You rolled  " << dieRoll << endl;
	//cout << "You needed  " << minRoll << endl;

	//Finally, check if the player has a high enough roll to pass the encounter
	if( dieRoll >= minRoll )
	{
		//If they pass the encounter
		cout << passStory << endl;
		endEncounter( passValue, player );
	}
	else
	{
		//If they fail the encounter
		cout << failStory << endl;
		endEncounter( failValue, player );
	}

	cout << "\n\nPress ENTER to continue..." << endl;
	cin.ignore();


}

int Encounter::validChoice( string choiceStr ) throw ( int )
{
	if( choiceStr.empty() )
	{
		throw 1;
	}

	if( !isdigit(choiceStr[0]) )
	{
		throw 2;
	}

	unsigned int choice = stoi( choiceStr );

	if( choice < 1 )
	{
		throw 3;
	}

	if( choice > 2 )
	{
		throw 4;
	}

	return choice;
}

void Encounter::endEncounter( int value, Character * player )
{
	switch( type )
	{
		case health:
			player->addHealth( value );
			cout << "You have " << player->getHealth() << " health remaining." << endl;
			break;
		case supplies:
			player->addSupplies( value );
			cout << "You have " << player->getSupplies() << " supplies remaining." << endl;
			break;
		case readstory:
			break;
	}
}

EncounterList::EncounterList()
{
	setupEncounters();
}

void EncounterList::setupEncounters()
{

	/*
	 * THESE ARE THE ENCOUNTERS:
	 * This whole section is where is big list of all the game's random encounters are constructured. There's a really specific format to be followe,
	 * but adding encounters will be extremely easy for us this way.
	 *
	 * Here's an example of how to define an encounter:
	 * Encounter <varname> = Encounter(
	 * 		"This is the introduction story",
	 * 		"1. Choice 1\n2.Choice 2.",
	 * 		<supplies, health, or story>,
	 * 		PASS_VALUE (int),
	 * 		FAIL_VALUE (int),
	 * 		"This is the story they read if they pass the encounter",
	 * 		"This is the story they read if they fail the encounter",
	 * 		ODDS OF PASSING THE ENCOUNTER (int between 0-100),
	 * 		CHOICE that gives them the bonus chance of passing (int either 0 or 1)
	 * 	);
	 *
	 */

	Encounter bridge = Encounter(
		"You reach a bridge that gave out. About to turn around, you notice the side walls of the bridge are intact. Do you: ",
		"\n1. Go across the bridge anyways. It's going to be dark soon.\n2. Turn around and go the long way. The bridge might crumble.",
		supplies,
		0,
		-10,
		"Luckily, you make it to the other side of bridge safely.",
		"You barely make it to the other side, but accidentally drop your water over the side.",
		75,
		1
	);

	Encounter woods = Encounter(
			"Looking back to where you came from, you see movement in the woods. You leave quickly! Once far enough away you're far away enough, you stop and take a rest. Do you eat a snack?",
			"\n1. Yes, I just biked for hours and need more energy!\n2. No. I need to conserve my food in case there's none in the next town over.",
			health,
			10,
			-5,
			"You eat some and heal up.",
			"Your stomach starts to growl and you feel sick from hunger.",
			80,
			1
	);

	Encounter randZombie = Encounter(
			"Behind you, you start to hear footsteps drawing closer. Your turn around quickly and see a zombie making his way to you. He's too close to escape. Do you...",
			"\n1. Punch at his face and try to take him out? \n2. Try to trip him so you can make an escape?",
			health,
			0,
			-20,
			"You manage to take the zombie down and get away safely!",
			"You have taken a bad bite, but the zombies appetite seems satisfied. You make your escape as he feasts.",
			40,
			2
	);

	Encounter ladder = Encounter(
			"You come across a lonely building that looks like it was held up by survivors at one point. On the roof you see what could be supplies. Do you...",
			"\n1. Climb the rusty ladder on the side of the building? \n2. Attempt to scale the wall?",
			supplies,
			10,
			-10,
			"You reach the top of the roof and are lucky enought to find some leftover supplies from the previous survivors.",
			"You try to climb up but the building begins to crumble and you fall, breaking some of your own supplies. Zombies are fast approaching, so you move on.",
			50,
			1
	);

	Encounter sleep = Encounter(
			"You're feeling too tired to move on and you need to rest. To your right you see a small crevice to hide in and to your left you see some trees you could climb in to sleep. Do you...",
			"\n1. Hide in the cave? Staying out of sight would be best! \n2. Climb the tree? nothing can reach you there.",
			supplies,
			0,
			-15,
			"You awaken, feeling refreshed, and gather your belongings.",
			"During the night some of your food was dragged away by animals. Nevertheless, you get up and move on.",
			30,
			1
	);

	Encounter falling = Encounter(
			"While crossing a bridge on the way to Santuary, it gives way and you slip. Hanging on by only a thread, do you...",
			"\n1. Reach up quickly before the wire snaps? \n2. Try to throw your gear up to lessen the weight?",
			health,
			-5,
			-20,
			"You manage to pull yourself up and continue on with only a few cut and bruises.",
			"Despite your best efforts, the wire snaps and you plunge into the water. You hit it hard and swallow a lot of water. Luckily, you manage to make it to the shore, but you're hurt badly.",
			40,
			2
	);

	Encounter drown = Encounter(
			"Zombies surround you on every side!!! The only way to go is through the river. Quickly looking for options, you see that you can...",
			"\n1. Swim. Those high-school classes better to pay off! \n2. Grab the log next to the river and try to float across! YOU CAN'T SWIM!!!",
			supplies,
			-5,
			-25,
			"Struggling for breath, you barely make it across the water. You lost a little gear to the water, but at least you're free of the zombies... \n\n...for now.",
			"You see the log sink down into the water from it's weight. You are pulled under by the current and find yourself down the river, free from the zombies, but missing a lot of your supplies!",
			70,
			1
	);

	Encounter car = Encounter(
			"You find an old car that seems broken down, but it has gas! Do you...",
			"\n1. Use your deus ex machina mechanic skills to fix that bad boy up for a faster ride? \n2. Kick it until it turns on",
			supplies,
			50,
			0,
			"Somehow, you manage to get the best rolling and you continue on!",
			"As expected, you fail. With a heavy heart, you continue on...",
			10,
			2
	);

	Encounter cake = Encounter(
			"You find cake. You must eat the cake. How will you eat the cake?",
			"\n1. Eat cake with fingers. \n2. Eat cake with face",
			health,
			-5,
			-10,
			"The cake is a lie.",
			"The cake is a lie.",
			50,
			1
	);

	Encounter fridge = Encounter(
			"You find an old fridge with food inside. It's not cold, but it looks like it's sealed. You decide to eat, but do you...",
			"\n1. Eat the yogurt? \n2. Eat the stew?",
			health,
			10,
			-10,
			"Luckily, you're able to digest the food, and except for some bad gas, it really makes you feel better!",
			"Eating old food wasn't your greatest idea... you suffer painful diarrhea for days",
			25,
			2
	);

	Encounter shrooms = Encounter(
			"While wandering along you stumble across a lovely patch of mushrooms to eat. You...",
			"\n1. Eat them raw? \n2. Roast them up first!",
			health,
			5,
			-15,
			"You eat the mushrooms and it reminds you of days past... yum :)",
			"Did you really just eat wild mushrooms? Wow... That was a bad move. POISoNED!",
			40,
			2
	);

	Encounter mizzou = Encounter(
			"On your way to Sanctuary, you stumble across the ruins of one of the greatest instituions that ever was..."
			"The University of Missouri. Looking at Naka Hall (or EBW because everyone is still calling it that) you decide to...",
			"\n1. Search the basement, that's where they're hiding the good stuff. \n2. Go upstairs! I bet Doctor Rivera has good tastes!",
			supplies,
			20,
			-5,
			"You're lucky enough to find some delicious snacks in the offices!",
			"You leave the building without a single useful bit of gear or food, and on your way out the door falls on you, because this university hates you.",
			60,
			2
	);

	Encounter puppy = Encounter(
			"In the shrubs in front of you, you hear some growling... Scared of what it might be, you ready yourself for a fight! From within the brush you see a dog emerge and charge towards you. Before you can even react, it is licking your nose. Do you...",
			"\n1. Scratch his ear and call him Ralph. \n2. Scratch his ear and call him Rover",
			health,
			5,
			-10,
			"This puppy is so thrilled at his new name! He makes you feel so happy and rejuvinated!",
			"Angry with the ugly name you gave him, the dog bites your little toe and runs away.",
			50,
			1
	);


	encounters.push_back( bridge );
	encounters.push_back( woods );
	encounters.push_back( randZombie );
	encounters.push_back( ladder );
	encounters.push_back( sleep );
	encounters.push_back( falling );
	encounters.push_back( drown );
	encounters.push_back( car );
	encounters.push_back( cake );
	encounters.push_back( fridge );
	encounters.push_back( shrooms );
	encounters.push_back( mizzou );
	encounters.push_back( puppy );

}

void EncounterList::doEncounter( Character * player )
{

	try
	{
		int encNum = randomEnc( encounters.size() );
		Encounter encounter = encounters[encNum];
		encounter.doEncounter( player );
		encounters.erase( encounters.begin() + encNum );
	}
	catch( int & e )
	{
		//No Encounter FOUND!
		cout << "Somehow the list of encounters became empty. FATAL ERROR" << endl;
	}

}

int EncounterList::randomEnc( unsigned int n )
{

	if( n < 1 )
	{
		throw -1;
	}
	unsigned int f = ( rand() % n );
	return f;

}

