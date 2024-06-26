#pragma once
#include "../earthUnit.h"
#include "../../basicDataStructures/priQueue.h"

class humanHealer : public earthUnit
{
private:
	static priQueue<earthUnit*>* unitMaintenanceList;
public:
	humanHealer(int iD, int Hp, int Pr, int Ac, int Tj) : earthUnit(iD, Hp, Pr, Ac, Tj) {};
	static priQueue<earthUnit*>* getUnitMaintenanceList();
	static void setUnitMaintenanceList(priQueue<earthUnit*>* unitMaintenanceList);
	void attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	static int getDeathCount();
};

