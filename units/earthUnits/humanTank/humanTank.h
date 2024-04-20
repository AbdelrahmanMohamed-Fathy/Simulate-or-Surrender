#pragma once
#include "../earthUnit.h"

class humanTank : public earthUnit
{
	static bool pctcheck;
	static int* EScount;
public:
	humanTank(int iD, int Hp, int Pr, int Ac, int Tj) : earthUnit(iD, Hp, Pr, Ac, Tj) {};
	void attack(alienArmy* aliens, int timeStep, bool printed, queue<unit_Interface*>* deathList);
};

