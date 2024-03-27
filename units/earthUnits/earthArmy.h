#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/stack.h"
#include "../../basicDataStructures/priQueue.h"
#include "humanSoldier/humanSoldier.h"
#include "humanTank/humanTank.h"
#include "humanGunner/humanGunner.h"

class gameManager;

class earthArmy
{
private:
	gameManager* gm;
	queue<humanSoldier*>* soldiers;
	stack<humanTank*>* tanks;
	priQueue<humanGunner*>* gunners;
	unsigned int nextFreeID;
public:
	//earthArmy();

	//Getters:
	queue<humanSoldier*>* getSoldiers();
	stack<humanTank*>* getTanks();
	priQueue<humanGunner*>* getGunners();

	//Adders:
	void addSoldier();
	void addTank();
	void addGunner();
	
	//Miscellaneous:
	bool isEmpty();
	void print();

	//~earthArmy();
};

