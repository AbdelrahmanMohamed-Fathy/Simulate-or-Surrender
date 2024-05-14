
#include"generator.h"
#include "gameManager.h"
#include "utils/generateNumber.cpp"
#include "basicDataStructures/queue.cpp"

generator::generator(gameManager* GM, int humanIDStart, int alienIDStart, int allyIDStart) : gm(GM), humanNextFreeID(humanIDStart), alienNextFreeID(alienIDStart), allyNextFreeID(allyIDStart)
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

bool generator::assignAllyArmyParamters(int HP[], int PW[], int AC[])
{
	bool invalidHealthRange = (HP[0] < 0 || HP[1] < HP[0]);
	bool invalidPowerRange = (PW[0] < 0 || PW[1] < PW[0]);
	bool invalidAttackCapacityRange = (AC[0] < 0 || AC[1] < AC[0]);
	if (invalidHealthRange || invalidPowerRange || invalidAttackCapacityRange)
	{
		return false;
	}
	allyHealthMin = HP[0];
	allyHealthMax = HP[1];
	allyPowerMin = PW[0];
	allyPowerMax = PW[1];
	allyAttackCapacityMin = AC[0];
	allyAttackCapacityMax = AC[1];
	return true;
}

bool generator::assignAlienArmyParamters(int AS, int AM, int AD, int HP[], int PW[], int AC[], int AMI)
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
	alienMonsterInfection = AMI;
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
		//Humans generation
		for (int i = 0; i < generationCount; i++)
		{
			if (humanNextFreeID >= 1999) break;
			generatedNumber = generateNumber();
			if (generatedNumber <= humanSoldierPercentage)
			{
				int HP = generateNumber(0.6*humanHealthMin,0.8* humanHealthMax);
				int PW = generateNumber(0.5*humanPowerMin,0.6* humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				humanSoldier* newUnit = new humanSoldier(humanNextFreeID, HP, PW, AC, timeStep);
				gm->getEarthArmy()->addSoldier(newUnit);
				units.enqueue(newUnit);
			}
			else if (generatedNumber <= (humanTankPercentage + humanSoldierPercentage))
			{
				int HP = generateNumber(1.25*humanHealthMin,1.5* humanHealthMax);
				int PW = generateNumber(1.25*humanPowerMin,2* humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				humanTank* newUnit = new humanTank(humanNextFreeID, HP, PW, AC, timeStep);
				gm->getEarthArmy()->addTank(newUnit);
				units.enqueue(newUnit);
			}
			else if (generatedNumber <= (humanTankPercentage + humanSoldierPercentage + humanGunnerPercentage))
			{
				int HP = generateNumber(0.75*humanHealthMin,0.85* humanHealthMax);
				int PW = generateNumber(1.25*humanPowerMin,1.5* humanPowerMax);
				int AC = generateNumber(2*humanAttackCapacityMin,1.25* humanAttackCapacityMax);
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

	//Ally generation
	if(emergencyState && generateNumber() <= generationProbability)
	{
		
		for (int i = 0; i < generationCount; i++)
		{
			if (allyNextFreeID >= 6999) break;
			int HP = generateNumber(0.5 * allyHealthMin, 0.75 * allyHealthMax);
			int PW = generateNumber(0.7 * allyPowerMin, 0.8 * allyPowerMax);
			int AC = generateNumber(allyAttackCapacityMin, allyAttackCapacityMax);
			saviourUnit* newUnit = new saviourUnit(allyNextFreeID, HP, PW, AC, timeStep);
			gm->getAllyArmy()->addSaviour(newUnit);
			units.enqueue(newUnit);
		}
	}

	//Aliens generation
	if (generateNumber() <= generationProbability)
	{
		int generatedNumber;
		for (int i = 0; i < generationCount; i++)
		{
			if (alienNextFreeID >= 3999) break;
			generatedNumber = generateNumber();
			if (generatedNumber <= alienSoldierPercentage)
			{
				int HP = generateNumber(0.5*alienHealthMin,0.75* alienHealthMax);
				int PW = generateNumber(0.7*alienPowerMin,0.8* alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				alienSoldier* newUnit = new alienSoldier(alienNextFreeID, HP, PW, AC, timeStep);
				gm->getAlienArmy()->addSoldier(newUnit);
				units.enqueue(newUnit);
			}
			else if (generatedNumber <= (alienMonsterPercentage + alienSoldierPercentage))
			{
				int HP = generateNumber(1.5*alienHealthMin,2* alienHealthMax);
				int PW = generateNumber(1.5*alienPowerMin,2* alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				alienMonster* newUnit = new alienMonster(alienNextFreeID, HP, PW, AC, alienMonsterInfection, timeStep);
				gm->getAlienArmy()->addMonster(newUnit);
				units.enqueue(newUnit);
			}
			else
			{
				int HP = generateNumber(0.5*alienHealthMin,0.75* alienHealthMax);
				int PW = generateNumber(1.5*alienPowerMin,1.75* alienPowerMax);
				int AC = generateNumber(2*alienAttackCapacityMin,1.5* alienAttackCapacityMax);
				alienDrone* newUnit = new alienDrone(alienNextFreeID, HP, PW, AC, timeStep);
				gm->getAlienArmy()->addDrone(newUnit);
				units.enqueue(newUnit);
			}
			alienNextFreeID++;
		}
	}
}

void generator::setEmergencyState(bool rescueNeeded)
{
	emergencyState = rescueNeeded;
}