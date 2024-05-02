#include "generator.h"
#include "gameManager.h"
#include "utils/generateNumber.cpp"
#include "basicDataStructures/queue.cpp"

generator::generator(gameManager* GM, int humanIDStart, int alienIDStart) : gm(GM), humanNextFreeID(humanIDStart), alienNextFreeID(alienIDStart)
{
}

generator::~generator()
{
	unit_Interface* temp;
	while (units.dequeue(temp))
		delete temp;
}

bool generator::assignGeneralParamteres(int N, int Prob)
{
	if ((N > 0) && (Prob > 0))
	{
		generationProbability = Prob;
		generationCount = N;
		return true;
	}
	return false;
}

bool generator::assignEarthArmyParamters(int ES, int ET, int EG, int EHU, int HP[], int PW[], int AC[])
{
	bool incorrectPercentages = (ES + ET + EG + EHU != 100);
	bool invalidHealthRange = (HP[0] < 0 || HP[1] < HP[0]);
	bool invalidPowerRange = (PW[0] < 0 || PW[1] < PW[0]);
	bool invalidAttackCapacityRange = (AC[0] < 0 || AC[1] < AC[0]);
	bool invalidHealUnitPercentage = (EHU > 5);
	if (incorrectPercentages || invalidHealthRange || invalidPowerRange || invalidAttackCapacityRange || invalidHealUnitPercentage)
	{
		return false;
	}
	humanSoldierPercentage = ES;
	humanTankPercentage = ET;
	humanGunnerPercentage = EG;
	humanHealUnitPercentage = EHU;
	humanHealthMin = HP[0];
	humanHealthMax = HP[1];
	humanPowerMin = PW[0];
	humanPowerMax = PW[1];
	humanAttackCapacityMin = AC[0];
	humanAttackCapacityMax = AC[1];
	return true;
}

bool generator::assignAlienArmyParamters(int AS, int AM, int AD, int HP[], int PW[], int AC[])
{
	bool incorrectPercentages = (AS + AM + AD != 100);
	bool invalidHealthRange = (HP[0] < 0 || HP[1] < HP[0]);
	bool invalidPowerRange = (PW[0] < 0 || PW[1] < PW[0]);
	bool invalidAttackCapacityRange = (AC[0] < 0 || AC[1] < AC[0]);
	if (incorrectPercentages || invalidHealthRange || invalidPowerRange || invalidAttackCapacityRange)
	{
		return false;
	}
	alienSoldierPercentage = AS;
	alienMonsterPercentage = AM;
	alienDronePercentage = AD;
	alienHealthMin = HP[0];
	alienHealthMax = HP[1];
	alienPowerMin = PW[0];
	alienPowerMax = PW[1];
	alienAttackCapacityMin = AC[0];
	alienAttackCapacityMax = AC[1];
	return true;
}

void generator::generate(int timeStep)
{
	
	if (generateNumber() <= generationProbability)
	{
		int generatedNumber;
		for (int i = 0; i < generationCount; i++)
		{
			if (humanNextFreeID >= 1999) break;
			generatedNumber = generateNumber();
			if (generatedNumber <= humanSoldierPercentage)
			{
				int HP = generateNumber(humanHealthMin, humanHealthMax);
				int PW = generateNumber(humanPowerMin, humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				humanSoldier* newUnit = new humanSoldier(humanNextFreeID, HP, PW, AC, timeStep);
				gm->getEarthArmy()->addSoldier(newUnit);
				units.enqueue(newUnit);
			}
			else if (generatedNumber <= (humanTankPercentage + humanSoldierPercentage))
			{
				int HP = generateNumber(humanHealthMin, humanHealthMax);
				int PW = generateNumber(humanPowerMin, humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				humanTank* newUnit = new humanTank(humanNextFreeID, HP, PW, AC, timeStep);
				gm->getEarthArmy()->addTank(newUnit);
				units.enqueue(newUnit);
			}
			else if (generatedNumber <= (humanTankPercentage + humanSoldierPercentage + humanHealUnitPercentage))
			{
				int HP = generateNumber(humanHealthMin, humanHealthMax);
				int PW = generateNumber(humanPowerMin, humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				humanGunner* newUnit = new humanGunner(humanNextFreeID, HP, PW, AC, timeStep);
				gm->getEarthArmy()->addGunner(newUnit);
				units.enqueue(newUnit);
			}
			else
			{
				int HP = generateNumber(humanHealthMin, humanHealthMax);
				int PW = generateNumber(humanPowerMin, humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				humanHealer* newUnit = new humanHealer(humanNextFreeID, HP, PW, AC, timeStep);
				gm->getEarthArmy()->addHealer(newUnit);
				units.enqueue(newUnit);
			}
			humanNextFreeID++;
		}
	}
	if (generateNumber() <= generationProbability)
	{
		int generatedNumber;
		for (int i = 0; i < generationCount; i++)
		{
			if (alienNextFreeID >= 3999) break;
			generatedNumber = generateNumber();
			if (generatedNumber <= alienSoldierPercentage)
			{
				int HP = generateNumber(alienHealthMin, alienHealthMax);
				int PW = generateNumber(alienPowerMin, alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				alienSoldier* newUnit = new alienSoldier(alienNextFreeID, HP, PW, AC, timeStep);
				gm->getAlienArmy()->addSoldier(newUnit);
				units.enqueue(newUnit);
			}
			else if (generatedNumber <= (alienMonsterPercentage + alienSoldierPercentage))
			{
				int HP = generateNumber(alienHealthMin, alienHealthMax);
				int PW = generateNumber(alienPowerMin, alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				alienMonster* newUnit = new alienMonster(alienNextFreeID, HP, PW, AC, timeStep);
				gm->getAlienArmy()->addMonster(newUnit);
				units.enqueue(newUnit);
			}
			else
			{
				int HP = generateNumber(alienHealthMin, alienHealthMax);
				int PW = generateNumber(alienPowerMin, alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				alienDrone* newUnit = new alienDrone(alienNextFreeID, HP, PW, AC, timeStep);
				gm->getAlienArmy()->addDrone(newUnit);
				units.enqueue(newUnit);
			}
			alienNextFreeID++;
		}
	}
}
