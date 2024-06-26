#pragma once
#include "../unit_Interface.h"
#include "../../basicDataStructures/queue.h"

class alienArmy;

class earthUnit : public unit_Interface
{
protected:
	const int maxHealth;
public:
	earthUnit(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj), maxHealth(Hp) {};
	virtual void attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed) = 0;
};

