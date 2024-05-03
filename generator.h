#pragma once
#include "basicDataStructures/queue.h"
#include "units/unit_Interface.h"
class gameManager;

class generator
{
private:
	gameManager* gm;
	queue<unit_Interface*> units;

	//Generatiuon paramaters:
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

	//IDs
		int humanNextFreeID;
		int alienNextFreeID;
public:
	generator(gameManager* GM, int humanIDStart = 1, int alienIDStart = 2001);
	~generator();
	bool assignGeneralParamteres(int N, int Prob);
	bool assignEarthArmyParamters(int ES, int ET, int EG, int EHU, int HP[], int PW[], int AC[]);
	bool assignAlienArmyParamters(int AS, int AM, int AD, int HP[], int PW[], int AC[]);
	void generate(int timeStep);
};