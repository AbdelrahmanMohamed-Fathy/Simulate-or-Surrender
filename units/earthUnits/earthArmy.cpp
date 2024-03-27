#include "earthArmy.h"
#include "../../basicDataStructures/queue.cpp"
#include "../../basicDataStructures/stack.cpp"
#include "../../basicDataStructures/priQueue.cpp"


earthArmy::earthArmy(gameManager* GM) : gm(GM)
{
	soldiers = new queue<humanSoldier*>;
	tanks = new stack<humanTank*>;
	gunners = new priQueue<humanGunner*>;
	nextFreeID = 1;
}

earthArmy::~earthArmy()
{
	delete soldiers;
	delete tanks;
	delete gunners;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Getters														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
queue<humanSoldier*>* earthArmy::getSoldiers()
{
	return soldiers;
}

stack<humanTank*>* earthArmy::getTanks()
{
	return tanks;
}

priQueue<humanGunner*>* earthArmy::getGunners()
{
	return gunners;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Adders														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void earthArmy::addSoldier()
{
}

void earthArmy::addTank()
{
}

void earthArmy::addGunner()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Miscellaneous													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool earthArmy::isEmpty()
{
	if (soldiers->isEmpty() && tanks->isEmpty() && gunners->isEmpty())
		return true;
	return false;
}

void earthArmy::print()
{
	cout << "================================ Earth army units ================================\n";
	cout << soldiers->getCount() << " Human Soldiers: ";
	soldiers->print();
	cout << tanks->getCount() << " Human Tanks: ";
	tanks->print();
	cout << gunners->getCount() << "Human Gunners: ";
	gunners->print();
}

void earthArmy::attack(alienArmy* aliens, bool printed)
{
}