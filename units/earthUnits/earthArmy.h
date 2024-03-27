#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/stack.h"
#include "../../basicDataStructures/priQueue.h"

class gameManager;

class earthArmy
{
private:
	gameManager* gm;
	queue<>* soldiers;
	stack<>* tanks;
	priQueue<>* gunners;
	unsigned int nextFreeID;
public:
	//earthArmy();

	//Getters:
	queue<>* getSoldiers();
	stack<>* getTanks();
	priQueue<>* getGunners();

	//Adders:
	void addSoldier();
	void addTank();
	void addGunner();
	
	//Miscellaneous:
	bool isEmpty();
	void print();

	//~earthArmy();
};

