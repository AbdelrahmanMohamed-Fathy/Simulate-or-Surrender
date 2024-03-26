#include "unit_Interface.h"

string unit_Interface::generateUnitLine() const
{
	return string	( "Td: "  + to_string(destructionTime)
					+ " ID: " + to_string(ID)
					+ " Tj: " + to_string(joinTime)
					+ " Df: " + to_string(firstAttackDelay)
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Setters														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void unit_Interface::setDestructionTime(int dt)
{
	destructionTime = dt;
	destructionDelay = destructionTime - firstAttackedTime;
	battleTime = destructionTime - joinTime;
}

void unit_Interface::setfirstAttackedTime(int at)
{
	firstAttackedTime = at;
	firstAttackDelay = firstAttackedTime - joinTime;
}

