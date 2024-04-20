#include "alienArmy.h"
#include "../../basicDataStructures/queue.cpp"
#include "../../basicDataStructures/randomBag.cpp"
#include "../../basicDataStructures/deQueue.cpp"
#include "../../gameManager.h"

alienArmy::alienArmy(gameManager* GM) : gm(GM)
{
	soldiers = new queue<alienSoldier*>;
	monsters = new randomBag<alienMonster*>;
	drones = new deQueue<alienDrone*>;
	nextFreeID = 2000;
}

alienArmy::~alienArmy()
{
	alienSoldier* temp1;
	while (soldiers->dequeue(temp1))
		delete temp1;

	alienMonster* temp2;
	while (monsters->remove(temp2))
		delete temp2;

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

randomBag<alienMonster*>* alienArmy::getMonsters()
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
	alienMonster* newUnit = new alienMonster(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	monsters->addElement(newUnit);
}

void alienArmy::addDrone(int HP, int PW, int AC)
{
	alienDrone* newUnit = new alienDrone(nextFreeID++, HP, PW, AC, gm->getTimeStep());
	if (gm->getTimeStep() % 2 == 0)
		drones->enqueueFront(newUnit);
	else
		drones->enqueueBack(newUnit);
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
	//Alien Soldier
	alienSoldier* soldier;
	if (soldiers->peek(soldier)) {
		soldier->attack(humans, gm->getDeathList(), gm->getTimeStep(), printed);
	}

	//Alien Monster
	alienMonster* temp;
	if (monsters->peek(temp)) {
		temp->attack(humans, gm->getDeathList(), gm->getTimeStep(), printed);
	}

	//Alien Drone
	alienDrone *frontDrone, *backDrone;
	if (drones->peekFront(frontDrone) && drones->peekBack(backDrone)) {
		frontDrone->attack(humans, gm->getDeathList(), gm->getTimeStep(), printed);
		backDrone->attack(humans, gm->getDeathList(), gm->getTimeStep(), printed);
	}
}