#pragma once
#include "../alienUnit.h"

class alienDrone : public alienUnit
{
public:
	alienDrone(int iD, int Hp, int Pr, int Ac, int Tj) : alienUnit(iD, Hp, Pr, Ac, Tj) {};
	void attack(earthArmy* humans, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	static int getDeathCount();
};