#include "humanGunner.h"

double humanGunner::getPriority()
{
    return (double)power*(health/100.0);
}
