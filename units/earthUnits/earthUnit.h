#pragma once
#include "../unit_Interface.h"

class alienArmy;

class earthUnit : public unit_Interface
{
public:
	earthUnit(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
	//virtual void attack(alienArmy* aliens, int timeStep, bool printed) = 0;
};

