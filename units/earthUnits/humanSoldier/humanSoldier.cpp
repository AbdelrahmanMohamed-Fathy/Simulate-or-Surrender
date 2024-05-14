#include "humanSoldier.h"
#include "../earthArmy.h"
#include "../../alienUnits/alienArmy.h"
#include"../../gameManager.h"
#include <cmath>


void humanSoldier::attack(gameManager* gm, queue<unit_Interface*>* deathList, int timeStep, bool printed) {

	queue<alienSoldier*>* aliensoldier = gm->getAlienArmy()->getSoldiers();
	queue<humanSoldier*>* earthsoldier = gm->getEarthArmy()->getSoldiers();
	alienArmy* aliens = gm->getAlienArmy();
	earthArmy* humans = gm->getEarthArmy();
	alienSoldier* temp;
	humanSoldier* betrayed;
	queue<alienSoldier*> attack;
	queue<humanSoldier*> betrayal;
	queue<humanSoldier*> toBeReturned;

	for (int i = 0; i < (int)attackCapacity; i++)
	{
		if (getInfection())
		{
			while (earthsoldier->dequeue(betrayed))
			{
				if (!betrayed->getInfection())
				{
					betrayal.enqueue(betrayed);
					break;
				}
				toBeReturned.enqueue(betrayed);
			}
			while (toBeReturned.dequeue(betrayed))
			{
				earthsoldier->enqueue(betrayed);
			}
		}
		else if (aliensoldier->dequeue(temp))
		{
			attack.enqueue(temp);
		}
	}
	
	if (printed) {
		cout << "ES " << this << " attacking: ";
		if (!getInfection()) {
			attack.print();
		}
		else {
			betrayal.print();
		}
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
				deathList->enqueue(temp);
				int tempCount;
				tempCount = aliens->getDeathCountAS();
				tempCount++;
				aliens->setDeathCountAS(tempCount);
			}
			else aliensoldier->enqueue(temp);
		}

		if (betrayal.dequeue(betrayed))
		{
			if (betrayed->getFirstAttackedTime() == -1)
			{
				betrayed->setFirstAttackedTime(timeStep);
			}
			*betrayed->getHP() -= (power * (health / 100.0)) / sqrt(*temp->getHP());
			if (*betrayed->getHP() <= 0) {
				betrayed->setDestructionTime(timeStep);
				deathList->enqueue(betrayed);
				if (betrayed->getInfection())
				{
					int infectionCount = humans->getInfectionCountES();
					infectionCount--;
					humans->setInfectionCountES(infectionCount);
				}
				int tempCount;
				tempCount = humans->getDeathCountES();
				tempCount++;
				humans->setDeathCountES(tempCount);
			}
			else earthsoldier->enqueue(betrayed);
		}
	}
}

bool humanSoldier::getImmunity() const
{
	return immune;
}

bool humanSoldier::getInfection() const
{
	return infected;
}

void humanSoldier::setImmunity(bool immunity)
{
	immune = immunity;
}

void humanSoldier::setInfection(bool infection)
{
	infected = infection;
}