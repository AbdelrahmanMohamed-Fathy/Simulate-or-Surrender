#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/stack.h"
#include "../../basicDataStructures/priQueue.h"
#include "humanSoldier/humanSoldier.h"
#include "humanTank/humanTank.h"
#include "humanGunner/humanGunner.h"
#include "humanHealer/humanHealer.h"

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
	stack<humanHealer*>* healers;

	priQueue<earthUnit*>* unitMaintenanceList;
	
public:
	earthArmy(gameManager* GM);
	~earthArmy();

	//Getters:
	queue<humanSoldier*>* getSoldiers();
	stack<humanTank*>* getTanks();
	priQueue<humanGunner*>* getGunners();
	stack<humanHealer*>* getHealers();
	priQueue<earthUnit*>* getUnitMaintenanceList();

	//Adders:
	void addSoldier(int HP, int PW, int AC);
	void addTank(int HP, int PW, int AC);
	void addGunner(int HP, int PW, int AC);
	void addHealer(int HP, int PW, int AC);
	
	//Miscellaneous:
	bool isEmpty();
	void print();
	void attack(alienArmy* aliens, bool printed);
};

