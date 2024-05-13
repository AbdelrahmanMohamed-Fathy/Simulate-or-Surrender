#include "generator.h"
#include "gameManager.h"
#include "utils/generateNumber.cpp"

generator::generator(gameManager* GM) : gm(GM)
{
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

void generator::generate()
{
	
	if (generateNumber() <= generationProbability)
	{
		int generatedNumber;
		for (int i = 0; i < generationCount; i++)
		{
			generatedNumber = generateNumber();
			if (generatedNumber <= humanSoldierPercentage)
			{
				int HP = generateNumber(humanHealthMin, humanHealthMax);
				int PW = generateNumber(humanPowerMin, humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				gm->getEarthArmy()->addSoldier(HP, PW, AC);
			}
			else if (generatedNumber <= (humanTankPercentage + humanSoldierPercentage))
			{
				int HP = generateNumber(humanHealthMin, humanHealthMax);
				int PW = generateNumber(humanPowerMin, humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				gm->getEarthArmy()->addTank(HP, PW, AC);
			}
			else if (generatedNumber <= (humanTankPercentage + humanSoldierPercentage + humanHealUnitPercentage))
			{
				int HP = generateNumber(humanHealthMin, humanHealthMax);
				int PW = generateNumber(humanPowerMin, humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				gm->getEarthArmy()->addHealer(HP, PW, AC);
			}
			else
			{
				int HP = generateNumber(humanHealthMin, humanHealthMax);
				int PW = generateNumber(humanPowerMin, humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				gm->getEarthArmy()->addGunner(HP, PW, AC);
			}
		}
	}
	if (generateNumber() <= generationProbability)
	{
		int generatedNumber;
		for (int i = 0; i < generationCount; i++)
		{
			generatedNumber = generateNumber();
			if (generatedNumber <= alienSoldierPercentage)
			{
				int HP = generateNumber(alienHealthMin, alienHealthMax);
				int PW = generateNumber(alienPowerMin, alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				gm->getAlienArmy()->addSoldier(HP, PW, AC);
			}
			else if (generatedNumber <= (alienMonsterPercentage + alienSoldierPercentage))
			{
				int HP = generateNumber(alienHealthMin, alienHealthMax);
				int PW = generateNumber(alienPowerMin, alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				gm->getAlienArmy()->addMonster(HP, PW, AC, alienMonsterInfection);
			}
			else
			{
				int HP = generateNumber(alienHealthMin, alienHealthMax);
				int PW = generateNumber(alienPowerMin, alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				gm->getAlienArmy()->addDrone(HP, PW, AC);
			}
		}
	}
}
