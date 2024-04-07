#include "humanHealer.h"

priQueue<earthUnit*>* unitMaintenanceList = new priQueue<earthUnit*>;

priQueue<earthUnit*>* humanHealer::getunitMaintenanceList()
{
    return unitMaintenanceList;
}
