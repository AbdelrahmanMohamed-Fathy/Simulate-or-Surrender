#pragma once
#include "../unit_Interface.h"

class earthArmy;

class alienUnit : public unit_Interface
{
public:
	alienUnit(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
	//virtual void attack(earthArmy* humans, bool printed) = 0;
};

