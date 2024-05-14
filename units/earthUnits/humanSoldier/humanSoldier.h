#pragma once
#include "../earthUnit.h"

class humanSoldier : public earthUnit
{
private:
	
public:
	humanSoldier(int iD, int Hp, int Pr, int Ac, int Tj) : earthUnit(iD, Hp, Pr, Ac, Tj) {};
	virtual void attack(gameManager* gm, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	static int getDeathCount();
	void setInfection(bool infection);
	void setImmunity(bool immunity);
	bool getInfection() const;
	bool getImmunity() const;
};

static ostream& operator<<(ostream& out, const humanSoldier* soldier)
{
    if (soldier->getInfection())
    {
        out << soldier->getID() << "*";
        return out;
    }
    else
    {
        out << soldier->getID();
        return out;
    }
}



