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
}

alienArmy::~alienArmy()
{
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
int alienArmy::getDeathCountAS()
{
	return deathCountAS;
}
int alienArmy::getDeathCountAD()
{
	return deathCountAD;
}
int alienArmy::getDeathCountAM()
{
	return deathCountAM;
}
void alienArmy::setDeathCountAS(int deathCount)
{
	deathCountAS = deathCount;
}
void alienArmy::setDeathCountAD(int deathCount)
{
	deathCountAD = deathCount;
}
void alienArmy::setDeathCountAM(int deathCount)
{
	deathCountAM = deathCount;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Adders														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alienArmy::addSoldier(alienSoldier*& soldier)
{
	soldiers->enqueue(soldier);
}

void alienArmy::addMonster(alienMonster*& monster)
{
	monsters->addElement(monster);
}

void alienArmy::addDrone(alienDrone*& drone)
{
	if (gm->getTimeStep() % 2 == 0)
		drones->enqueueFront(drone);
	else
		drones->enqueueBack(drone);
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