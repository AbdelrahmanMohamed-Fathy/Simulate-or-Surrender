#include "humanHealer.h"
#include "../../alienUnits/alienArmy.h"

priQueue<earthUnit*>* humanHealer::unitMaintenanceList = nullptr;

priQueue<earthUnit*>* humanHealer::getUnitMaintenanceList()
{
    return unitMaintenanceList;
}

void humanHealer::setUnitMaintenanceList(priQueue<earthUnit*>* UML)
{
    unitMaintenanceList = UML;
}

void humanHealer::attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
	earthUnit* temp;
	double dummy;
	priQueue<earthUnit*> heal;
	for (int i = 0; i < (int)attackCapacity; i++) {
		
		while (unitMaintenanceList->dequeue(temp, dummy) && ((timeStep - temp->getMaintenanceWaitStartTime()) >= 10)) {
			deathList->enqueue(temp);
		}
		heal.enqueue(temp, dummy);
	}

	if (printed) {
		cout << "ES " << ID << " attacking: ";
		heal.print();
	}

	int count = heal.getCount();

	for (int i = 0; i < count; i++) {
		if (heal.dequeue(temp, dummy)) {
			
			*temp->getHP() += (power * (health / 100.0)) / sqrt(*temp->getHP());
			if (dummy == -INFINITY) {
				
			}
			else {

			}
		}
	}
}

int humanHealer::getDeathCount()
{
    return deathCount;
}

