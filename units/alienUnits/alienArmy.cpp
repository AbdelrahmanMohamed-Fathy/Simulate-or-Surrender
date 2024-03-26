#include "alienArmy.h"

bool alienArmy::isEmpty()
{
	if (soldiers.isEmpty() && monsters.isEmpty() && drones.isEmpty())
		return true;
	return false;
}