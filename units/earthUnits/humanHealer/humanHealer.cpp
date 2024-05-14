#include "humanHealer.h"
#include "../../alienUnits/alienArmy.h"
#include "../earthArmy.h"

priQueue<earthUnit*>* humanHealer::unitMaintenanceList = nullptr;
earthArmy* humanHealer::army = nullptr;

priQueue<earthUnit*>* humanHealer::getUnitMaintenanceList()
{
    return unitMaintenanceList;
}

void humanHealer::setUnitMaintenanceList(priQueue<earthUnit*>* UML)
{
    unitMaintenanceList = UML;
}

void humanHealer::setEarthArmy(earthArmy* EA)
{
	army = EA;
}

void humanHealer::attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
	earthUnit* temp;
	army->getCuredSoldiers()->dequeue((humanSoldier*&)(temp));
	army->getSoldiers()->enqueue(((humanSoldier*)temp));
	double dummy;
	priQueue<earthUnit*> heal;
	for (int i = 0; i < (int)attackCapacity; i++) {
		bool exists = unitMaintenanceList->dequeue(temp, dummy);
		while ( exists && ((timeStep - temp->getMaintenanceWaitStartTime()) >= 10)) {
			temp->setDestructionTime(timeStep);
			deathList->enqueue(temp);
			if (dummy == -INFINITY)
				army->setDeathCountET(army->getDeathCountET() + 1);
			else
				army->setDeathCountES(army->getDeathCountES() + 1);

			exists = unitMaintenanceList->dequeue(temp, dummy);
		}
		if (exists) heal.enqueue(temp, dummy);
	}

	if (printed) {
		cout << "ES " << ID << " healing: ";
		heal.print();
	}

	int count = heal.getCount();

	for (int i = 0; i < count; i++) {
		if (heal.dequeue(temp, dummy)) {
			*temp->getHP() += (power * (health / 100.0)) / sqrt(*temp->getHP());
			if (dummy == -INFINITY) {
				army->getTanks()->push((humanTank*)(temp));
			}
			else {
				if (((humanSoldier*)temp)->getInfection())
				{
					((humanSoldier*)temp)->setInfection(false);
					((humanSoldier*)temp)->setImmunity(true);
					army->setInfectionCountES(army->getInfectionCountES() - 1);
					army->getCuredSoldiers()->enqueue(((humanSoldier*)temp));
				}
				else
				{
					army->getSoldiers()->enqueue((humanSoldier*)(temp));
				}
			}
		}
	}
	this->setDestructionTime(timeStep);
	this->setFirstAttackedTime(timeStep);
	army->setDeathCountEH(army->getDeathCountEH() + 1);
	deathList->enqueue(this);
}

