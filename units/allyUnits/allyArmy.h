#pragma once
#include "saviourUnit/saviourUnit.h"


class allyArmy
{
private:
	gameManager* gm;

	queue<saviourUnit*>* saviours;

	bool rescueRequired;
public:
	allyArmy(gameManager* GM);
	~allyArmy();

	//Getters:
	bool getRescueState();

	//Setters:
	void setRescue(bool needRescue);

	//Adders: (only for generator use)
	void addSaviour(saviourUnit*& saviour);

	//Miscellaneous:
	bool isEmpty();
	void print();
	void attack(alienArmy* aliens, bool printed);
};

