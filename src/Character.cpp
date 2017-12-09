#include "Character.h"


/*
 * Character constructor!
 * To make a character you have to put in a name, and the other values are optional
 */
Character::Character( string _name, int _health = 100, int _supplies = 10, int _luck = 50 )
{
	name = _name;
	health = _health;
	supplies = _supplies;
	luck = _luck;
}

Character::~Character()
{
}

/*
 * printPlayerData
 * 		This is just a nifty method used at the start of the game to display the random stats
 */
void Character::printPlayerData()
{
	cout << endl << name << "'s Stats" << endl
			<< "Health: " << health << endl
			<< "Supplies: " << supplies << endl
			<< "Luck: " << luck << endl;
}

//Return the luck
int Character::getLuck()
{
	return luck;
}

//Return the health
int Character::getHealth()
{
	return health;
}

//Return the supplies
int Character::getSupplies()
{
	return supplies;
}

//Return the name
string Character::getName()
{
	return name;
}

/*
 * showStory
 * 		This is a simple method that takes in the turn number and checks to see if there is an existing record in the mainStory map. If there is, it gets printed
 */
void Character::showStory( int turnNumber )
{
	std::map<int, string>::const_iterator iter;

	//Check through the entire map
	for ( iter = mainStory.begin(); iter != mainStory.end(); iter++ )
	{
		//If there is a record with a key equal to the turn number
		if( iter->first == turnNumber )
		{
			//Show that story!
			cout << iter->second << "\n" << endl;
			return;
		}
	}

}

/*
 * addHealth
 * 		A setter used for adding and subtracting health from the player. This will not let the health exceed 100 or go below 0
 */
void Character::addHealth(int number)
{
	//If health would be below 0 with addition
	if ((health + number) < 0)
	{
		health = 0;
	}
	//If health would be above 100 with addition
	else if ((health + number) > 100)
	{
		health = 100;
	}
	else
	{
		health = health + number;
	}
}

/*
 * addSupplies
 * 		A setter used for adding and subtracting supplies from the player. This will no let the supplies exceed 100 or go below 0
 */
void Character::addSupplies(int number)
{
	//If supplies would be below 0 with addition
	if ((supplies + number) < 0)
	{
		supplies = 0;
	}
	//If supplies would be greater than 100
	else if ((supplies + number) > 100)
	{
		supplies = 100;
	}
	else
	{
		supplies = supplies + number;
	}
}

/*
 * addLuck
 * 		A setter used for adding and subtracking luck from the player. This will not let the luck exceed 100 or go below 0
 */
void Character::addLuck(int number)
{
	//If the luck would be less than 0
	if ((luck + number) < 0)
	{
		luck = 0;
	}
	//If the luck would be greater than 100
	else if ((luck + number) > 100)
	{
		luck = 100;
	}
	else
	{
		luck = luck + number;
	}
}

/*
 * addStory
 * 		A simple method used for adding a story element associated with a key (turn) to the map
 */
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

CharacterList::~CharacterList()
{
	int size = list.size();
	int i = 0;

	for (i = 0; i < size; i++) {
		delete list[i];
	}
}

