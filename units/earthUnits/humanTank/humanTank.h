#pragma once
#include "../earthUnit.h"

class humanTank : public earthUnit
{
private:
	static unsigned int deathCount;
	static bool pctCheck;
public:
	humanTank(int iD, int Hp, int Pr, int Ac, int Tj) : earthUnit(iD, Hp, Pr, Ac, Tj) {};
	static void setpctCheck(bool set);
	static bool getpctCheck();
	void attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	static int getDeathCount();
};

