#include "earthUnit.h"
#include "../../gameManager.h"

void earthUnit::setMaintenanceWaitStartTime(int timeStep)
{
	maintenanceWaitStartTime = timeStep;
}

int earthUnit::getMaintenanceWaitStartTime() {
	return maintenanceWaitStartTime;
}

bool earthUnit::checkMaintenanceListViability()
{
	if (health < maxHealth * 0.2) 
		return true;
	return false;
}

void earthUnit::attack(gameManager* gm, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
	attack(gm->getAlienArmy(), deathList, timeStep, printed);
}

bool earthUnit::getImmunity() const
{
	return immune;
}

bool earthUnit::getInfection() const
{
	return infected;
}

void earthUnit::setImmunity(bool immunity)
{
	immune = immunity;
}

void earthUnit::setInfection(bool infection)
{
	infected = infection;
}