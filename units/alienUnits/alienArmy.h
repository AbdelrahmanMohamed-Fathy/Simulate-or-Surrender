#pragma once
#include "../../basicDataStructures/queue.h"
#include "../../basicDataStructures/Bag.h"
#include "../../basicDataStructures/deQueue.h"
#include "../../gameManager.h"

class alienArmy
{
private:
	gameManager* gm;
	queue<>* Soldiers;
	Bag<>* Monsters;
	deQueue<>* Drones;
public:
	alienArmy();

	queue<>* getSoldiers();
	Bag<>* getMonsters();
	deQueue<>* getDrones();

	~alienArmy()
};

