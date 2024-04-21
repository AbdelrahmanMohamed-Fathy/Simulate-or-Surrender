#include "alienDrone.h"
#include "../../earthUnits/earthArmy.h"
#include <cmath>

unsigned int alienDrone::deathCount = 0;

void alienDrone::attack(earthArmy* humans, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
	stack<humanTank*>* tanks;
	humanTank* temp;
	tanks = humans->getTanks();
	priQueue<humanGunner*>* gunner;
	humanGunner* temp1;
	gunner = humans->getGunners();
	priQueue<earthUnit*> attack;
	double priority;
	earthUnit* unit;

	for (int i = 0; i < floor(attackCapacity / 2); i++) {
		if (tanks->pop(temp)) {
			attack.enqueue(temp, 1);
		}
	}
	for (int i = 0; i < ceil(attackCapacity / 2); i++) {
		if (gunner->dequeue(temp1, priority)) {
			attack.enqueue(temp1, 2);
		}
	}

	if (printed) {
		cout << "AD " << ID << " attacking: ";
		attack.print();
	}
	int count = attack.getCount();

	for (int i = 0; i < count; i++) {
		if (attack.dequeue(unit, priority)) {
			if (unit->getFirstAttackedTime() == -1) {
				unit->setFirstAttackedTime(timeStep);	
			}
			*unit->getHP() -= (power * (health / 100.0)) / sqrt(*unit->getHP());
			if (*unit->getHP() <= 0) {
				unit->setDestructionTime(timeStep);
				deathList->enqueue(unit);
			}
			else
			{
				switch ((int)priority) {
				case 1: tanks->push((humanTank*)unit);
					break;
				case 2: gunner->enqueue((humanGunner*)unit, ((humanGunner*)unit)->getPriority());
					break;
				}
			}
		}	
	}
}

int alienDrone::getDeathCount()
{
	return deathCount;
}
