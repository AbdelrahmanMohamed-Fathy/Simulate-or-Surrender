#include "earthUnit.h"

void earthUnit::setMaintenanceWaitStartTime(int timeStep)
{
	maintenanceWaitStartTime = timeStep;
}

int earthUnit::getMaintenanceWaitStartTime() {
	return maintenanceWaitStartTime;
}