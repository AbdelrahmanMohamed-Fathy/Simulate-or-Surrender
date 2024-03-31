#pragma once
#include "../earthUnit.h"

class humanTank : public earthUnit
{

public:
	humanTank(int iD, int Hp, int Pr, int Ac, int Tj) : earthUnit(iD, Hp, Pr, Ac, Tj) {};
};

