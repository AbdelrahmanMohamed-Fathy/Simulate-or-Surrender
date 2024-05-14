#pragma once
#include "../../unit_Interface.h"

class alienArmy;
class gameManager;

class saviourUnit : public unit_Interface
{
private:
	bool infected = false;
	bool immune = true;
public:
	saviourUnit(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj) {};
	virtual void attack(gameManager* gm, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	virtual void attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	void setInfection(bool infection);
	void setImmunity(bool immunity);
	bool getInfection() const;
	bool getImmunity() const;
};

