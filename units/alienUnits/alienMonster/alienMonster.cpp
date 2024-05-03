#include "alienMonster.h"

#include"../../earthUnits/earthArmy.h"

#include "../../basicDataStructures/priQueue.cpp"

#include"../../../utils/generateNumber.cpp"


void alienMonster::attack(earthArmy* humans, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
	priQueue<earthUnit*> attackedq;

	for (int i = 0; i < attackCapacity; i++)
	{
		int x = generateNumber(1, 2);
		switch (x)
		{
		case 1:
			humanSoldier * soldier;
			if(humans->getSoldiers()->dequeue(soldier))
				attackedq.enqueue(soldier, 0);
			break;
		case 2:
			humanTank * tank;
			if(humans->getTanks()->pop(tank))
				attackedq.enqueue(tank, 1);
			break;
		}
	}

	if (printed)
	{
		cout << "AM " << ID << " attacking: ";
		attackedq.print();
	}
	int count = attackedq.getCount();
	for (int i = 0; i < count; i++)
	{
		earthUnit* human;
		double pri;
		if (attackedq.dequeue(human, pri))
		{
			if (human->getFirstAttackedTime() == -1)
			{
				human->setFirstAttackedTime(timeStep);
			}
			double* humanHP = human->getHP();
			*humanHP -= (((power * health) / 100) / sqrt(*humanHP));
			human->setFirstAttackedTime(timeStep);
			if (*humanHP <= 0)
			{
				human->setDestructionTime(timeStep);
				deathList->enqueue(human);
				switch ((int)pri)
				{
				int tempCount;
				case 0:
					tempCount = humans->getDeathCountES();
					tempCount++;
					humans->setDeathCountES(tempCount);
					break;
				case 1:
					tempCount = humans->getDeathCountET();
					tempCount++;
					humans->setDeathCountET(tempCount);
				}
			}
			else if (human->checkMaintenanceListViability())
			{
				priQueue<earthUnit*>* mainList = humans->getUnitMaintenanceList();
				switch ((int)pri) {
				
				case 0:mainList->enqueue(human, -(*human->getHP()));
					break;

				case 1:mainList->enqueue(human, -INFINITY);
					break;
				}
			}
			else
			{
				switch ((int)pri)
				{
				case 0:
					humans->getSoldiers()->enqueue((humanSoldier*)human);
					break;
				case 1:
					humans->getTanks()->push((humanTank*)human);
				}
			}
		}
	}
}

int alienMonster::getDeathCount()
{
	return deathCount;
}
