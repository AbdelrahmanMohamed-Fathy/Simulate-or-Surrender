#pragma once
#include "units/alienUnits/alienArmy.h"
#include "units/earthUnits/earthArmy.h"
#include "units/unit_Interface.h"
#include "generator.h"

class gameManager
{
private:
	int timeStep;
	earthArmy* humans;
	alienArmy* aliens;
	queue<unit_Interface*>* deathList;
	generator* unitGenerator;
	bool earthVictory;	// true if humans are the winner, false if aliens are the winner
	bool structureTest;	// true if the manager is instructed to run the structure test instead of a normal test
public:
	gameManager();
	~gameManager();

	//Starts the program
	void start();

	//Modes:
	void runInteractive();
	void runSilent();
	void testStructures();

	//File management:
	bool readInputFile(const string filePath,bool grandSimulation);
	void produceOutputFile();

	//Getters:
	int getTimeStep();
	earthArmy* getEarthArmy();
	alienArmy* getAlienArmy();

	//Miscellaneous:
	int CheckWinner();
	void runStep(bool printed);
	void printAlive();
	void printDead();
	void fight(bool printed);
};

