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
	void addSoldier(int HP, int PW, int AC);
	void addMonster(int HP, int PW, int AC);
	void addDrone(int HP, int PW, int AC);

	//Miscellaneous:
	bool isEmpty();
	void print();
	void attack(earthArmy* humans, bool printed);

	~alienArmy();
};

