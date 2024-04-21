#include "humanTank.h"
#include"../../alienUnits/alienArmy.h"
#include"../../../basicDataStructures/priQueue.cpp"
#include"../../../Utils/generateNumber.cpp"

bool humanTank::pctCheck = false;

void humanTank::setpctCheck(bool set)
{
	pctCheck = set;
}

bool humanTank::getpctCheck()
{
	return pctCheck;
}

void humanTank::attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
	priQueue<alienUnit*> attackedq;

	if (!pctCheck)
	{
		for (int i = 0; i < (int)attackCapacity; i++)
		{
			alienMonster* monster;
			if(aliens->getMonsters()->remove(monster))
				attackedq.enqueue(monster,0);
		}
	}
	else
	{
		for (int i = 0; i < attackCapacity; i++)
		{
			int x = generateNumber(1, 2);
			switch (x)
			{
			case 1:
				alienMonster * monster;
				if(aliens->getMonsters()->remove(monster))
					attackedq.enqueue(monster, 0);
				break;
			case 2:
				alienSoldier * soldier;
				if(aliens->getSoldiers()->dequeue(soldier))
					attackedq.enqueue(soldier, 1);
				break;
			}
		}
	}

	if (printed)
	{
		cout << "ET " << ID << " attacking: ";
		attackedq.print();
	}

	int count = attackedq.getCount();

	for (int i = 0; i < count; i++)
	{
		alienUnit* alien;
		double pri;
		if (attackedq.dequeue(alien,pri))
		{
			if (alien->getFirstAttackedTime() == -1)
			{
				alien->setFirstAttackedTime(timeStep);
			}
			double* alienHP = alien->getHP();
			*alienHP -=  (((power * health) / 100) / sqrt(*alienHP));
			alien->setFirstAttackedTime(timeStep);
			if (*alienHP <= 0)
			{
				alien->setDestructionTime(timeStep);
				deathList->enqueue(alien);
			}
			else
			{
				switch ((int)pri)
				{
				case 0:
					aliens->getMonsters()->addElement((alienMonster*&)alien);
					break;
				case 1:
					aliens->getSoldiers()->enqueue((alienSoldier*)alien);
				}
			}
		}
	}
}
