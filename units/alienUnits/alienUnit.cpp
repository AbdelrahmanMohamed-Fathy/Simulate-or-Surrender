#include "alienUnit.h"
#include "../../gameManager.h"

void alienUnit::attack(gameManager* gm, queue<unit_Interface*>* deathList, int timeStep, bool printed)
{
	attack(gm->getEarthArmy(), deathList, timeStep, printed);
}