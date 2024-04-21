#include "humanSoldier.h"
#include "../earthArmy.h"
#include "../../alienUnits/alienArmy.h"
#include <cmath>

unsigned int humanSoldier::deathCount = 0;

void humanSoldier::attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed) {
	queue<alienSoldier*>* aliensoldier;
	aliensoldier=aliens->getSoldiers();
	alienSoldier* temp;
	queue<alienSoldier*> attack;
	
	for (int i = 0; i < (int)attackCapacity; i++) {
		if (aliensoldier->dequeue(temp)) {
			attack.enqueue(temp);
		}
	}
	
	if (printed) {
		cout << "ES " << ID << " attacking: ";
		attack.print();
	}

	int count = attack.getCount();

	for (int i = 0; i < count; i++) {
		if (attack.dequeue(temp)) {
			if (temp->getFirstAttackedTime()==-1) {
				temp->setFirstAttackedTime(timeStep);
			}
			*temp->getHP() -= (power * (health / 100.0)) / sqrt(*temp->getHP());
			if (*temp->getHP() <= 0) {
				temp->setDestructionTime(timeStep);
				deathList->enqueue(temp);
			}
			else aliensoldier->enqueue(temp);
		}
	}
}

int humanSoldier::getDeathCount()
{
	return deathCount;
}
