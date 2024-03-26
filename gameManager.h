#pragma once
#include "units/alienUnits/alienArmy.h"
#include "units/earthUnits/earthArmy.h"
#include "units/unit_Interface.h"
#include "utils/victoryScreens.cpp"
#include "generator.h"
#include <conio.h>

class gameManager
{
private:
	int TimeStep;
	earthArmy humans;
	alienArmy aliens;
	queue<unit_Interface*> deathList;
	generator unitGenerator;
	bool earthVictory; // true if humans are the winner, false if aliens are the winner
public:
	//Starts the program
	void start();

	//Modes:
	void runInteractive();
	void runSilent();

	//File management:
	void readInputFile(const string filePath,bool grandSimulation);
	void produceOutputFile();

	//Getters:
	earthArmy* getEarthArmy();
	alienArmy* getAlienArmy();

	//Miscellaneous:
	int CheckWinner();

	~gameManager();
};

