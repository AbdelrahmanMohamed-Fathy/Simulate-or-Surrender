#include "gameManager.h"
#include "utils/victoryScreens.cpp"
#include "basicDataStructures/queue.cpp"
#include <conio.h>


gameManager::gameManager()
{
	srand(100);
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
		<< "(3) weakEarth, weakAliens\n"
		<< "(4) data-structure test\n";
	
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
		if (!readInputFile(filePath + "TEST.txt", false))
		{
			cout << "input file failed to read. Exiting program";
			return;
		};
		cout << "initiating data-structure test.\n";
		srand(1020);
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
		srand(1020);
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
		runStep(true);
		printDead();
		cout << "press any key to continue.\n\n\n\n";
		_getch();
		system("cls");
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
	cout << "Press any key to start test.\n";
	_getch();
	while (timeStep != 50)
	{
		unitGenerator->generate();
		int x = generateNumber();
		if (x >= 1 && x <= 10)
		{
			humanSoldier* soldier;
			if(humans->getSoldiers()->dequeue(soldier))
				(humans->getSoldiers())->enqueue(soldier);
		}
		if (x >= 11 && x <= 20)
		{
			humanTank* tank;
			if ((humans->getTanks())->pop(tank))
			{
				deathList->enqueue(tank);
			}
		}
		if (x >= 21 && x <= 30)
		{
			double* health;
			double dummy;
			humanGunner* gunner;
			if (humans->getGunners()->dequeue(gunner, dummy))
			{
				health = gunner->getHP();
				*health /= 2;
				humans->getGunners()->enqueue(gunner, gunner->getPriority());
			}
		}
		if (x >= 31 && x <= 40) {
			alienSoldier* solider;
			double *health;
			queue<alienSoldier*>* temp;
			temp = new queue<alienSoldier*>;
			for (int i = 0; i < 5; i++) {
				if (aliens->getSoldiers()->dequeue(solider))
				{
					health = solider->getHP();
					health -= 30;
					temp->enqueue(solider);
					temp->dequeue(solider);
					aliens->getSoldiers()->enqueue(solider);
				}
			}
			delete temp;
		}
		if (x >= 41 && x <= 50) {
			alienMonster* monster;
			for (int i = 0; i < 5; i++) {
				if(aliens->getMonsters()->remove(monster))
					(aliens->getMonsters())->addElement(monster);
			}
		}
		if (x >= 51 && x < 60) {
			alienDrone* drone;
			for (int i = 0; i < 3; i++) {
				if ((aliens->getDrones())->dequeuefront(drone))
					deathList->enqueue(drone);
			}

			for (int i = 0; i < 3; i++) {
				if ((aliens->getDrones())->dequeueback(drone))
					deathList->enqueue(drone);
			}
		}

		cout << "==================================================================================\n\n";
		printAlive();
		printDead();
		cout << "press any key to continue.\n\n\n\n";
		_getch();
		timeStep++;
	}
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

	int ES; int ET; int EG; int EH; int HP[2]; int PW[2]; int AC[2];
	inputFile >> ES >> ET >> EG >> EH;
	(inputFile >> HP[0]).ignore(1) >> HP[1];
	(inputFile >> PW[0]).ignore(1) >> PW[1];
	(inputFile >> AC[0]).ignore(1) >> AC[1];
	if (!unitGenerator->assignEarthArmyParamters(ES, ET, EG, EH, HP, PW, AC))
	{
		return false;
	};

	int AS; int AM; int AD;

	inputFile >> AS >> AM >> AD;
	(inputFile >> HP[0]).ignore(1) >> HP[1];
	(inputFile >> PW[0]).ignore(1) >> PW[1];
	(inputFile >> AC[0]).ignore(1) >> AC[1];
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
		<< humanDeadSoldierCount / (humanSoldierCount + humanDeadSoldierCount) * 100 << "% ES,"
		<< humanDeadTankCount / (humanTankCount + humanDeadTankCount) * 100 << "% ET,"
		<< humanDeadGunnerCount / (humanGunnerCount + humanDeadGunnerCount) * 100 << "% EG\n"
		<< "Percentage of total dead units to total units: "
		<< totalHumanDeadCount / (totalHumanCount + totalHumanDeadCount) * 100 << "%\n"
		<< "Average delay values: "
		<< totalHumanDf / totalHumanCount << " Df, "
		<< totalHumanDd / totalHumanCount << " Dd, "
		<< totalHumanDb / totalHumanCount << " Db\n"
		<< "Percentage delay values: "
		<< totalHumanDf / totalHumanDb * 100 << "% Df/Db, "
		<< totalHumanDd / totalHumanDb * 100 << "% Dd/Db\n\n";

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
		<< alienDeadSoldierCount / (alienSoldierCount + alienDeadSoldierCount) * 100 << "% AS,"
		<< alienDeadMonsterCount / (alienMonsterCount + alienDeadMonsterCount) * 100 << "% AM,"
		<< alienDeadDroneCount / (alienDroneCount + alienDeadDroneCount) * 100 << "% AD\n"
		<< "Percentage of total dead units to total units: "
		<<  totalAlienDeadCount / (totalAlienCount + totalAlienDeadCount)  * 100 << "%\n"
		<< "Average delay values: "
		<< totalAlienDf / totalAlienCount << " Df, "
		<< totalAlienDd / totalAlienCount << " Dd, "
		<< totalAlienDb / totalAlienCount << " Db\n"
		<< "Percentage delay values: "
		<< totalAlienDf / totalAlienDb * 100 << "% Df/Db, "
		<< totalAlienDd / totalAlienDb * 100 << "% Dd/Db\n";

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

queue<unit_Interface*>* gameManager::getDeathList()
{
	return deathList;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Miscellaneous													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int gameManager::CheckWinner()
{
	if (timeStep < 40)
	{
		return 0;
	}
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
	if(printed) printAlive();
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
	if (printed)
	{
		cout << "======================= Units fighting at current timestep =======================\n";
	}
	humans->attack(aliens, printed);
	aliens->attack(humans, printed);
}

