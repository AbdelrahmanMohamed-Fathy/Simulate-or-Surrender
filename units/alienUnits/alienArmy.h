#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/bag.h"
#include "../../basicDataStructures/deQueue.h"
#include "alienSoldier/alienSoldier.h"
#include "alienMonster/alienMonster.h"
#include "alienDrone/alienDrone.h"

class gameManager;

class alienArmy
{
private:
	gameManager* gm;
	queue<alienSoldier*>* soldiers;
	bag<alienMonster*>* monsters;
	deQueue<alienDrone*>* drones;
	unsigned int nextFreeID;
public:
	//alienArmy();

	//Getters:
	queue<alienSoldier*>* getSoldiers();
	bag<alienMonster*>* getMonsters();
	deQueue<alienDrone*>* getDrones();

	//Adders:
	void addSoldier();
	void addTank();
	void addGunner();

	//Miscellaneous:
	bool isEmpty();
	void print();

	~alienArmy();
};

