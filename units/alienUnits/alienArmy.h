#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/randomBag.h"
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

	//Units:
	queue<alienSoldier*>* soldiers;
	randomBag<alienMonster*>* monsters;
	deQueue<alienDrone*>* drones;

	//Death Counts:
	unsigned int deathCountAS = 0;
	unsigned int deathCountAD = 0;
	unsigned int deathCountAM = 0;

public:
	alienArmy(gameManager* GM);
	~alienArmy();

	//Getters:
	queue<alienSoldier*>* getSoldiers();
	randomBag<alienMonster*>* getMonsters();
	deQueue<alienDrone*>* getDrones();
	int getDeathCountAS();
	int getDeathCountAD();
	int getDeathCountAM();

	//Setters;
	void setDeathCountAS(int);
	void setDeathCountAD(int);
	void setDeathCountAM(int);

	//Adders: (only for generator use)
	void addSoldier(alienSoldier*& soldier);
	void addMonster(alienMonster*& monster);
	void addDrone(alienDrone*& drone);

	//Miscellaneous:
	bool isEmpty();
	void print();
	void attack(earthArmy* humans, bool printed);
};