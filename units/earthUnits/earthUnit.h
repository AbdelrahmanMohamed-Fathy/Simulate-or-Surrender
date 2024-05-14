#pragma once
#include "../unit_Interface.h"
#include "../../basicDataStructures/queue.h"

class alienArmy;

class earthUnit : public unit_Interface
{
protected:
	const int maxHealth;
	int maintenanceWaitStartTime;
	bool infected = false;
	bool immune = false;
public:
	earthUnit(int iD, int Hp, int Pr, int Ac, int Tj) : unit_Interface(iD, Hp, Pr, Ac, Tj), maxHealth(Hp) {};
	virtual void attack(gameManager* gm, queue<unit_Interface*>* deathList, int timeStep, bool printed);
	virtual void attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed) {};
	void setMaintenanceWaitStartTime(int timeStep);
	int getMaintenanceWaitStartTime();
	bool checkMaintenanceListViability();
	void setInfection(bool infection);
	void setImmunity(bool immunity);
	bool getInfection() const;
	bool getImmunity() const;
};

static ostream& operator<<(ostream& out, const earthUnit& soldier)
{
	if (soldier.getInfection())
	{
		out << soldier.getID() << "*";
		return out;
	}
	else
	{
		out << soldier.getID();
		return out;
	}
}