#pragma once
#include "../earthUnit.h"

class humanSoldier : public earthUnit
{
private:
	
public:
	humanSoldier(int iD, int Hp, int Pr, int Ac, int Tj) : earthUnit(iD, Hp, Pr, Ac, Tj) {};
	virtual void attack(gameManager* gm, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	void setInfection(bool infection);
	void setImmunity(bool immunity);
	bool getInfection() const;
	bool getImmunity() const;
};



