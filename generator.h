#pragma once
#include "basicDataStructures/queue.h"
#include "units/unit_Interface.h"
class gameManager;

class generator
{
private:
	gameManager* gm;
	queue<unit_Interface*> units;

		//General parameters:
		int generationProbability;
		int generationCount;

		//Earth army parameters:
		int humanHealthMin;
		int humanHealthMax;
		int humanPowerMin;
		int humanPowerMax;
		int humanAttackCapacityMin;
		int humanAttackCapacityMax;

		int humanSoldierPercentage;
		int humanTankPercentage;
		int humanGunnerPercentage;
		int humanHealUnitPercentage;

		//Ally army parameters:
		int allyHealthMin;
		int allyHealthMax;
		int allyPowerMin;
		int allyPowerMax;
		int allyAttackCapacityMin;
		int allyAttackCapacityMax;

		bool emergencyState = false;

		//Alien army paramters:
		int alienHealthMin;
		int alienHealthMax;
		int alienPowerMin;
		int alienPowerMax;
		int alienAttackCapacityMin;
		int alienAttackCapacityMax;

		int alienSoldierPercentage;
		int alienMonsterPercentage;
		int alienDronePercentage;

    int alienMonsterInfection;
  
	//IDs
		int humanNextFreeID;
		int alienNextFreeID;
		int allyNextFreeID;
  
public:
	generator(gameManager* GM, int humanIDStart = 1, int alienIDStart = 2001, int allyIDStart = 5001);
	~generator();
	bool assignGeneralParamteres(int N, int Prob);
	bool assignEarthArmyParamters(int ES, int ET, int EG, int EHU, int HP[], int PW[], int AC[]);
	bool assignAllyArmyParamters(int HP[], int PW[], int AC[]);
	bool assignAlienArmyParamters(int AS, int AM, int AD, int HP[], int PW[], int AC[], int AMI);
	void generate(int timeStep);
	bool assignAlienArmyParamters(int AS, int AM, int AD, int HP[], int PW[], int AC[], int AMI);

	void setEmergencyState(bool rescueNeeded);
};