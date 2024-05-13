#pragma once
#include "../alienUnit.h"

class alienMonster : public alienUnit
{
private:
	int infectionRate;
public:
	alienMonster(int iD, int Hp, int Pr, int Ac, int Ir, int Tj) : alienUnit(iD, Hp, Pr, Ac, Tj) { infectionRate = Ir; };
	void attack(earthArmy* humans, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	static int getDeathCount();
};