#include "unit_Interface.h"

unsigned int unit_Interface::deathCount = 0;

string unit_Interface::generateUnitLine() const
{
	return string	( "Td: "  + to_string(destructionTime)
					+ " ID: " + to_string(ID)
					+ " Tj: " + to_string(joinTime)
					+ " Df: " + to_string(firstAttackedDelay)
					+ " Dd: " + to_string(destructionDelay)
					+ " Db: " + to_string(battleTime)
					+ "\n"
					);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Getters														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int unit_Interface::getID() const
{
	return ID;
}

double* unit_Interface::getHP()
{
	return &health;
}

int unit_Interface::getFirstAttackedTime() const
{
	return firstAttackedTime;
}

int unit_Interface::getFirstAttackedDelay() const
{
	return firstAttackedDelay;
}

int unit_Interface::getDestructionDelay() const
{
	return destructionDelay;
}

int unit_Interface::getBattleTime()
{
	return battleTime;
}

int unit_Interface::getDeathCount()
{
	return deathCount;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Setters														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void unit_Interface::setDestructionTime(int dt)
{
	destructionTime = dt;
	destructionDelay = destructionTime - firstAttackedTime;
	battleTime = destructionTime - joinTime;
	deathCount++;
}

void unit_Interface::setFirstAttackedTime(int at)
{
	firstAttackedTime = at;
	firstAttackedDelay = firstAttackedTime - joinTime;
}

