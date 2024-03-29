#pragma once
#include "../../unit_Interface.h"

class humanSoldier : public unit_Interface
{

public:
	humanSoldier(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
};

