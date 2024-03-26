#pragma once
#include "units/alienUnits/alienArmy.h"
#include "units/earthUnits/earthArmy.h"
#include "units/unit_Interface.h"
#include <string>
#include <fstream>

class gameManager
{
private:
	int time;
	earthArmy humans;
	alienArmy aliens;
	queue<unit_Interface> deathList;
public:
	//Starts the program
	void start();

	//Modes:
	void runInteractive();
	void runSilent();

	//File management:
	void readInputFile();
	void produceOutputFile();

	//Getters:
	earthArmy* getEarthArmy();
	alienArmy* getAlienArmy();

	~gameManager();
};

