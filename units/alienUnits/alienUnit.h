#pragma once
#include "../unit_Interface.h"
#include "../../basicDataStructures/queue.h"

class earthArmy;
class gameManager;

class alienUnit : public unit_Interface
{
public:
	alienUnit(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
	virtual void attack(gameManager* gm, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	virtual void attack(earthArmy* humans, queue<unit_Interface*>* deathList, int timeStep, bool printed) {};
};

