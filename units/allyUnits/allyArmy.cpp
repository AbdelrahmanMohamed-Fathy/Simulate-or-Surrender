#include "allyArmy.h"
#include "../../gameManager.h"

allyArmy::allyArmy(gameManager* GM) : gm(GM)
{
	saviours = new queue<saviourUnit*>;
}

allyArmy::~allyArmy()
{
	delete saviours;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Getters														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool allyArmy::getRescueState()
{
	return rescueRequired;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Setters														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void allyArmy::setRescue(bool needRescue)
{
	rescueRequired = needRescue;
	if (!needRescue)
	{
		delete saviours;
		saviours = new queue<saviourUnit*>;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Adders														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void allyArmy::addSaviour(saviourUnit*& saviour)
{
	saviours->enqueue(saviour);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Miscellaneous													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool allyArmy::isEmpty()
{
	return saviours->isEmpty();
}

void allyArmy::print()
{
	cout << "================================= ally army unit =================================\n";
	cout << saviours->getCount() << " Saviours: ";
	saviours->print();
	cout << endl;
}

void allyArmy::attack(alienArmy* aliens, bool printed)
{
	//Saviour unit:
	saviourUnit* saviour;
	if (saviours->peek(saviour)) {
		saviour->attack(aliens, gm->getDeathList(), gm->getTimeStep(), printed);
	}
}