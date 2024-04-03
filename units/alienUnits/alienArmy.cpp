#include "alienArmy.h"
#include "../../basicDataStructures/queue.cpp"
#include "../../basicDataStructures/bag.cpp"
#include "../../basicDataStructures/deQueue.cpp"
#include "../../gameManager.h"

alienArmy::alienArmy(gameManager* GM) : gm(GM)
{
	soldiers = new queue<alienSoldier*>;
	monsters = new bag<alienMonster*>;
	drones = new deQueue<alienDrone*>;
	nextFreeID = 2000;
}

alienArmy::~alienArmy()
{
	alienSoldier* temp1;
	while (soldiers->dequeue(temp1))
		delete temp1;

	alienMonster** temp2{};
	while (monsters->remove(*temp2))
	{
		delete *temp2;
		delete temp2;
	}

	alienDrone* temp3;
	while (drones->dequeuefront(temp3))
		delete temp3;

	delete soldiers;
	delete monsters;
	delete drones;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Getters														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
queue<alienSoldier*>* alienArmy::getSoldiers()
{
	return soldiers;
}

bag<alienMonster*>* alienArmy::getMonsters()
{
	return monsters;
}

deQueue<alienDrone*>* alienArmy::getDrones()
{
	return drones;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Adders														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alienArmy::addSoldier(int HP, int PW, int AC)
{
	alienSoldier* newUnit = new alienSoldier(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	soldiers->enqueue(newUnit);
}

void alienArmy::addMonster(int HP, int PW, int AC)
{
	alienMonster** newUnit = new alienMonster*;
	*newUnit = new alienMonster(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	monsters->addElement(*newUnit);
}

void alienArmy::addDrone(int HP, int PW, int AC)
{
	alienDrone* newUnit = new alienDrone(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	drones->enqueueFront(newUnit);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Miscellaneous													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool alienArmy::isEmpty()
{
	if (soldiers->isEmpty() && monsters->isEmpty() && drones->isEmpty())
		return true;
	return false;
}

void alienArmy::print()
{
	cout << "================================ Alien army units ================================\n";
	cout << soldiers->getCount() << " Alien Soldiers: ";
	soldiers->print();
	cout << monsters->getCount() << " Alien Monsters: ";
	monsters->print();
	cout << drones->getCount() << " Alien Drones: ";
	drones->print();
}

void alienArmy::attack(earthArmy* humans, bool printed)
{
}