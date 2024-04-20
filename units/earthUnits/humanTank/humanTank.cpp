#include "humanTank.h"

#include"../../alienUnits/alienArmy.h"

#include"../../../basicDataStructures/priQueue.cpp"

#include"../../../Utils/generateNumber.cpp"

bool humanTank::pctcheck = false;

void humanTank::attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
	priQueue<alienUnit*> attackedq;
	if (pctcheck)
	{
		if (*EScount / ((aliens->getSoldiers()->getCount())) > 0.8)
		{
			pctcheck = false;
		}
	}
	else
	{
		if (*EScount / ((aliens->getSoldiers()->getCount())) < 0.3)
		{
			pctcheck = true;
		}
	}


	if (!pctcheck)
	{
		for (int i = 0; i < attackCapacity; i++)
		{
			alienMonster* monster;
			aliens->getMonsters()->remove(monster);
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
				aliens->getMonsters()->remove(monster);
				attackedq.enqueue(monster, 0);
				break;
			case 2:
				alienSoldier * soldier;
				aliens->getSoldiers()->dequeue(soldier);
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

	for (int i = 0; i < attackedq.getCount(); i++)
	{
		alienUnit* alien;
		double pri;
		if (attackedq.dequeue(alien,pri))
		{
			if (alien->getFirstAttackedTime() == -1)
			{
				alien->setfirstAttackedTime(timeStep);
			}
			double* alienHP = alien->getHP();
			*alienHP -=  (((power * health) / 100) / sqrt(*alienHP));
			alien->setfirstAttackedTime(timeStep);
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
					//aliens->getMonsters()->addElement(&(alienMonster*)alien);
					break;
				case 1:
					aliens->getSoldiers()->enqueue((alienSoldier*)alien);
				}
			}
		}
	}
}
