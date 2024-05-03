#include "earthUnit.h"

void earthUnit::setMaintenanceWaitStartTime(int timeStep)
{
	maintenanceWaitStartTime = timeStep;
}

bool earthUnit::checkMaintenanceListViability()
{
	if (health < maxHealth * 0.2) 
		return true;
	return false;
}
