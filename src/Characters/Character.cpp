#include "Character.h"

Character::Character(int choice) {
	cout << "constructor" << endl;

	if (choice == 1) {
		name = "Dr. Rivera";
		health = 75;
		supplies = 10;
		luck = 25;

	}
	else if (choice == 2) {
		name = "Clark Kent";
		health = 50;
		supplies = 100;
		luck = 10;
	}
	else if (choice == 3) {
		name = "Smith Cooper";
		health = 100;
		supplies = 70;
		luck = 30;
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
	cout << _name << " constructor" << endl;
	name = _name;
	health = _health;
	supplies = _supplies;
	luck = _luck;
}

Character::~Character() {
	cout << name << " deconstructor" << endl;
}

void Character::printPlayerData()
{
	cout << "\n" << name << "'s Data" << endl
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

void Character::addStory( int turn, string story )
{
	cout << "Adding Story to " << name << endl;
	mainStory.emplace( turn, story );
}
