#pragma once
#include "../earthUnit.h"

class humanSoldier : public earthUnit
{
private:
	bool infected = false;
	bool immune = false;
public:
	humanSoldier(int iD, int Hp, int Pr, int Ac, int Tj) : earthUnit(iD, Hp, Pr, Ac, Tj) {};
	virtual void attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	static int getDeathCount();
	void setInfection(bool infection);
	void setImmunity(bool immunity);
	bool getInfection();
	bool getImmunity();
};

