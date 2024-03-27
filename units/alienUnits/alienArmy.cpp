#include "alienArmy.h"
#include "../../basicDataStructures/queue.cpp"
#include "../../basicDataStructures/bag.cpp"
#include "../../basicDataStructures/deQueue.cpp"

alienArmy::alienArmy(gameManager* GM) : gm(GM)
{
	soldiers = new queue<alienSoldier*>;
	monsters = new bag<alienMonster*>;
	drones = new deQueue<alienDrone*>;
	nextFreeID = 2000;
}

alienArmy::~alienArmy()
{
	delete soldiers;
	delete monsters;
	delete drones;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Getters														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
queue<alienSoldier*>* alienArmy::getSoldiers()
{
	return soldiers;
}

bag<alienMonster*>* alienArmy::getMonsters()
{
	return monsters;
}

deQueue<alienDrone*>* alienArmy::getDrones()
{
	return drones;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Adders														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alienArmy::addSoldier()
{
}

void alienArmy::addMonster()
{
}

void alienArmy::addDrone()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Miscellaneous													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool alienArmy::isEmpty()
{
	if (soldiers->isEmpty() && monsters->isEmpty() && drones->isEmpty())
		return true;
	return false;
}

void alienArmy::print()
{
	cout << "================================ Alien army units ================================\n";
	cout << soldiers->getCount() << " Alien Soldiers: ";
	soldiers->print();
	cout << monsters->getCount() << " Alien Monsters: ";
	monsters->print();
	cout << drones->getCount() << "Alien Drones: ";
	drones->print();
}

void alienArmy::attack(earthArmy* humans, bool printed)
{
}