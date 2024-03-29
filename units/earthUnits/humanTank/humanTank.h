#pragma once
#include "../../unit_Interface.h"

class humanTank : public unit_Interface
{

public:
	humanTank(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
};

