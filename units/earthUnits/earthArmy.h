#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/stack.h"
#include "../../basicDataStructures/priQueue.h"
#include "../../gameManager.h"

class earthArmy
{
private:
	gameManager* gm;
	queue<>* Soldiers;
	stack<>* Tanks;
	priQueue<>* Gunners;
public:
	earthArmy();

	queue<>* getSoldiers();
	stack<>* getTanks();
	priQueue<>* getGunners();

	~earthArmy();
};

