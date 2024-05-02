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
				int HP = generateNumber(0.8*humanHealthMin,0.95* humanHealthMax);
				int PW = generateNumber(0.5*humanPowerMin,0.8* humanPowerMax);
				int AC = generateNumber(humanAttackCapacityMin, humanAttackCapacityMax);
				gm->getEarthArmy()->addSoldier(HP, PW, AC);
			}
			else if (generatedNumber <= (humanTankPercentage + humanSoldierPercentage))
			{
				int HP = generateNumber(1.5*humanHealthMin,2* humanHealthMax);
				int PW = generateNumber(1.25*humanPowerMin,2* humanPowerMax);
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
				int HP = generateNumber(0.7*humanHealthMin,0.85* humanHealthMax);
				int PW = generateNumber(1.25*humanPowerMin,1.5* humanPowerMax);
				int AC = generateNumber(2*humanAttackCapacityMin,1.25* humanAttackCapacityMax);
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
				int HP = generateNumber(0.5*alienHealthMin,0.75* alienHealthMax);
				int PW = generateNumber(0.5*alienPowerMin,0.75* alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				gm->getAlienArmy()->addSoldier(HP, PW, AC);
			}
			else if (generatedNumber <= (alienMonsterPercentage + alienSoldierPercentage))
			{
				int HP = generateNumber(1.5*alienHealthMin,2* alienHealthMax);
				int PW = generateNumber(1.5*alienPowerMin,2* alienPowerMax);
				int AC = generateNumber(alienAttackCapacityMin, alienAttackCapacityMax);
				gm->getAlienArmy()->addMonster(HP, PW, AC);
			}
			else
			{
				int HP = generateNumber(0.5*alienHealthMin,0.75* alienHealthMax);
				int PW = generateNumber(1.75*alienPowerMin,1.25* alienPowerMax);
				int AC = generateNumber(2*alienAttackCapacityMin,1.5* alienAttackCapacityMax);
				gm->getAlienArmy()->addDrone(HP, PW, AC);
			}
		}
	}
}
