#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/bag.h"
#include "../../basicDataStructures/deQueue.h"
#include "../../gameManager.h"

class alienArmy
{
private:
	gameManager* gm;
	queue<>* Soldiers;
	bag<>* Monsters;
	deQueue<>* Drones;
public:
	alienArmy();

	queue<>* getSoldiers();
	bag<>* getMonsters();
	deQueue<>* getDrones();

	~alienArmy()
};

