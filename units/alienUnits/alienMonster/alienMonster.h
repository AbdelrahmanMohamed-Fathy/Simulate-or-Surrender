#pragma once
#include "../../unit_Interface.h"

class alienMonster : public unit_Interface
{
public:
	alienMonster(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
};

