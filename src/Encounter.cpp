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

//Basic encounter constructor. Almost everything is required because encounters have many unique parameters
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

/*
 * doEncounter
 * 	This method is where the player gets the story for an encounter and makes their decision on what to do. Then they will get an outcome depending
 * 	on their choice and a luck factor
 */
void Encounter::doEncounter( Character * player )
{

	//Show the story about this encounter
	cout << story << endl;

	//Show the options for the encounter
	cout << choice << endl << ">> ";

	//Ask player for choice
	string choiceString;
	getline(cin, choiceString);
	unsigned int choiceNum = 0;

	//Simply validate whether that number was valid
	while( choiceNum == 0 )
	{
		try
		{
			choiceNum = validChoice( choiceString );
		}
		catch( ... )
		{
			cout << "Invalid choice. Try again: " << endl;
			//Show the options for the encounter
			cout << choice << endl << ">> ";
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

	cout << "\n\n\n\nPress <ENTER> to continue...";
	string tempString;
	getline(cin, tempString);
	cout << endl;
}

/*
 * validChoice
 * 		A method for error checking the player's choice during an encounter
 */
int Encounter::validChoice( string choiceStr ) throw ( int )
{
	//If they didn't input anything
	if( choiceStr.empty() )
	{
		throw 1;
	}

	//If they didn't input an integer
	if( !isdigit(choiceStr[0]) )
	{
		throw 2;
	}

	//Get integer value from string
	unsigned int choice = stoi( choiceStr );

	//If they put in a number less than 1
	if( choice < 1 )
	{
		throw 3;
	}

	//If they input a number greater than 2
	if( choice > 2 )
	{
		throw 4;
	}

	return choice;
}

/*
 * endEncounter
 * 		This function handles the modifcation of stats and telling the player what they have remaining.
 */
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
		-30,
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
			-30,
			"You're feeling better already.",
			"You feel sick.",
			80,
			1
	);

	Encounter randZombie = Encounter(
			"Behind you, you start to hear footsteps drawing closer. Your turn around quickly and see a zombie making his way to you. He's too close to escape. Do you...",
			"\n1. Punch at his face and try to take him out? \n2. Try to trip him so you can make an escape?",
			health,
			0,
			-35,
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
			-40,
			"You reach the top of the roof and are lucky enought to find some leftover supplies from the previous survivors.",
			"You try to climb up but the building begins to crumble and you fall, breaking some of your own supplies. Zombies are fast approaching, so you move on.",
			50,
			1
	);

	Encounter sleep = Encounter(
			"You're feeling too tired to move on and you need to rest. To your right you see a small crevice to hide in and to your left you see some trees you could climb in to sleep. Do you...",
			"\n1. Hide in the cave? Staying out of sight would be best! \n2. Climb the tree? Nothing can reach you there.",
			supplies,
			0,
			-25,
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
			-30,
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
			-45,
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
			-25,
			"Somehow, you manage to get the best rolling and you continue on!",
			"As expected, you fail. With a heavy heart, you continue on...",
			10,
			2
	);

	Encounter cake = Encounter(
			"You find cake. You must eat the cake. How will you eat the cake?",
			"\n1. Eat cake with fingers. \n2. Eat cake with face",
			health,
			0,
			10,
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
			-30,
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
			-35,
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
			-35,
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
			-35,
			"This puppy is so thrilled at his new name! He makes you feel so happy and rejuvenated!",
			"Angry with the ugly name you gave him, the dog bites your little toe and runs away.",
			50,
			1
	);

	Encounter mother = Encounter(
			"In the distance you hear a growl... but this one is familiar. As the growl draws closer you can see the face becoming clearer. It's your zombified mother. As grumpy as aways, she staggers towards you, a little worse for wear. You still don't have the heart to let her go on, so you...",
			"\n1. Decide to cut her head off. \n2. Hit her with one blast of a shotgun.",
			health,
			0,
			-40,
			"Her head is gone. The nagging is gone. You're finally free.",
			"You hesitate just a moment to long and she gets one last bite down on you before you put an end to her. You've escaped that monster, but not without some damage.",
			25,
			2
	);

	Encounter gang = Encounter(
			"Before you can react, you are surrounded by a gang of survivor armed to the teeth, your only option is to talk your way out. You...",
			"\n1. Pretend that you don't speak English and hope for mercy. \n2. Offer them some of your best supplies to spare your life.",
			supplies,
			-10,
			-35,
			"The gang decides to have mercy on you and let's you go and only takes a few of your supplies",
			"The gang laughs in your face before stripping you of most of your possessions.",
			30,
			1
	);

	Encounter cpp = Encounter(
			"You find a computer that has information to help you get to sanctuary, but you have to write some C++ because. You...",
			"\n1. Write some classes because you're a boss? \n2. Write a rotate ellipse function very poorly?",
			health,
			0,
			-30,
			"You write the code and get the information you need!",
			"All this coding has been so taxing on your weak eyes...",
			75,
			2
	);

	Encounter survivors = Encounter(
			"The sound of an engine roars closer and closer to you as you duck for cover behind a rock. The vehicles stop "
			"right in front of you and several armed men and women emerge. They order you to come out. After considering running, you decide that "
			"surrendering is your best option. You come out and they greet you with a smile. You're welcomed to their camp for a night of rest.\n"
			"They are a group of survivors from that are trying to build their own colony in the North. They offer you some supplies, do you...",
			"\n1. Graciously accept the supplies? \n2. Try to convince them to give you even more",
			supplies,
			25,
			-35,
			"They decide to give you what they were offering and a little extra because you're a little extra ;)",
			"They changed their mind. You get mugged and beaten.",
			25,
			1
	);

	Encounter water = Encounter(
			"The thirst has been setting in and you know that you need to find some water soon. You find a small puddle and decide to drink the water. Do you...",
			"\n1. Try to filter it through a piece of cloth \n2. Drink the water as is",
			health,
			20,
			-30,
			"Thank goodness you got some water that was clean! You're feeling a little better",
			"The stale water wreaks havoc on your system and you fall dangerously ill.",
			20,
			1
	);

	Encounter child = Encounter(
			"As you make your way through the city, a little girl starts making her way towards you. You don't have the heart to kill the child. So you...",
			"\n1. Run away quickly and hope the girl doesn't move fast. \n2. Hide in a nearby building until she passes",
			supplies,
			0,
			-25,
			"You watch as the little creeps along slowly, luckily, not noticing you.",
			"The little girl makes eye contact with you, and to your surprise she moves like lightning. She attacks you and gets a bite in before you can put her down",
			55,
			2
	);

	Encounter store = Encounter(
			"In a small town you come across a convenient store. The windows are barred and the door is locked, but there are a lot of supplies inside. You're going to try to break in, do you...",
			"\n1. Go through the window. \n2. Try to crawl under the building",
			health,
			10,
			-40,
			"You manage to get inside and find some delicious Hostess (not a sponsor) snacks!",
			"While trying to break in, you cut yourself on some rust and develop tetanus!",
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
	encounters.push_back( mother );
	encounters.push_back( gang );
	encounters.push_back( cpp );
	encounters.push_back( survivors );
	encounters.push_back( water );
	encounters.push_back( child );
	encounters.push_back( store );

}

/*
 * doEncounter
 * 		This is the method that gets called from the playGame method to give each player an encounter. It will take in a player object, whose stats may
 * 		be modified and check. Then it selects an encounter from the list of encounters generatred on initialization.
 */
void EncounterList::doEncounter( Character * player )
{

	try
	{
		//Pick a random number from 0 to the size of the encounter list
		int encNum = randomEnc( encounters.size() );

		//Create a pointer to that encounter
		Encounter encounter = encounters[encNum];

		//Call the doEncounter method on that encounter
		encounter.doEncounter( player );

		//Erase that encounter from the list of encounters
		encounters.erase( encounters.begin() + encNum );
	}
	catch( int & e )
	{
		//No Encounter FOUND!
		cout << "Somehow the list of encounters became empty. FATAL ERROR" << endl;
	}

}

/*
 * randomEnc
 * 		This si a simple method for selecting an encounter from the list.It's passed an unsigned int that should be > 0. Then it randomly generates
 * 		and integer between 0 and the value passed. Then returns that value.
 */
int EncounterList::randomEnc( unsigned int n )
{

	if( n < 1 )
	{
		throw -1;
	}

	//Generate random int between 0-n
	unsigned int f = ( rand() % n );

	//Return int
	return f;

}

