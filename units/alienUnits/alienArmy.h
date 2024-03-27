#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/bag.h"
#include "../../basicDataStructures/deQueue.h"
#include "alienSoldier/alienSoldier.h"
#include "alienMonster/alienMonster.h"
#include "alienDrone/alienDrone.h"

class gameManager;
class earthArmy;

class alienArmy
{
private:
	gameManager* gm;
	queue<alienSoldier*>* soldiers;
	bag<alienMonster*>* monsters;
	deQueue<alienDrone*>* drones;
	unsigned int nextFreeID;
public:
	alienArmy(gameManager* GM);

	//Getters:
	queue<alienSoldier*>* getSoldiers();
	bag<alienMonster*>* getMonsters();
	deQueue<alienDrone*>* getDrones();

	//Adders:
	void addSoldier();
	void addMonster();
	void addDrone();

	//Miscellaneous:
	bool isEmpty();
	void print();
	void attack(earthArmy* humans, bool printed);

	~alienArmy();
};

