#pragma once
#include "../../unit_Interface.h"

class humanGunner : public unit_Interface
{
public:
	humanGunner(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
};

