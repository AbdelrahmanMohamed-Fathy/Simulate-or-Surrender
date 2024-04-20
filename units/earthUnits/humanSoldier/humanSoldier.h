#pragma once
#include "../earthUnit.h"

class humanSoldier : public earthUnit
{

public:
	humanSoldier(int iD, int Hp, int Pr, int Ac, int Tj) : earthUnit(iD, Hp, Pr, Ac, Tj) {};
	virtual void attack(alienArmy* aliens, int timeStep, bool printed);
};

