#include "alienMonster.h"

#include"../../earthUnits/earthArmy.h"

#include "../../basicDataStructures/priQueue.cpp"

#include"../../../utils/generateNumber.cpp"

void alienMonster::attack(earthArmy* humans,int timeStep, bool printed, queue<unit_Interface*>* deathList)
{
	priQueue<earthUnit*> attackedq;

	for (int i = 0; i < attackCapacity; i++)
	{
		int x = generateNumber(1, 2);
		switch (x)
		{
		case 1:
			humanSoldier * soldier;
			humans->getSoldiers()->dequeue(soldier);
			attackedq.enqueue(soldier, 0);
			break;
		case 2:
			humanTank * tank;
			humans->getTanks()->pop(tank);
			attackedq.enqueue(tank, 1);
			break;
		}
	}

	if (printed)
	{
		cout << "AM " << ID << " attacking: ";
		attackedq.print();
	}

	for (int i = 0; i < attackedq.getCount(); i++)
	{
		earthUnit* human;
		double pri;
		if (attackedq.dequeue(human, pri))
		{
			if (human->getFirstAttackedTime() == -1)
			{
				human->setfirstAttackedTime(timeStep);
			}
			double* humanHP = human->getHP();
			*humanHP -= (((power * health) / 100) / sqrt(*humanHP));
			human->setfirstAttackedTime(timeStep);
			if (*humanHP <= 0)
			{
				human->setDestructionTime(timeStep);
				deathList->enqueue(human);
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
