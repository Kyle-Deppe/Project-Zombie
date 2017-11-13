#include "Character.h"

Character::Character(int choice) {

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
		name = "Smol Pupper";           // Pupper //////////////////////////////////////////////////////////////////// Joel: Choose name
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

void Player::addChoice(int newChoice)
{
	if (prevChoices.size() >= 1) {
		prevChoice = getLastChoice();
	}

	prevChoices.push_back(newChoice);
	currentChoice = getLastChoice();
}

void Player::turn1() {
	if (characterNumber == 1) {
		cout << endl << "You are Arnold Cooper, a member of the United States Marines. Sitting at your desk, you listen to the radio"
			<< endl << "as it tells you about how San Diego is safe from the pandemic. That's all you need to hear. You pack your bags,"
			<< endl << "keeping in mind that your truck is out of gas and you need to pack lightly. After food and water, you decide to"
			<< endl << "also bring a:"
			<< endl << "1. Pistol and ammunition."
			<< endl << "2. Crow bar.";
	}
	else if (characterNumber == 2) {
		cout << endl << "You are Clark Kent, a lawyer in New York City.";
	}
	else if (characterNumber == 3) {
		cout << endl << "You are Dr. Rivera, an ingenious professor in Missouri.";
	}
	else if (characterNumber == 4) {
		cout << endl << "You am pupper.";
	}
	else if (characterNumber == 5) {
		cout << endl << "You are Abigail Willow, a student at Westhall Elementary.";
	}
	else if (characterNumber == 6) {
		cout << endl << "You are Darwin Arnold, some weird survivalist/conspiracy theorist guy that Tsiania sucked at describing."
	}
}

void Player::turn2() {
	if (characterNumber == 1) {
		if (prevChoice == 1) {
			addSupplies(rand() % 11);
			addLuck((rand() % 11) * -1);
		}
		else {
			addSupplies((rand() % 11) * (-1));
			addLuck(rand() % 11);
		}
		cout << endl << "You've gone outside and started biking west. You reach a bridge that gave out. About to turn around,"
			<< endl << "you notice the side walls of the bridge are intact. Do you"
			<< endl << "1. Turn around and go the long way. The bridge might crumble."
			<< endl << "2. Go across the bridge anyways. It's going to be dark soon.";
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}

void Player::turn3() {
	if (characterNumber == 1) {
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}

void Player::turn4() {
	if (characterNumber == 1) {
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}

void Player::turn5() {
	if (characterNumber == 1) {
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}

void Player::turn6() {
	if (characterNumber == 1) {
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}

void Player::turn7() {
	if (characterNumber == 1) {
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}

void Player::turn8() {
	if (characterNumber == 1) {
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}

void Player::turn9() {
	if (characterNumber == 1) {
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}

void Player::turn10() {
	if (characterNumber == 1) {
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}

void Player::displayEpilogue() {
	if (characterNumber == 1) {
	}
	else if (characterNumber == 2) {

	}
	else if (characterNumber == 3) {

	}
	else if (characterNumber == 4) {

	}
	else if (characterNumber == 5) {

	}
	else if (characterNumber == 6) {

	}
}