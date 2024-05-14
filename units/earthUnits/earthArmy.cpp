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
	humanHealer::setEarthArmy(this);
}

earthArmy::~earthArmy()
{
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

queue<humanSoldier*>* earthArmy::getCuredSoldiers()
{
	return curedSoldiers;
}

int earthArmy::getDeathCountET()
{
	return deathCountET;
}

int earthArmy::getDeathCountEG()
{
	return deathCountEG;
}

int earthArmy::getDeathCountES()
{
	return deathCountES;
}

int earthArmy::getDeathCountEH()
{
	return deathCountEH;
}

int earthArmy::getInfectionCountES()
{
	return infectionCountES;
}

int earthArmy::getTotalInfectionCountES()
{
	return totalInfectionCountES
}

void earthArmy::setDeathCountET(int deathCount)
{
	deathCountET = deathCount;
}

void earthArmy::setDeathCountEG(int deathCount)
{
	deathCountEG = deathCount;
}

void earthArmy::setDeathCountES(int deathCount)
{
	deathCountES = deathCount;
}

void earthArmy::setDeathCountEH(int deathCount)
{
	deathCountEH = deathCount;
}

void earthArmy::setInfectionCountES(int infectionCount)
{
	infectionCountES = infectionCount;
}

void earthArmy::setTotalInfectionCountES(int totalInfectionCount)
{
	totalInfectionCountES = totalInfectionCount;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Adders														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void earthArmy::addSoldier(humanSoldier*& soldier)
{
	soldiers->enqueue(soldier);
}

void earthArmy::addTank(humanTank*& tank)
{
	tanks->push(tank);
}

void earthArmy::addGunner(humanGunner*& gunner)
{
	gunners->enqueue(gunner, gunner->getPriority());
}

void earthArmy::addHealer(humanHealer*& healer)
{
	healers->push(healer);
}

void earthArmy::addToMaintenance(earthUnit*& human, double pri)
{
	unitMaintenanceList->enqueue(human, pri);
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
	cout << healers->getCount() << " Human Healers: ";
	healers->print();
	cout << unitMaintenanceList->getCount() << " Human Units inside Maintenance List: ";
	unitMaintenanceList->print();
	cout << endl << " Human Soldiers Infection Rate: " << infectionCountES / soldiers->getCount() << "%";
	cout << endl;
}

void earthArmy::attack(alienArmy* aliens, bool printed)
{
	//Human Soldier:
	humanSoldier* soldier;
	if (soldiers->peek(soldier)) {
		soldier->attack(gm, gm->getDeathList(), gm->getTimeStep(), printed);
	}

	//Human Tank:
	if (humanTank::getpctCheck() || aliens->getSoldiers()->isEmpty())
	{
		if (aliens->getSoldiers()->isEmpty() || soldiers->getCount() / ((aliens->getSoldiers()->getCount())) > 0.8)
		{
			humanTank::setpctCheck(false);
		}
	}
	else
	{
		if (soldiers->getCount() / ((aliens->getSoldiers()->getCount())) < 0.3)
		{
			humanTank::setpctCheck(true);
		}
	}
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

	//Human Healer:
	humanHealer* healer;
	if (healers->pop(healer))
	{
		healer->attack(aliens, gm->getDeathList(), gm->getTimeStep(), printed);
	}
}