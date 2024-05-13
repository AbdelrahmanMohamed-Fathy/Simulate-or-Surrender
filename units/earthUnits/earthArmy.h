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

	//Units:
	queue<humanSoldier*>* soldiers;
	stack<humanTank*>* tanks;
	priQueue<humanGunner*>* gunners;
	stack<humanHealer*>* healers;

	//Death Counts:
	unsigned int deathCountES = 0;
	unsigned int deathCountET = 0;
	unsigned int deathCountEG = 0;
	unsigned int deathCountEH = 0;

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
	int getDeathCountET();
	int getDeathCountEG();
	int getDeathCountES();
	int getDeathCountEH();

	//Setters:
	void setDeathCountET(int);
	void setDeathCountEG(int);
	void setDeathCountES(int);
	void setDeathCountEH(int);

	//Adders: (only for generator use)
	void addSoldier(humanSoldier*& soldier);
	void addTank(humanTank*& tank);
	void addGunner(humanGunner*& gunner);
	void addHealer(humanHealer*& healer);
	void addToMaintenance(earthUnit*& human, double pri);
	
	//Miscellaneous:
	bool isEmpty();
	void print();
	void attack(alienArmy* aliens, bool printed);
};