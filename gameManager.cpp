#include "gameManager.h"
#include "utils/victoryScreens.cpp"
#include "basicDataStructures/queue.cpp"
#include <conio.h>

gameManager::gameManager()
{
	timeStep = 0;
	earthVictory = true;
	structureTest = false;
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
		structureTest = true;
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
	if (!readInputFile(filePath, y))
	{
		cout << "input file failed to read. Exiting program";
		return;
	};
	
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
	if (!structureTest)
		produceOutputFile();
	delete humans;
	delete aliens;

	unit_Interface* temp;
	while (deathList->dequeue(temp))
		delete temp;

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
bool gameManager::readInputFile(const string filePath,bool grandSimulation)
{
	ifstream inputFile(filePath,ios::in);

	int N; int Prob; 
	inputFile >> N >> Prob;
	(grandSimulation) ? (N *= 10):(N=N);
	if (!unitGenerator->assignGeneralParamteres(N, Prob))
	{
		return false;
	};

	int ES; int ET; int EG; int EHU; int HP[2]; int PW[2]; int AC[2];
	inputFile >> ES >> ET >> EG >> EHU >> HP[0] >> HP[1] >> PW[0] >> PW[1] >> AC[0] >> AC[1];
	if (!unitGenerator->assignEarthArmyParamters(ES, ET, EG, EHU, HP, PW, AC))
	{
		return false;
	};

	int AS; int AM; int AD;
	inputFile >> AS >> AM >> AD >> HP[0] >> HP[1] >> PW[0] >> PW[1] >> AC[0] >> AC[1];
	if (!unitGenerator->assignAlienArmyParamters(AS, AM, AD, HP, PW, AC))
	{
		return false;
	};

	inputFile.close();
	return true;
}

void gameManager::produceOutputFile()
{
	ofstream outputFile("Combat Report.txt", ios::out | ios::trunc);
	if (earthVictory)
		outputFile << humanVictoryScreen;
	else
		outputFile << alienVictoryScreen;

	double totalHumanDf = 0; double totalAlienDf = 0; double totalHumanDd = 0; double totalAlienDd = 0; double totalHumanDb = 0; double totalAlienDb = 0;
	outputFile << "\n\nKilled units:\n\n";
	unit_Interface* temp = nullptr;
	while (deathList->dequeue(temp))
	{
		outputFile << temp;
		if (temp->getID() < 1000)
		{
			totalHumanDf += temp->getFirstAttackedDelay();
			totalHumanDd += temp->getDestructionDelay();
			totalHumanDb += temp->getBattleTime();
		}
		else
		{
			totalAlienDf += temp->getFirstAttackedDelay();
			totalAlienDd += temp->getDestructionDelay();
			totalAlienDb += temp->getBattleTime();
		} 
	}

	double humanSoldierCount = humans->getSoldiers()->getCount();
	double humanTankCount = humans->getTanks()->getCount();
	double humanGunnerCount = humans->getGunners()->getCount();
	double totalHumanCount = humanSoldierCount + humanTankCount + humanGunnerCount;
	double humanDeadSoldierCount = humanSoldier::getDeathCount();
	double humanDeadTankCount = humanTank::getDeathCount();
	double humanDeadGunnerCount = humanGunner::getDeathCount();
	double totalHumanDeadCount = humanDeadSoldierCount + humanDeadTankCount + humanDeadGunnerCount;

	outputFile << "Earth army stats:\n"
		<< "Total number of units left: "
		<< humanSoldierCount << " ES, "
		<< humanTankCount << " ET, "
		<< humanGunnerCount << " EG\n"
		<< "Percentage of dead units relative to their total: "
		<< humanDeadSoldierCount / humanSoldierCount << "% ES,"
		<< humanDeadTankCount / humanTankCount << "% ET,"
		<< humanDeadGunnerCount / humanGunnerCount << "% EG\n"
		<< "Percentage of total dead units to total units: "
		<< totalHumanCount / totalHumanDeadCount << "%\n"
		<< "Average delay values: "
		<< totalHumanDf / totalHumanCount << " Df, "
		<< totalHumanDd / totalHumanCount << " Dd, "
		<< totalHumanDb / totalHumanCount << " Db\n"
		<< "Percentage delay values: "
		<< totalHumanDf / totalHumanDb << "% Df/Db, "
		<< totalHumanDd / totalHumanDb << "% Dd/Db\n\n";

	double alienSoldierCount = aliens->getSoldiers()->getCount();
	double alienMonsterCount = aliens->getMonsters()->getCount();
	double alienDroneCount = aliens->getDrones()->getCount();
	double totalAlienCount = alienSoldierCount + alienMonsterCount + alienDroneCount;
	double alienDeadSoldierCount = alienSoldier::getDeathCount();
	double alienDeadMonsterCount = alienMonster::getDeathCount();
	double alienDeadDroneCount = alienDrone::getDeathCount();
	double totalAlienDeadCount = alienDeadSoldierCount + alienDeadMonsterCount + alienDeadDroneCount;

	outputFile << "Alien army stats:\n"
		<< "Total number of units left: "
		<< alienSoldierCount << " AS, "
		<< alienMonsterCount << " AM, "
		<< alienDroneCount << " AD\n"
		<< "Percentage of dead units relative to their total: "
		<< alienDeadSoldierCount / alienSoldierCount << "% AS,"
		<< alienDeadMonsterCount / alienMonsterCount << "% AM,"
		<< alienDeadDroneCount / alienDroneCount << "% AD\n"
		<< "Percentage of total dead units to total units: "
		<< totalAlienCount / totalAlienDeadCount << "%\n"
		<< "Average delay values: "
		<< totalAlienDf / totalAlienCount << " Df, "
		<< totalAlienDd / totalAlienCount << " Dd, "
		<< totalAlienDb / totalAlienCount << " Db\n"
		<< "Percentage delay values: "
		<< totalAlienDf / totalAlienDb << "% Df/Db, "
		<< totalAlienDd / totalAlienDb << "% Dd/Db\n";

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
	cout << deathList->getCount() << " units: ";
	deathList->print();
}

void gameManager::fight(bool printed)
{
	humans->attack(aliens, printed);
	aliens->attack(humans, printed);
}