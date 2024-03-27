#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/stack.h"
#include "../../basicDataStructures/priQueue.h"
#include "humanSoldier/humanSoldier.h"
#include "humanTank/humanTank.h"
#include "humanGunner/humanGunner.h"

class gameManager;
class alienArmy;

class earthArmy
{
private:
	gameManager* gm;
	queue<humanSoldier*>* soldiers;
	stack<humanTank*>* tanks;
	priQueue<humanGunner*>* gunners;
	unsigned int nextFreeID;
public:
	earthArmy(gameManager* GM);

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
	void attack(alienArmy* aliens, bool printed);

	~earthArmy();
};

