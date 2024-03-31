#pragma once
#include "../alienUnit.h"

class alienMonster : public alienUnit
{
public:
	alienMonster(int iD, int Hp, int Pr, int Ac, int Tj) : alienUnit(iD, Hp, Pr, Ac, Tj) {};
};