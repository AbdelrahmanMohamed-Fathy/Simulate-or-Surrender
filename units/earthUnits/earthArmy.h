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
	unsigned int nextFreeID;

	//Units:
	queue<humanSoldier*>* soldiers;
	stack<humanTank*>* tanks;
	priQueue<humanGunner*>* gunners;
public:
	earthArmy(gameManager* GM);
	~earthArmy();

	//Getters:
	queue<humanSoldier*>* getSoldiers();
	stack<humanTank*>* getTanks();
	priQueue<humanGunner*>* getGunners();

	//Adders:
	void addSoldier(int HP, int PW, int AC);
	void addTank(int HP, int PW, int AC);
	void addGunner(int HP, int PW, int AC);
	
	//Miscellaneous:
	bool isEmpty();
	void print();
	void attack(alienArmy* aliens, bool printed);
};