void CharacterList::setupCharacters()
{
	//Here is where we can write all of the charcter information, and we'll only have to do it once

	// Make sure to write a delete() for all of these.
	Character * arnoldCooper = new Character( "Arnold", 50 + (rand() % 41), 50 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( arnoldCooper );

	Character * clarkKent = new Character( "Clark", 50 + (rand() % 41), 50 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( clarkKent );

	Character * drRivera = new Character( "Luis Rivera", 50 + (rand() % 41), 50 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( drRivera );

	Character * lilPupper = new Character( "Lil' Pupper", 50 + (rand() % 41), 50 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( lilPupper );

	Character * abigailWillow = new Character( "Abigail", 50 + (rand() % 41), 50 + (rand() % 41), 35 + (rand() % 41) );
	list.push_back( abigailWillow );

	Character * darwinArnold = new Character( "Darwin", 50 + (rand() % 41), 50 + (rand() % 41), 35 + (rand() % 41) );
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
	arnoldCooper->addStory(0, "You are Arnold Cooper, a member of the United States Marines.");
	arnoldCooper->addStory(2, "Your emergency phone rings and it attracts another zombie. You run away until you feel safe. Looking at the caller ID, you get ticked off because it's an automated call from the IRS asking for taxes.");
	arnoldCooper->addStory(4, "You've reached a door and it's locked. Unfolding your handy dandy swiss army knife, you kneel down to unlock it. Crap, you don't remember how to do this. So you kick the door the heck down and walk on in.");
	arnoldCooper->addStory(7, "Reaching a rural area, there's a rustle in the woods. Ignoring it, you keep going. But the rustling doesn't stop. Panicking, you break into a sprint. "
							" Whatever is after you, it's right on your heels. You keep running until you trip and fall on your face. The creature trips over you and breaks its own neck on the fall. Well that was close.");
	arnoldCooper->addStory(10, "You've reached salvation. Walking right up to the base, you get greeted at the front gate and walk on in. Welcome to San Diego.");



	//CLARK KENT'S STORIES
	clarkKent->addStory(0, "You are Clark Kent, a journalist from New York City.");
	clarkKent->addStory(2, "You look up to the sky, and see a bright light. It crashes into the ground next to you. That's weird. You ignore it and keep on going.");
	clarkKent->addStory(4, "Nighttime arrives. Reaching an urban area, you walk slowly, searching for a place to find food. When suddenly, BAM, some weird guy"
						   " in a bat suit comes out of no where and slams his fist into your face. How rude. You snap his neck and keep looking for food."
						   " It has never occurred to you before, but you realize you're kind of ridiculously strong.");
	clarkKent->addStory(7, "A zombie steps into your path. You blink a little more firmly than usual and he disintegrates at your feet. And everything behind him"
						   " for about ten feet is a path of destruction. Woops. Now, back to whatever I was doing...");
	clarkKent->addStory(10, "You look up ahead and see your destination: San Diego. Taking a step forward, you remember something. You're freaking Superman!"
							" This realization elates you with energy. Taking a deep breath, you prepare for what you must do. Grabbing the ground firmly with"
							" two hands, you pull and stretch it apart. Muscles aching, you pull harder and harder with the force of a billion men until, finally, the Earth"
							" breaks in half. That oughta do it. Content, you fly out into space to go live with some other alien race that's better than humanity.");



	//LUIS RIVERA'S STORIES
	drRivera->addStory(0, "You are Dr. Rivera, an ingenious professor in Missouri. After finishing up some important research on the Zombie Apocolypse you start your journey towards Sanctuary, with the information ni hand to develop a cure.");
	drRivera->addStory(3, "Unphased by the troubles of the journey, you pull out your laptop and begin developing lectures for the classes you're hoping to teach, once you reach Sanctuary. " );
	drRivera->addStory(5, "Lying down for another night of rest you hear a noise creeping towards you. Turning switftly and arming yourself, you look up to see a figure moving towards you. As the moonlight reaches its "
						  "face you finally recognize the face of none other than Tushar! He comes forward and greets you with a hug and the two of you sit down for a night of debating whether or not Eclipse is a good IDE."	);
	drRivera->addStory(8, "Nearing your journey's end you start to feel very excited! You're going to save the world. The cure to this disease is in the palm of your hand!" );
	drRivera->addStory(10, "In the distance you can see the faint outline of a wall! There it is! You move forward as fast as you can until you reach the wall. You're welcomed inside and you begin your new life developing computers in this world without electricity. "
							"The new R-Box 9001 features state of the art features like binary. Running of treadmill power, your new machines push the colony into the best tech of the 20th century! "
							"You feel like a hero as you finally finish the vaccination and begin distributing it to all of Sanctuary...\n\nTwo months later everyone has been vaccinated. Unfortunately, the proper sanitization wasn't used and most of the colony died from infection. Leaving only a humans left to be the end of humanity.");


	//LIL' PUPPER'S STORIES
	lilPupper->addStory( 0, "You are lil' pupper! You're the cutest 'lil guy in town <3, but underneath that fluffy coat of fur, you have vicious, survival skills.");
	lilPupper->addStory( 2, "The zombie apocolypse seems completely wonderful to you! As the jolly 'lil doggy you are, you trot along over the hills towards Sanctuary." );
	lilPupper->addStory( 4, "You've made it so far! You yelp and bark with so much joy and reward yourself by having a good 'ol time chasing your 'lil tail!" );
	lilPupper->addStory( 7, "Although the zombie growls and delicious smells are alluring to you, you point your 'lil nose forward and push ahead, determined to wag your 'lil tail in safety once again!" );
	lilPupper->addStory( 10, "The smell of good 'ol Purina Puppy Chow (not a sponsor) fills your nostrils as you approach the gate to Sanctuary. You're welcomed in and the humans there love you."
			"\nFor weeks they can't seem to keep their hands off of you, and you love it! You wag your tail and relax day and night. Then one day "
			"as you're reclining by the fire butcher Doug comes over to play with you. He throws your toy over into his shop and you chase it down "
			"to bring back and make him proud. But as you go into the shop and start sniffing around, you hear the door close and Butcher Doug picks you up "
			"to cuddle. You're loving it as he scratches your ears and puts your chubby, puppy body on his table."
	);



	//ABIGAIL WILLOW'S STORIES
	//ABIGAIL WILLOW'S STORIES
	abigailWillow->addStory(0, "You are Abigail Willow, a student at Westhall Middle School. You're 13 years old carrying only whats in your backpack and your phone."
		"The Zombies don't wait for you to get home before they attack. You escape the building and its chaos. From a crashed car next to the building you hear from the radio about San Dieg0 "
		"trying to save the human race. Without a doubt start your adventure to San Diego.");
	abigailWillow->addStory(2, "As you take a breather you see a boy running towards you shouting. 'Run!!!' he says and soon you see why, a horde of zombies make there way around the corner he ran from."
		"You follow close behind him until you both take shelter in a house that was left open. 'I'm Alex' he says once we caught our breath. Afterward you both head you seperate ways. You only ddepend on yourself");
	abigailWillow->addStory(4, "You are halfway there, it's only been a few weeks but you can feel how little there is left of humanity. You are seeing less stragglers and the ones who you do see you avoid."
		"People are desperate");
	abigailWillow->addStory(7, "You soon realize how bleak and dangerous the world has become. You never really stopped to think on your parents or friends (or fake friends) who could all be dead now. "
		"You refuse to travel at night time, wild animals are becoming braver as they realize humans aren't the top predators anymore, and humans have fallen back to the old justice ways.");
	abigailWillow->addStory(10, "At the rising dawn you see the San Diego with people guarding the perimeter. With a sigh of relief you come out of hiding and walk slowly towards the gates trying to hold back tears."
		"As the gates open to you and a military personel walks out to you saying 'Welcome' and you can't help but cry. 'I'm actually alive, I made it here to safety...'");
	


	//DARNWIN ARNOLD'S STORIES
	darwinArnold->addStory(0, "You are Darwin Arnold, you are a  survivalist contradictory to your name. No one believed in your learning and now they will all regret it hahaha. This is the time to prove yourself"
		"This is your time to shine. You aren't at your safe place where your wife is since you were delivering some cargo as a truck driver. But you will be there in the end, surviving.");
	darwinArnold->addStory(2,"'Oh my gosh this world sucks' you think to yourself. You thought you were prepared but now that it's happening, you are questioning everything you know. You start writing the field guid to zombies "
		"to make time go by faster whenever you're stopping for the night when the light is allowed");

	darwinArnold->addStory(4, "You witness a large community of humans get torn to shreds by zombies and your sanity starts to decrease. You thought you could escape this reality at night in your sleep but you only recieve nightmares. "
	"You continue your journey home to your wife...");
	if (darwinArnold->getHealth() <= 30)
		darwinArnold->addStory(7, "You can no longer sleep and you are constantly hearing voices whether they are screams of pain, groans of zombies, or your inner demon. You are contemplating giving up now...");
	else
		darwinArnold->addStory(7, "You do basic work outs to get you tired so you can gain rest and remind yourself of your wife. This works and you gain some of your sanity back. The journey has been long but you are holding on");
	
	darwinArnold->addStory(10, "You see your secluded home a few hundred meters away. Sprinting the remainder of the way you feel your hope rise seeing majority of the animals still looking healthy. You run to the fence and shake the bell"
		" longing to see your wife. You see her face appear from inside the lookout tower and you can help but yell her name 'Susan! I'm Here!'");
}

/*
 * chooseCharacter
 * 		This is the method that gets called during the game setup for each character to select a character from the list. Once a character is
 * 		selected, they have to be removed from the list
 */
Character* CharacterList::chooseCharacter()
{
	//Display instruction
	string choiceString = "0";
	cout << endl << "Please select a character:" << endl;

	//Output a list of all remaining Characters
	displayCharacters();

	cout << ">> ";
	getline(cin, choiceString);
	unsigned int charSelect = 0;

	//This simple validates whether they have chosen a charcacter in the list
	while( charSelect == 0 )
	{
		try
		{
			//If a valid character has been selected
			charSelect = charChoice( choiceString );
		}
		catch( ... )
		{
			cout << endl << "Invalid choice. Try again." << endl;
			displayCharacters();
			cout << ">> ";
			getline(cin, choiceString);
		}
	}

	//Subtract one from the value, because the map goes from 0-5 and the user has optiosn 1-6
	--charSelect;

	//Save a pointer to the selected character to be returned
	Character * rtn = list[charSelect];

	//Remove the pointer from the list of characters that can be selected
	list.erase( list.begin() + ( charSelect ) );

	return rtn;

}

/*
 * charChoice
 * 		Simply input validation for when the player is selecting a character.
 */
int CharacterList::charChoice( string choice ) throw( int )
{
	//If nothing was input
	if( choice.empty() )
	{
		throw 1;
	}

	//If they did not input an integer
	if( !isdigit(choice[0]) )
	{
		throw 2;
	}

	//Convert string to integer
	unsigned int charNum = stoi( choice );

	//If the value is less than 1
	if( charNum < 1 )
	{
		throw 3;
	}

	//If they input a number greater than the length of the list (must be invalid)
	if( charNum > list.size() )
	{
		throw 4;
	}

	return charNum;
}

/*
 * displayCharacters
 * 		This is a simple method for displaying the name of every character in the list, with a number associated. This is sued for selecting characaters
 */
void CharacterList::displayCharacters()
{
	for( unsigned int i = 0; i < list.size(); i++ )
	{
	    std::cout << (i + 1) << ". " << list[i]->getName() << endl;
	}
}
