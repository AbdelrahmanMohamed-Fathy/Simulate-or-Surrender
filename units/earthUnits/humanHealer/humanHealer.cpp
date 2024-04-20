#include "humanHealer.h"
#include "../../alienUnits/alienArmy.h"

priQueue<earthUnit*>* humanHealer::unitMaintenanceList = nullptr;

priQueue<earthUnit*>* humanHealer::getUnitMaintenanceList()
{
    return unitMaintenanceList;
}

void humanHealer::setUnitMaintenanceList(priQueue<earthUnit*>* UML)
{
    unitMaintenanceList = UML;
}

void humanHealer::attack(alienArmy* aliens, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
}
