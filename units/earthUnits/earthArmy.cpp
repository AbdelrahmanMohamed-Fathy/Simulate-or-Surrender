#include "earthArmy.h"
#include "../../basicDataStructures/queue.cpp"
#include "../../basicDataStructures/stack.cpp"
#include "../../basicDataStructures/priQueue.cpp"
#include "../../gameManager.h"

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
void earthArmy::addSoldier(int HP, int PW, int AC)
{
	//humanSoldier* newUnit = new humanSoldier(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	//soldier->enqueue(newUnit);
}

void earthArmy::addTank(int HP, int PW, int AC)
{
	//humanTank* newUnit = new humanTank(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	//tanks->push(newUnit);
}

void earthArmy::addGunner(int HP, int PW, int AC)
{
	//humanGunner* newUnit = new humanGunner(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	//gunners->enqueue(newUnit, PW * (HP/100));
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
	cout << gunners->getCount() << " Human Gunners: ";
	gunners->print();
}

void earthArmy::attack(alienArmy* aliens, bool printed)
{
}