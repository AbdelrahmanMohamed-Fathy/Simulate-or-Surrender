#include "alienSoldier.h"
#include "../../earthUnits/earthArmy.h"
#include<cmath>


void alienSoldier::attack(earthArmy* humans, queue<unit_Interface*>* deathList,int timeStep, bool printed) {
	queue<humanSoldier*>* humansoldier;
	humansoldier = humans->getSoldiers();
	humanSoldier* temp;
	queue<humanSoldier*> attack;

	for (int i = 0; i < (int)attackCapacity; i++) {
		if (humansoldier->dequeue(temp)) {
			attack.enqueue(temp);
		}
	}

	if (printed) {
		cout << "AS " << ID << " attacking: ";
		attack.print();
	}

	int count = attack.getCount();

	for (int i = 0; i < count; i++) {
		if (attack.dequeue(temp)) {
			if (temp->getFirstAttackedTime() == -1) {
				temp->setFirstAttackedTime(timeStep);
			}
			*temp->getHP() -= (power * (health / 100.0)) / sqrt(*temp->getHP());
			if (*temp->getHP() <= 0) {
				temp->setDestructionTime(timeStep);
				int tempCount;
				tempCount = humans->getDeathCountES();
				tempCount++;
				humans->setDeathCountES(tempCount);
				deathList->enqueue(temp);
			}
			else if ((earthUnit*)temp->checkMaintenanceListViability())
			{
				temp->setMaintenanceWaitStartTime(timeStep);
				priQueue<earthUnit*>* mainList = humans->getUnitMaintenanceList();
				mainList->enqueue((earthUnit*)temp, -(*temp->getHP()));
			}
			else humansoldier->enqueue(temp);
		}
	}
}
