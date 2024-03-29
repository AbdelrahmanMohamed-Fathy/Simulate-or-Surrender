#pragma once
#include "../../unit_Interface.h"

class alienDrone : public unit_Interface
{
public:
	alienDrone(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
};

