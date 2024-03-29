#pragma once
#include "../../unit_Interface.h"

class alienSoldier : public unit_Interface
{
public:
	alienSoldier(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
};

