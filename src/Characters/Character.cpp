#include "Character.h"

Character::Character(int choice) {
	// cout << "constructor" << endl;

	if (choice == 1) {
		name = "Dr. Rivera";
		health = 35 + (rand() % 41);
		supplies = 35 + (rand() % 41);
		luck = 35 + (rand() % 41);
	}
	else if (choice == 2) {
		name = "Clark Kent";
		health = 35 + (rand() % 41);
		supplies = 35 + (rand() % 41);
		luck = 35 + (rand() % 41);
	}
	else if (choice == 3) {
		name = "Smith Cooper";
		health = 35 + (rand() % 41);
		supplies = 35 + (rand() % 41);
		luck = 35 + (rand() % 41);
	}
	else if (choice == 4) {
		// Lil Pupper
	}
	else if (choice == 5) {
		// Child
	}
	else if (choice == 6) {
		// Conspiracy Theorist
	}
}

Character::Character( string _name, int _health = 100, int _supplies = 10, int _luck = 50 ) {
	// cout << _name << " constructor" << endl;
	name = _name;
	health = _health;
	supplies = _supplies;
	luck = _luck;
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
