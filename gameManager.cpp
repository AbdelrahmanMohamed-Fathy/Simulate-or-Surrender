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
	helldivers = new allyArmy(this);
	unitGenerator = new generator(this);
	deathList = new queue<unit_Interface*>();
}

gameManager::~gameManager()
{
	if (!structureTest)
		produceOutputFile();
	delete humans;
	delete aliens;
	delete helldivers;

	delete deathList;
	delete unitGenerator;
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
		<< "(4) strongEarth, ModerateAliens\n"
		<< "(5) weakEarth, ModerateAliens\n"
		<< "(6) data-structure test\n";
	
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
		filePath += "strongEarth_moderateAliens.txt";
		break;
	case 5:
		filePath += "weakEarth_moderateAliens.txt";
		break;
	case 6:
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
	cout << "Simulation running...\n";
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
		unitGenerator->generate(timeStep);
		int x = generateNumber();
		if (x >= 1 && x <= 10)
		{
			humanSoldier* soldier;
			if (humans->getSoldiers()->dequeue(soldier))
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
			double* health;
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
				if (aliens->getMonsters()->remove(monster))
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

		system("cls");
		printAlive();
		printDead();
		cout << "press any key to continue.\n";
		_getch();
		timeStep++;
	}
	return;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												File management													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Input file format:
{N} {Prob} {infectProb} {saviourThreshHold}

{Earth unit percentages}
{health range}
{power range}
{attack capacity range}

{health range}
{power range}
{attack capacity range}

{Alien unit percentages}
{health range}
{power range}
{attack capacity range}
*/
bool gameManager::readInputFile(const string filePath,bool grandSimulation)
{
	ifstream inputFile(filePath,ios::in);

	int N; int Prob; int infectProb; int saviourThreshHold;
	inputFile >> N >> Prob >> infectProb >> saviourThreshHold;
	(grandSimulation) ? (N *= 10):(N=N);
	if (!unitGenerator->assignGeneralParamteres(N, Prob))
	{
		return false;
	};
	humans->setEmergencyThreshhold(saviourThreshHold);

	int ES; int ET; int EG; int EH; int HP[2]; int PW[2]; int AC[2];
	inputFile >> ES >> ET >> EG >> EH;
	(inputFile >> HP[0]).ignore(1) >> HP[1];
	(inputFile >> PW[0]).ignore(1) >> PW[1];
	(inputFile >> AC[0]).ignore(1) >> AC[1];
	if (!unitGenerator->assignEarthArmyParamters(ES, ET, EG, EH, HP, PW, AC))
	{
		return false;
	};

	(inputFile >> HP[0]).ignore(1) >> HP[1];
	(inputFile >> PW[0]).ignore(1) >> PW[1];
	(inputFile >> AC[0]).ignore(1) >> AC[1];
	if (!unitGenerator->assignAllyArmyParamters(HP, PW, AC))
	{
		return false;
	};

	int AS; int AM; int AD;
	inputFile >> AS >> AM >> AD;
	(inputFile >> HP[0]).ignore(1) >> HP[1];
	(inputFile >> PW[0]).ignore(1) >> PW[1];
	(inputFile >> AC[0]).ignore(1) >> AC[1];
	if (!unitGenerator->assignAlienArmyParamters(AS, AM, AD, HP, PW, AC, infectProb))
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
	outputFile << "\n\nFinal timestep: " << timeStep << endl;
	outputFile << "Killed units:\n";
	unit_Interface* temp = nullptr;
	while (deathList->dequeue(temp))
	{
		outputFile << temp;
		if (temp->getID() < 2000)
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
	outputFile << endl;

	double humanSoldierCount = humans->getSoldiers()->getCount();
	double humanTankCount = humans->getTanks()->getCount();
	double humanGunnerCount = humans->getGunners()->getCount();
	double humanHealerCount = humans->getHealers()->getCount();
	double totalHumanCount = humanSoldierCount + humanTankCount + humanGunnerCount + humanHealerCount;
	double humanDeadSoldierCount = humans->getDeathCountES();
	double humanDeadTankCount = humans->getDeathCountET();
	double humanDeadGunnerCount = humans->getDeathCountEG();
	double humanDeadHealerCount = humans->getDeathCountEH();
	double totalHumanDeadCount = humanDeadSoldierCount + humanDeadTankCount + humanDeadGunnerCount + humanDeadHealerCount;

	outputFile << "Earth army stats:\n"
		<< "Total number of units left: "
		<< humanSoldierCount << " ES, "
		<< humanTankCount << " ET, "
		<< humanGunnerCount << " EG, "
		<< humanHealerCount << " EH\n"
		<< "Percentage of dead units relative to their total: "
		<< humanDeadSoldierCount / (humanSoldierCount + humanDeadSoldierCount) * 100 << "% ES,"
		<< humanDeadTankCount / (humanTankCount + humanDeadTankCount) * 100 << "% ET,"
		<< humanDeadGunnerCount / (humanGunnerCount + humanDeadGunnerCount) * 100 << "% EG,"
		<< humanDeadHealerCount / (humanHealerCount + humanDeadHealerCount) * 100 << "% EH\n"
		<< "Percentage of total dead units to total units: "
		<< totalHumanDeadCount / (totalHumanCount + totalHumanDeadCount) * 100 << "%\n"
		<< "Percentage of total infected units: " << humans->getTotalInfectionCountES() / (humanDeadSoldierCount)+(humanSoldierCount) << "%\n"
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
	double alienDeadSoldierCount = aliens->getDeathCountAS();
	double alienDeadMonsterCount = aliens->getDeathCountAM();
	double alienDeadDroneCount = aliens->getDeathCountAD();
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

allyArmy* gameManager::getAllyArmy()
{
	return helldivers;
}

queue<unit_Interface*>* gameManager::getDeathList()
{
	return deathList;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												Miscellaneous													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gameManager::signalForHelp(bool rescueNeeded)
{
	unitGenerator->setEmergencyState(rescueNeeded);
}

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
	unitGenerator->generate(timeStep);
	if (printed) printAlive();
	fight(printed);
	if (printed) printDead();
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
	helldivers->attack(aliens, printed);
	aliens->attack(humans, printed);
	if (printed) cout << endl;
}