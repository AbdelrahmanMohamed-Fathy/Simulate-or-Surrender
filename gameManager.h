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
	generator unitGenerator;
	bool earthVictory; // true if humans are the winner, false if aliens are the winner
public:
	gameManager();
	//Starts the program
	void start();

	//Modes:
	void runInteractive();
	void runSilent();
	void testStructures();

	//File management:
	void readInputFile(const string filePath,bool grandSimulation);
	void produceOutputFile();

	//Getters:
	earthArmy* getEarthArmy();
	alienArmy* getAlienArmy();

	//Miscellaneous:
	int CheckWinner();
	void runStep(bool printed);
	void print();
	void generate();
	void fight(bool printed);

	~gameManager();
};

