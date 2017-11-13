#include "Character.h"

Character::Character(int choice) {
	// cout << "constructor" << endl;

	if (choice == 1) {
		name = "Arnold";				// Arnold Cooper
		health = 50 + (rand() % 41);
		supplies = 35 + (rand() % 41);
		luck = 35 + (rand() % 41);
	}
	else if (choice == 2) {
		name = "Clark";					// Clark Kent
		health = 50 + (rand() % 41);
		supplies = 35 + (rand() % 41);
		luck = 35 + (rand() % 41);
	}
	else if (choice == 3) {
		name = "Dr. Rivera";			// Dr. Rivera
		health = 50 + (rand() % 41);
		supplies = 35 + (rand() % 41);
		luck = 35 + (rand() % 41);
	}
	else if (choice == 4) {
		// name = ???                   // Lil Pupper ///////////////////////////////////////////////
		health = 50 + (rand() % 41);
		supplies = 35 + (rand() % 41);
		luck = 35 + (rand() % 41);
	}
	else if (choice == 5) {
		name = "Abigail";				// Abigail Willow
		health = 50 + (rand() % 41);
		supplies = 35 + (rand() % 41);
		luck = 35 + (rand() % 41);
	}
	else if (choice == 6) {
		name = "Darwin";				// Darwin Arnold
		health = 50 + (rand() % 41);
		supplies = 35 + (rand() % 41);
		luck = 35 + (rand() % 41);
	}
}

Character::~Character() {
	// cout << name << " deconstructor" << endl;
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

int Character::getTurn()
{
	return turnNumber;
}

void Character::addHealth(int number) {
	if ((health + number) < 0) {
		health = 0;
	}
	else if ((health + number) > 100) {
		health = 100;
	}
	else {
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
	cout << "Adding Story to " << name << endl;
	mainStory.emplace( turn, story );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Player::Player(int choice) : Character(choice) {
	characterNumber = choice;
};

void Player::turn1() {
	if (characterNumber == 1) {
		cout << endl << "You are Arnold Cooper, a member of the United States Marines. Sitting in your chair...";
	}
}

void Player::turn2() {

}

void Player::turn3() {

}

void Player::turn4() {

}

void Player::turn5() {

}

void Player::turn6() {

}

void Player::turn7() {

}

void Player::turn8() {

}

void Player::turn9() {

}

void Player::turn10() {

}

void Player::displayEpilogue() {

}