#include "humanGunner.h"
#include "../../alienUnits/alienArmy.h"
#include "../../basicDataStructures/priQueue.cpp"

void humanGunner::attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
	deQueue<alienDrone*>* drone;
	alienDrone* temp;
	drone = aliens->getDrones();
	randomBag<alienMonster*>* monster;
	alienMonster* temp1;
	monster = aliens->getMonsters();
	priQueue<alienUnit*> attack;
	double priority;
	alienUnit* unit;

	for (int i = 0; i < floor(attackCapacity / 2); i++) {
		if (drone->dequeueback(temp)) {
			attack.enqueue(temp, 1);
		}
		if (drone->dequeuefront(temp)) {
			attack.enqueue(temp, 1);
		}
	}
	for (int i = 0; i < ceil(attackCapacity / 2); i++) {
		if (monster->remove(temp1)) {
			attack.enqueue(temp1, 2);
		}
	}

	if (printed) {
		attack.print();
	}

	for (int i = 0; i < attack.getCount(); i++) {
		if (attack.dequeue(unit, priority)) {
			if (unit->getFirstAttackedTime() == -1) {
				unit->setFirstAttackedTime(timeStep);
			}
			*unit->getHP() -= (power * (health / 100.0)) / sqrt(*unit->getHP());
			if (unit->getHP() <= 0) {
				unit->setDestructionTime(timeStep);
				deathList->enqueue(unit);
			}
			switch ((int)priority) {
			case 1: 
				if (i % 2 == 0)
					drone->enqueueFront((alienDrone*)unit);
				else
					drone->enqueueBack((alienDrone*)unit);
				break;
			case 2: 
				monster->addElement((alienMonster*)unit);
				break;
			}
		}
	}
}

double humanGunner::getPriority()
{
    return (double)power*(health/100.0);
}
