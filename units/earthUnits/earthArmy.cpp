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
	healers = new stack<humanHealer*>;
	unitMaintenanceList = new priQueue<earthUnit*>;
	humanHealer::setUnitMaintenanceList(unitMaintenanceList);
	nextFreeID = 1;
}

earthArmy::~earthArmy()
{
	humanSoldier* temp1;
	while (soldiers->dequeue(temp1))
		delete temp1;

	humanTank* temp2;
	while (tanks->pop(temp2))
		delete temp2;

	humanGunner* temp3; double dummy;
	while (gunners->dequeue(temp3, dummy))
		delete temp3;

	humanHealer* temp4;
	while (healers->pop(temp4))
		delete temp4;

	earthUnit* temp5;
	while (unitMaintenanceList->dequeue(temp5, dummy))
		delete temp4;

	delete soldiers;
	delete tanks;
	delete gunners;
	delete healers;
	delete unitMaintenanceList;
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

stack<humanHealer*>* earthArmy::getHealers()
{
	return healers;
}
priQueue<earthUnit*>* earthArmy::getUnitMaintenanceList()
{
	return unitMaintenanceList;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Adders														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void earthArmy::addSoldier(int HP, int PW, int AC)
{
	humanSoldier* newUnit = new humanSoldier(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	soldiers->enqueue(newUnit);
}

void earthArmy::addTank(int HP, int PW, int AC)
{
	humanTank* newUnit = new humanTank(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	tanks->push(newUnit);
}

void earthArmy::addGunner(int HP, int PW, int AC)
{
	humanGunner* newUnit = new humanGunner(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	gunners->enqueue(newUnit, newUnit->getPriority());
}

void earthArmy::addHealer(int HP, int PW, int AC)
{
	humanHealer* newUnit = new humanHealer(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	healers->push(newUnit);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Miscellaneous													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool earthArmy::isEmpty()
{
	if (soldiers->isEmpty() && tanks->isEmpty() && gunners->isEmpty() && healers->isEmpty())
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
	cout << healers->getCount() << " Human Healers: ";
	healers->print();
}

void earthArmy::attack(alienArmy* aliens, bool printed)
{
	//Human Soldier:
	humanSoldier* soldier;
	if (soldiers->peek(soldier)) {
		soldier->attack(aliens,gm->getTimeStep(),printed);
	}

	//Human Tank:
	humanTank* tank;
	if (tanks->peek(tank)) {
		tank->attack(aliens, gm->getDeathList(), gm->getTimeStep(), printed);
	}

	//Human Gunner:
	humanGunner* gunner;
	double temp;
	if (gunners->peek(gunner, temp)) {
		gunner->attack(aliens, gm->getDeathList(), gm->getTimeStep(), printed);
	}
}