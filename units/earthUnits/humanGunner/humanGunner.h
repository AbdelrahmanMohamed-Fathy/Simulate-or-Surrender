#pragma once
#include "../earthUnit.h"

class humanGunner : public earthUnit
{
public:
	humanGunner(int iD, int Hp, int Pr, int Ac, int Tj) : earthUnit(iD, Hp, Pr, Ac, Tj) {};
	void attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	double getPriority();
};

