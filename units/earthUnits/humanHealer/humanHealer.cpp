#include "humanHealer.h"

priQueue<earthUnit*>* humanHealer::unitMaintenanceList = nullptr;

priQueue<earthUnit*>* humanHealer::getUnitMaintenanceList()
{
    return unitMaintenanceList;
}

void humanHealer::setUnitMaintenanceList(priQueue<earthUnit*>* UML)
{
    unitMaintenanceList = UML;
}
