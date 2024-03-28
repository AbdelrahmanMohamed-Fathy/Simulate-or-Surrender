#include "gameManager.h"
#include "utils/victoryScreens.cpp"
#include "basicDataStructures/queue.cpp"
#include <conio.h>

gameManager::gameManager()
{
	timeStep = 0;
	earthVictory = true;
	humans = new earthArmy(this);
	aliens = new alienArmy(this);
	unitGenerator = new generator(this);
	deathList = new queue<unit_Interface*>();
}

void gameManager::start()
{
	int x; bool y;
	string filePath = "scenarios/";
	cout << "Welcome to the simulation, which scenario would you like to run?\n"
		<< "(0) strongEarth, strongAliens\n"
		<< "(1) strongEarth, weakAliens\n"
		<< "(2) weakEarth, StrongAliens\n"
		<< "(3) weakEarth, weakAliens\n";
	
	cin >> x;
	switch (x)
	{
	case 0:
		filePath += "strongEarth_strongAliens.txt";
		break;
	case 1:
		filePath += "strongEarth_weakAliens.txt";
		break;
	case 2:
		filePath += "weakEarth_strongAliens.txt";
		break;
	case 3:
		filePath += "weakEarth_weakAliens.txt";
		break;
	case 4:
		system("cls");
		cout << "initiating secret data-structure test.";
		testStructures();
		return;
	default:
		cout << "Invalid input, defaulting to case (0).\n";
	}

	cout	<< "do you wish to run a simple simulation or a grand simulation?\n"
			<< "(0) Simple simulation\n"
			<< "(1) Grand simulation\n";

	cin >> y;
	readInputFile(filePath,y);
	
	cout	<< "do you wish to run the test seed or a random seed?\n"
			<< "(0) test seed\n"
			<< "(1) random seed\n";

	cin >> x;
	switch (x)
	{
	case 0:
		srand(100);
		break;
	case 1:
		srand(time(NULL));
		break;
	default:
		cout << "Invalid input, defaulting to case (1).\n";
	}
	
	cout	<< "do you wish to run in interactive mode or silent mode?\n"
			<< "(0) Interactive mode\n"
			<< "(1) Silent mode\n";

	cin >> x;
	switch (x)
	{
	case 0:
		system("cls");
		runInteractive();
		break;
	case 1:
		system("cls");
		runSilent();
		break;
	default:
		cout << "Invalid input, defaulting to case (0).\n";
		system("cls");
		runInteractive();
	}
	cout << "Simulation complete.";
	return;
}

gameManager::~gameManager()
{
	produceOutputFile();
	delete humans;
	delete aliens;
	delete deathList;
	delete unitGenerator;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Modes														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gameManager::runInteractive()
{
	cout << "Press any key to start simulation.\n";
	_getch();
	while (CheckWinner()==0)
	{
		system("cls");
		printAlive();
		runStep(true);
		printDead();
		cout << "press any key to continue.\n";
		_getch();
	}
	return;
}

void gameManager::runSilent()
{
	cout << "Press any key to start simulation.\n";
	_getch();
	while (CheckWinner() == 0)
	{
		runStep(false);
	}
	return;
}

void gameManager::testStructures()
{
	return;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												File management													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gameManager::readInputFile(const string filePath,bool grandSimulation)
{
	ifstream inputFile(filePath,ios::in);



	inputFile.close();
}

void gameManager::produceOutputFile()
{
	ofstream outputFile("Combat Report.txt", ios::out | ios::trunc);
	if (earthVictory)
		outputFile << humanVictoryScreen;
	else
		outputFile << alienVictoryScreen;

	outputFile << "\n\nKilled units:\n";
	unit_Interface* temp = nullptr;
	while (deathList->dequeue(temp))
		outputFile << *temp;


	outputFile.close();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Getters														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int gameManager::getTimeStep()
{
	return timeStep;
}
earthArmy* gameManager::getEarthArmy()
{
	return humans;
}

alienArmy* gameManager::getAlienArmy()
{
	return aliens;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Miscellaneous													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int gameManager::CheckWinner()
{
	if (deathList->isEmpty())
	{
		return 0;
	}
	if (aliens->isEmpty())
	{
		earthVictory = true;
		return 1;
	}
	if (humans->isEmpty())
	{
		earthVictory = false;
		return 2;
	}
	return 0;
}

void gameManager::runStep(bool printed)
{
	unitGenerator->generate();
	fight(printed);
	timeStep++;
}

void gameManager::printAlive()
{
	cout << "current timestep: " << timeStep << endl;
	humans->print();
	aliens->print();
}

void gameManager::printDead()
{
	cout << "================================== Killed units ==================================\n";
	deathList->print();
}

void gameManager::fight(bool printed)
{
	humans->attack(aliens, printed);
	aliens->attack(humans, printed);
}