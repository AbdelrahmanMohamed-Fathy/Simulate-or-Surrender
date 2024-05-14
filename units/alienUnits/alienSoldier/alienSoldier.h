#pragma once
#include "../alienUnit.h"

class alienSoldier : public alienUnit
{
public:
	alienSoldier(int iD, int Hp, int Pr, int Ac, int Tj) : alienUnit(iD, Hp, Pr, Ac, Tj) {};
	virtual void attack(earthArmy* humans, queue<unit_Interface*>* deathList,int timeStep, bool printed);
};